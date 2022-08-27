#pragma once

class Vector3
{
private:
	// ���� ������� 
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static constexpr unsigned char Dimension = 3;

	// �������
	union
	{
		struct
		{
			struct { float _x, _y, _z; };
		};

		std::array<float, Dimension> _scalars = { 0.0f, 0.0f, 0.0f };
	};

public:
	// ������
	Vector3() = default;
	~Vector3() = default;

	Vector3(float x, float y, float z);
	Vector3(const Vector3& v);

	// ������
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);
	Vector3& operator/=(float scalar);
	const Vector3 operator+(const Vector3& other) const;
	const Vector3 operator-(const Vector3& other) const;
	const Vector3 operator*(float scalar) const;
	const Vector3 operator/(float scalar) const;
	const Vector3 operator-() const;
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	bool operator<(const Vector3& other) const;

	// ���� ���
	float Dot(const Vector3& other) const;

	// ���� ���
	Vector3 Cross(const Vector3& other) const;

	// ���� ���
	float Size() const;
	float SizeSquared() const;

	// �Ÿ� ���
	float distance(const Vector3& other) const;

	// ����ȭ
	Vector3 Normalize() const;

	// ���� ���� Ȯ��
	bool IsZero() const;
};

