#pragma once

enum CollisionType
{
	Out = 0,
	In,
	Overlap,
};

class Collision
{
public:
    static CollisionType RectToRect(Rect& a, Rect& b);
    static bool RectToInRect(Rect& a, Rect& b);
    static bool CircleToCircle(Circle& a, Circle& b);

    static CollisionType BoxToBox(Box& a, Box& b);
    static bool BoxToInBox(Box& a, Box& b);
    static bool SphereToSphere(Sphere& a, Sphere& b);
};

