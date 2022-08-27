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

	// �������
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
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y);
	Vector2(const Vector2& v);

	// ������
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);
	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator*(float scalar) const;
	const Vector2 operator/(float scalar) const;
	const Vector2 operator-() const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	bool operator<(const Vector2& other) const;

	// ���� ���
	float Dot(const Vector2& other) const;

	// ���� ���
	float Size() const;
	float SizeSquared() const;

	// �Ÿ� ���
	float distance(const Vector2& other) const;

	// ����ȭ
	Vector2 Normalize() const;

	// ���� ���� Ȯ��
	bool IsZero() const;
};

