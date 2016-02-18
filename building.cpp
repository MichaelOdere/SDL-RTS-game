#include "building.hpp"

Building::Building(SDL_Setup* sdl_setup, std::string FilePath, int x, int y)
{
    Structure = new Sprite(sdl_setup->GetRenderer(), FilePath.c_str(), x, y, 75, 75, CollisionRectangle(0, 0, 75, 75));

}

Building::~Building()
{
    delete Structure;
}

void Building::DrawBuilding()
{
    Structure->Draw();
}
