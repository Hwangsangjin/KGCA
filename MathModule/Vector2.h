#pragma once

struct Vector2
{
	// ���� ������� 
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 UnitZ;
	static const Vector2 One;
	static const Vector2 Zero;
	static const unsigned char Dimension = 2;

	// ��� ����
	union
	{
		struct
		{
			struct { float _x, _y; };
		};

		std::array<float, Dimension> _scalars = { 0.0f, 0.0f };
	};

	// ������
	Vector2() = default;
	Vector2(float x, float y);
	Vector2(const Vector2& vector);

	// ������
	const Vector2& operator+=(const Vector2& other);
	const Vector2& operator-=(const Vector2& other);
	const Vector2& operator*=(float scalar);
	const Vector2& operator/=(float scalar);
	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator*(float scalar) const;
	const Vector2 operator/(float scalar) const;
	const Vector2 operator-() const;
	const bool operator==(const Vector2& other) const;
	const bool operator!=(const Vector2& other) const;
	const bool operator<(const Vector2& other) const;

	// ���� ���
	float Dot(const Vector2& other) const;

	// ���� ���
	float Size() const;
	float SizeSquared() const;

	// ����ȭ
	void Normalize();
	Vector2 GetNormalize() const;
};

