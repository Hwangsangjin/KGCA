#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
    : Component(owner)
    , _radius(0.0f)
{
}

float CircleComponent::GetRadius() const
{
    return _owner->GetScale() * _radius;
}

const Vector2& CircleComponent::GetCenter() const
{
    return _owner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // �Ÿ� �������� ���
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    // ������ ���� �������� ���
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}
