#include "environment.hpp"

Environment::Environment(SDL_Setup* sdl_setup)
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*25, j*25, 25, 25); //map
        }
    }
}

Environment::~Environment()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            delete grass[i][j];
        }
    }
}

void Environment::DrawBack()
{

}
void Environment::DrawFront()
{

}
