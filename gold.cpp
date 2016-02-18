#include "gold.hpp"

Gold::Gold(SDL_Setup* sdl_setup, int x, int y)
{
    //each gold tile 50x50, location in map passed through x and y (mouse location when clicked)
    Mine = new Sprite(sdl_setup->GetRenderer(), "images/gold.bmp", x, y, 50, 50, CollisionRectangle(0,0,50,50));

    resources = 1000; //amount of resources to be mined, mining method to be implemented

}

Gold::~Gold()
{
    delete Mine;
}

void Gold::DrawGold()
{
    Mine->Draw();
}

bool Gold::Mining()
{
    if (resources > 0)
    {
        resources = resources - 0.005; //roughly one resource per second per villager
        return true;
    }
    return false;
}
