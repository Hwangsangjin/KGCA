#pragma once

struct Vector4
{
	// �����������
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;
	static const Vector4 One;
	static const Vector4 Zero;
	static const unsigned char Dimension = 4;

	// �������
	union
	{
		struct { float x, y, z, w; };

		std::array<float, Dimension> scalars = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	// ������
	Vector4() = default;
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& vector);

	// ������
	const Vector4& operator+=(const Vector4& other);
	const Vector4& operator-=(const Vector4& other);
	const Vector4& operator*=(float scalar);
	const Vector4& operator/=(float scalar);
	const Vector4 operator+(const Vector4& other) const;
	const Vector4 operator-(const Vector4& other) const;
	const Vector4 operator*(float scalar) const;
	const Vector4 operator/(float scalar) const;
	const Vector4 operator-() const;
	const bool operator==(const Vector4& other) const;
	const bool operator!=(const Vector4& other) const;
	const bool operator<=(const Vector4& other) const;
	const bool operator>=(const Vector4& other) const;

	// ���� ���
	float Dot(const Vector4& other) const;

	// ���� ���
	float Angle(const Vector4& other) const;

	// ���� ���
	float Length() const;
	float LengthSquared() const;

	// �Ÿ� ���
	float Distance(const Vector4& other) const;

	// ����ȭ
	void Normalize();
	Vector4 Identity() const;
};

