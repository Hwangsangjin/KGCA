#pragma once

struct Vector3
{
	// �������
	union
	{
		struct
		{
			struct { float x, y, z; };
		};

		float v[3];
	};

	// ������
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);

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
	Vector3 Cross(const Vector3& other) const;

	// ���� ���
	float Size() const;
	float SizeSquared() const;

	// ����ȭ
	void Normalize();
	Vector3 GetNormalize() const;
};

