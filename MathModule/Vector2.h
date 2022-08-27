#pragma once

class Vector2
{
private:
	// ���� ������� 
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 UnitZ;
	static const Vector2 One;
	static const Vector2 Zero;
	static constexpr unsigned char Dimension = 2;

	// ��� ����
	union
	{
		struct
		{
			struct { float _x, _y; };
		};

		std::array<float, Dimension> _scalars = { 0.0f, 0.0f };
	};

public:
	// ������
	constexpr Vector2() = default;
	constexpr Vector2(float x, float y);
	constexpr Vector2(const Vector2& vector);

	// ������
	constexpr Vector2& operator+=(const Vector2& other);
	constexpr Vector2& operator-=(const Vector2& other);
	constexpr Vector2& operator*=(float scalar);
	constexpr Vector2& operator/=(float scalar);
	constexpr Vector2 operator+(const Vector2& other) const;
	constexpr Vector2 operator-(const Vector2& other) const;
	constexpr Vector2 operator*(float scalar) const;
	constexpr Vector2 operator/(float scalar) const;
	constexpr Vector2 operator-() const;
	constexpr bool operator==(const Vector2& other) const;
	constexpr bool operator!=(const Vector2& other) const;
	constexpr bool operator<(const Vector2& other) const;

	// ���� ���
	constexpr float Dot(const Vector2& other) const;

	// ���� ���
	float Size() const;
	constexpr float SizeSquared() const;

	// ����ȭ
	void Normalize();
	Vector2 GetNormalize() const;
};

