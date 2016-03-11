#include "building.hpp"

Building::Building(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment)
{
    Structure = new Sprite(sdl_setup->GetRenderer(), passed_image, x, y, size_x, size_y, CollisionRectangle(0, 0, size_x, size_y));
    selected = false;
    alive = true;
    team = passed_team;
    creating = false;
    environment = passed_environment;
    previous_health = 0;
}

Building::~Building()
{
    if (health > 0) //if destroyed, Structure would have already been deleted
    {
        delete Structure;
    }
}


void Building::DrawBuilding()
{
    Structure->Draw();
}

void Building::Update()
{
    if (selected)
    {
        environment->displayHealthBar(Structure, health/max_health); //construction/health bar
    }

    if (health == previous_health && health != 1 && !constructed) //not being constructed after construction starts
    {
        environment->buildingNotConstructing(Structure->GetX(), Structure->GetY());

    }

    if (health <= 0)
    {
        alive = false;
        selected = false;
    }
    previous_health = health;
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

void Building::constructing()
{
    health += 0.02;
    if (health >= max_health)
    {
        constructed = true; //allows use of building and stops villager from constructing
        health = max_health; //ensures health is not greater than max
        environment->setCollisionImage(Structure); //set health bar to max health
    }
}
