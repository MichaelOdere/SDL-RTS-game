#include "collision_rectangle.hpp"

//invisible rectangle around sprites to detect collisions
//using to avoid walking through buildings, mining, attacking enemy units and showing selected unit
CollisionRectangle::CollisionRectangle()
{
    OffsetX = 0;
    OffsetY = 0;
    SetRectangle(0,0,0,0);
}

CollisionRectangle::CollisionRectangle(int x, int y, int w, int h)
{
    OffsetX = x;
    OffsetY = y;
    SetRectangle(x, y, w, h);
}

CollisionRectangle::~CollisionRectangle()
{
}

void CollisionRectangle::SetRectangle(int x, int y, int w, int h)
{
    CollisionRect.x = x + OffsetX;
    CollisionRect.y = y + OffsetY;
    CollisionRect.w = w;
    CollisionRect.h = h;
}
