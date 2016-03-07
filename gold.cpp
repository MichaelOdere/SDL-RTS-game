#include "gold.hpp"

Gold::Gold(SDL_Setup* sdl_setup, int x, int y, Environment* passed_environment)
{
    //each gold tile 50x50, location in map passed through x and y (mouse location when clicked)
    Mine = new Sprite(sdl_setup->GetRenderer(), "images/gold.png", x, y, 75, 75, CollisionRectangle(0,0,75,75));

    resources = 500; //amount of resources to be minedS
    max_resources = 500;

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
        Mine->DisplayRectangle(resources/max_resources);
    }

    if (resources <= 0)
    {
        alive = false;
        selected = false;
        environment->goldMineDepleted(Mine->GetX()+30, Mine->GetY()+30);
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
        resources = resources - 0.0025; //roughly one resource per second per villager
        return true;
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
