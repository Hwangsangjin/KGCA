#pragma once

class ObjectBase
{
public:
    std::string _name;
    float       _friction;
    float       _mass;
    float       _speed;

    virtual void Init();
    virtual void Frame(float deltaTime);
};