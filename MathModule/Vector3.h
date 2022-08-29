#pragma once

struct Vector3
{
	// 멤버변수
	union
	{
		struct
		{
			struct { float x, y, z; };
		};

		float v[3];
	};

	// 생성자
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);

	// 연산자
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

	// 내적 계산
	float Dot(const Vector3& other) const;

	// 외적 계산
	Vector3 Cross(const Vector3& other) const;

	// 길이 계산
	float Size() const;
	float SizeSquared() const;

	// 정규화
	void Normalize();
	Vector3 GetNormalize() const;
};

