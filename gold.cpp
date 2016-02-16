#include "gold.hpp"

Gold::Gold(SDL_Setup* sdl_setup, int x, int y)
{
    Rock = new Sprite(sdl_setup->GetRenderer(), "images/gold.bmp", x, y, 50, 50); //map

}

Gold::~Gold()
{
    delete Rock;
}

void Gold::DrawGold()
{
    Rock->Draw();
}
