#pragma once

struct Vector3
{
	// 정적 멤버변수 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static const unsigned char Dimension = 3;

	// 멤버변수
	union
	{
		struct
		{
			struct { float _x, _y, _z; };
		};

		std::array<float, Dimension> _scalars = { 0.0f, 0.0f, 0.0f };
	};

	// 생성자
	Vector3() = default;
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vector);

	// 연산자
	const Vector3& operator+=(const Vector3& other);
	const Vector3& operator-=(const Vector3& other);
	const Vector3& operator*=(float scalar);
	const Vector3& operator/=(float scalar);
	const Vector3 operator+(const Vector3& other) const;
	const Vector3 operator-(const Vector3& other);
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

