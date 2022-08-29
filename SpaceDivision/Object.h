#pragma once

class Object
{
public:
    std::string _name;
    float _friction;
    float _mass;
    float _speed;

	Vector3 _vDirection;
	Vector3 _vAcceleration;
	Vector3 _vVelocity;
	Vector3 _vForce;

	Rect _rect;
	Box _box;
	Circle _circle;
	Sphere _sphere;

	Object();
	Object(std::string name);

	virtual void Init();
    virtual void Frame(float fDeltaTime, float fGameTime) {}

	void SetSphere(Vector3 vCenter, float radius);
	void SetSphere(Box box);
	void SetPosition(Vector3 vPos, Vector3 vSize);
	void AddForce(Vector3 vforce);
};

