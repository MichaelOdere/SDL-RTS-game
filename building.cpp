#include "building.hpp"

Building::Building(SDL_Setup* sdl_setup, std::string FilePath, int x, int y)
{
    Structure = new Sprite(sdl_setup->GetRenderer(), FilePath.c_str(), x, y, 75, 75, CollisionRectangle(0, 0, 75, 75));
    selected = false;
    alive = true;
}

Building::~Building()
{
    delete Structure;
}


void Building::DrawBuilding()
{
    Structure->Draw();
    if(selected){
        Structure->DisplayRectangle(1.0);
    }
}

void Building::Update()
{
    if (selected)
    {
        std::cout << health << std::endl;
        Structure->DisplayRectangle(health/max_health);

    if (health <= 0)
    {
        alive = false;
        selected = false;
    }
    }
}

void Building::Select(){
    if(selected){
        selected = false;
    }else{
        selected = true;
    }
}

int Building::getStructureX(){
    return Structure->GetX();
}

int Building::getStructureY(){
    return Structure->GetY();
}
int Building::getStructureW(){
    return Structure->GetWidth();
}

int Building::getStructureH(){
    return Structure->GetHeight();
}

void Building::attacked(float attacker_attack) //called if attacked by another character
{
    health = health - attacker_attack;
}
