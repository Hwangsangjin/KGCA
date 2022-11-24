#include "pch.h"
#include "SpriteManager.h"
#include "Sprite.h"

HRESULT SpriteManager::Init()
{
    return TRUE;
}

HRESULT SpriteManager::Frame()
{
    return TRUE;
}

HRESULT SpriteManager::Render()
{
    return TRUE;
}

HRESULT SpriteManager::Release()
{
	sprites_.clear();

    return TRUE;
}

HRESULT SpriteManager::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	device_ = device;
	device_context_ = device_context;

	return TRUE;
}

HRESULT SpriteManager::GameDataLoad(const TCHAR* data)
{
	TCHAR buffer[256] = { 0 };
	TCHAR temp[256] = { 0 };
	TCHAR texture_path[256] = { 0 };
	TCHAR mask_path[256] = { 0 };
	TCHAR shader_path[256] = { 0 };

	int num = 0;
	FILE* file;
	_wfopen_s(&file, data, _T("rt"));
	if (file == nullptr)
	{
		return E_FAIL;
	}

	_fgetts(buffer, _countof(buffer), file);
	_stscanf_s(buffer, _T("%s"), temp, (unsigned int)_countof(temp));

	int animation = 0;
	for (;;)
	{
		int frame = 0;
		_fgetts(buffer, _countof(buffer), file);
		_stscanf_s(buffer, _T("%s %d%d %s%s%s"), 
			temp, (unsigned int)_countof(temp), 
			&frame, &animation, 
			texture_path, (unsigned int)_countof(texture_path),
			mask_path, (unsigned int)_countof(mask_path),
			shader_path, (unsigned int)_countof(shader_path));

		W_STR name = temp;
		if (name == L"#END")
		{
			break;
		}

		sprite_types_.push_back(animation);
		rect_names.push_back(temp);
		texture_names_.push_back(texture_path);
		mask_texture_names_.push_back(mask_path);
		shader_names_.push_back(shader_path);

		int read_frame = 0;

		if (animation == 0)
		{
			std::vector<RECT> rects;
			RECT rt;
			for (int i = 0; i < frame; i++)
			{
				_fgetts(buffer, _countof(buffer), file);
				_stscanf_s(buffer, _T("%d %d %d %d %d"),
					&read_frame,
					&rt.left, &rt.top, &rt.right, &rt.bottom);
				rects.push_back(rt);
			}

			sprite_rects_.push_back(rects);
		}
		else
		{
			TCHAR_STRING_VECTOR list;
			for (int i = 0; i < frame; i++)
			{
				_fgetts(buffer, _countof(buffer), file);
				_stscanf_s(buffer, _T("%d %s"),
					&read_frame,
					temp, (unsigned int)_countof(temp));
				list.push_back(temp);
			}

			sprite_strings_.push_back(list);
		}
	}

	fclose(file);

	return TRUE;
}

HRESULT SpriteManager::LoadFile(std::wstring sprite_file)
{
	sprite_rects_.clear();
	sprites_.clear();
	sprite_types_.clear();
	rect_names.clear();
	texture_names_.clear();
	mask_texture_names_.clear();
	shader_names_.clear();

	assert(SUCCEEDED(GameDataLoad(sprite_file.c_str())));

	for (size_t i = 0; i < sprite_files_.size(); i++)
	{
		if (sprite_files_[i] == sprite_file)
		{
			return TRUE;
		}
	}

	sprite_files_.push_back(sprite_file);

	UINT current_texture_index = 0;
	UINT current_uv_index = 0;

	for (size_t i = 0; i < rect_names.size(); i++)
	{
		// 중복 제거
		auto data = FindFile(rect_names[i]);
		if (data != nullptr)
		{
			continue;
		}

		Sprite* new_sprite = nullptr;
		if (sprite_types_[i] == 0)
		{
			new_sprite = new Sprite;
		}
		else
		{
			new_sprite = new SpriteTexture;
		}

		new_sprite->name_ = rect_names[i];
		new_sprite->texture_file_ = texture_names_[i];
		new_sprite->mask_file_ = mask_texture_names_[i];
		new_sprite->shader_file_ = shader_names_[i];

		if (sprite_types_[i] == 1)
		{
			new_sprite->strings_ = sprite_strings_[current_texture_index++];
		}
		else
		{
			new_sprite->rects_ = sprite_rects_[current_uv_index++];
		}

		if (new_sprite)
		{
			HRESULT is_loaded = new_sprite->Load(device_.Get(), device_context_.Get(), sprite_file);
			if (SUCCEEDED(is_loaded))
			{
				sprites_.insert(std::make_pair(new_sprite->name_, std::move(new_sprite)));
			}
			else
			{
				new_sprite->Release();
				delete new_sprite;
			}
		}
	}

    return TRUE;
}

std::shared_ptr<Sprite> SpriteManager::FindFile(std::wstring sprite_file)
{
	auto iter = sprites_.find(sprite_file);
	if (iter != sprites_.end())
	{
		return iter->second;
	}

	return nullptr;
}
