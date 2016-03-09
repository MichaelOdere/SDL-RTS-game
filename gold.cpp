#include "gold.hpp"

Gold::Gold(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, Environment* passed_environment)
{
    //each gold tile 75x75, location in map passed through x and y
    Mine = new Sprite(sdl_setup->GetRenderer(), passed_image, x, y, 75, 75, CollisionRectangle(0,0,75,75));

    resources = 750; //amount of resources to be mined
    max_resources = 750;

    selected = false;
    alive = true;
    environment = passed_environment;
}

Gold::~Gold()
{
    delete Mine;
}

void Gold::Update()
{
    if (selected)
    {
        environment->displayHealthBar(Mine, resources/max_resources);; //display remaining resources as health bar when selected
    }

    if (resources <= 0)
    {
        alive = false;
        selected = false;
        environment->goldMineDepleted(Mine->GetX()+30, Mine->GetY()+30); //tell AI gold mine depleted and its location
    }
}

void Gold::DrawGold()
{
    Mine->Draw();
}

bool Gold::Mining()
{
    if (resources > 0)
    {
        resources = resources - 0.0025; //roughly 1/2 resource per second per villager
        return true; //return true of mining successful
    }
    return false;
}

int Gold::getGoldX(){
    return Mine->GetX();
}

int Gold::getGoldY(){
    return Mine->GetY();
}

int Gold::getGoldW(){
    return Mine->GetWidth();
}

int Gold::getGoldH(){
    return Mine->GetHeight();
}
