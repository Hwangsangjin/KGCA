#pragma once

struct Vector3
{
	// ����������� 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static const unsigned char Dimension = 3;

	// �������
	union
	{
		struct { float x, y, z; };

		float v[3];
	};

	// ������
	Vector3() = default;
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vector);

	// ������
	const Vector3& operator+=(const Vector3& other);
	const Vector3& operator-=(const Vector3& other);
	const Vector3& operator*=(float scalar);
	const Vector3& operator/=(float scalar);
	const Vector3 operator+(const Vector3& other) const;
	const Vector3 operator-(const Vector3& other) const; 
	const Vector3 operator*(float scalar) const;
	const Vector3 operator/(float scalar) const;
	const Vector3 operator-() const;
	const bool operator==(const Vector3& other) const;
	const bool operator!=(const Vector3& other) const;
	const bool operator<(const Vector3& other) const;
	const bool operator<=(const Vector3& other) const;
	const bool operator>=(const Vector3& other) const;

	// ���� ���
	float Dot(const Vector3& other) const;

	// ���� ���
	float Angle(const Vector3& other) const;

	// ���� ���
	Vector3 Cross(const Vector3& other) const;

	// ���� ���
	float Length() const;
	float LengthSquared() const;

	// �Ÿ� ���
	float Distance(const Vector3& other) const;

	// ����ȭ
	void Normalize();
	Vector3 Identity() const;
};

