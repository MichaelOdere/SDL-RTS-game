#include "gold.hpp"

Gold::Gold(SDL_Setup* sdl_setup, int x, int y)
{
    //each gold tile 50x50, location in map passed through x and y (mouse location when clicked)
    Rock = new Sprite(sdl_setup->GetRenderer(), "images/gold.bmp", x, y, 50, 50, CollisionRectangle(0,0,0,0));

    resources = 100; //amount of resources to be mined, mining method to be implemented

}

Gold::~Gold()
{
    delete Rock;
}

void Gold::DrawGold()
{
    Rock->Draw();
}
