#ifndef COLLISION_RECTANGLE_HPP
#define COLLISION_RECTANGLE_HPP

#include "imports.hpp"


class CollisionRectangle
{
    public:
        CollisionRectangle(); //default constructor for sprites without collisions
        CollisionRectangle(int x, int y, int w, int h);
        ~CollisionRectangle();

        void SetRectangle(int x, int y, int w, int h);
        SDL_Rect GetRectangle() { return CollisionRect; }

        void SetX(int x) { CollisionRect.x = x + OffsetX; }
        void SetY(int y) { CollisionRect.y = y + OffsetY; }

    private:
        int OffsetX;
        int OffsetY;
        SDL_Rect CollisionRect;
};

#endif // COLLISION_RECTANGLE_HPP
