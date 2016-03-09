#include "character.hpp"
#include "main.hpp"
#include <math.h>

Character::Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) //Constructor
{

    environment = passed_environment;
    selected = false;
    alive = true;
    attacking = false;
    targeted = false;
    enemy = NULL;

    character_target = false;

    sdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, 30, 40, CollisionRectangle(0,0,30,40)); //unit to move around
    unit->SetUpAnimation(9,4);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2); //allows for unit to stand directly over target instead of offset

    prevX = starting_x;
    prevY = starting_y;

    timeCheck = SDL_GetTicks();
    follow = false;
    distance = 0;
    stopAnimation = false;

    follow_target = NULL;
}

Character::~Character() //Destructor
{
    delete unit;
}

double Character::GetDistance(int x1, int y1, int x2, int y2)
{ //used for unit to take most direct path to target
    double differenceX = x1 - x2;
    double differenceY = y1 - y2;
    double distance = sqrt((differenceX * differenceX) + (differenceY * differenceY));
    return distance;
}

void Character::Draw()
{
    unit->Draw();
}

void Character::Update()
{
        Animate(); // Changes the angle of the character depending on the direction of the click
        Select();  // Selects the character
        Move();    // Moves the character

        if (targeted)
        {
            if (!attacker->isAlive())
            {
                targeted = false;
            }
        }

        if (unit->GetX() > 550 && team == 1) //if human crosses into orc territory, tell AI
        {
            environment->inEnemyTerritory(this);
        }

        //COMBAT
        target = environment->Combat(unit, team); //search for enemy in collision box, returns first enemy found
        buildingTarget = environment->CombatBuilding(unit, team);
        if( target != NULL) //if no enemies, Combat returns NULL
        {
            target->attacked(attack); //attack enemy by passing character's attack to enemy
            attacking = true;
        }else if(buildingTarget != NULL){
            buildingTarget->attacked(attack);
            attacking = true;
        } else
        {
            attacking = false;
        }


        //Check if Character is DEAD
        if (health <= 0)
        {
            alive = false;
            selected = false;
            environment->removeCharacter(team);
        }
}

void Character::Animate(){

    //get angle from unit to destination
    angle = atan2(follow_point_y - unit->GetY(), follow_point_x - unit->GetX());
    angle = angle * (180/3.14159) + 180; //convert angle to degrees

    if (!stopAnimation) //if unit has not reached target yet
    {
        if (135 >= angle && angle > 45) //Walking up
        {
            if (distance > 5) //allow buffer room
            {
                unit->Animation(0,8,0,200); //(start, end, selected animation, speed)
            } else
            {
                unit->Animation(1,1,0,200); //Set unit to single state to stop animation
            }
        } else if (225 >= angle && angle > 135) //Walking Left
        {
            if (distance > 5)
            {
                unit->Animation(0,8,3,200);
            } else
            {
                unit->Animation(1,1,3,200);
            }
        } else if (315 >= angle && angle > 225) //Walking Down
        {
            if (distance > 5)
            {
                unit->Animation(0,8,2,200);
            } else
            {
                unit->Animation(1,1,2,200);
            }
        } else //Walking Right
        {
            if (distance > 5)
            {
                unit->Animation(0,8,1,200);
            } else
            {
                unit->Animation(1,1,1,200);
            }
        }
    }
}

void Character::Select(){

    if (selected)
    {
        environment->displayHealthBar(unit, health/max_health); //selection box around unit

        if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN && team == 1) //mouse button clicked
        {
            if (sdl_setup->GetEv()->button.button == SDL_BUTTON_RIGHT) //specifically, the right mouse button
            //if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT) //specifically, for charlie lol ;)
            {
                follow_target = environment->FindTarget(*MouseX, *MouseY); //check if mouse click is in collision box of another Character (friendly or enemy)

                if (follow_target == NULL) //target is location
                {
                    follow_point_x = *MouseX; //set target where clicked
                    follow_point_y = *MouseY; //set target where clicked
                    character_target = false;
                } else //target is Character
                {
                    follow_point_x = follow_target->getCharacterX(); //set target to Character
                    follow_point_y = follow_target->getCharacterY(); //set target to Character
                    character_target = true;
                }
                follow = true;
            }
        }
    }
}

void Character::Move(){

    if (character_target) //if following another Character
    {
        follow_point_x = follow_target->getCharacterX(); //update target
        follow_point_y = follow_target->getCharacterY(); //update target
    }

    if (timeCheck+10 < SDL_GetTicks() && follow)
    {
        distance = GetDistance(unit->GetX(), unit->GetY(), follow_point_x, follow_point_y);

        stopAnimation = (distance < 5); //boolean to stop animation within 5 of target

        if (distance != 0)
        {
            bool colliding = false;

            for (int i = 0; i < environment->getBuildings().size(); i++) //check for collision
            {
                if (environment->getBuildings()[i]->isAlive())
                {
                    //check if colliding with building that is either constructed or on your team (prevents builder from getting stuck in completed building, cannot collide with unfinished enemy buildings)
                    if (unit->isCollidingBuilding(environment->getBuildings()[i]->GetBuilding()->GetCollisionRect()) && (environment->getBuildings()[i]->isConstructed() || environment->getBuildings()[i]->getTeam() == team))
                    {
                        //below if statements move character away from collision to avoid getting stuck on it
                        if (unit->GetX() > follow_point_x)
                        {
                            unit->SetX(unit->GetX()+1);
                            unit->SetY(unit->GetY()+1);
                        }
                        if (unit->GetX() < follow_point_x)
                        {
                            unit->SetX(unit->GetX()-1);
                            unit->SetY(unit->GetY()-1);
                        }
                        if (unit->GetY() > follow_point_y)
                        {
                            unit->SetY(unit->GetY()+1);
                            unit->SetX(unit->GetX()+1);
                        }
                        if (unit->GetY() > follow_point_y)
                        {
                            unit->SetY(unit->GetY()-1);
                            unit->SetX(unit->GetX()-1);
                        }
                        colliding = true;
                        if (!hasTask) {
                            distance = 0;   //stop unit on collision
                            follow = false;
                            follow_point_x = unit->GetX();
                            follow_point_y = unit->GetY();
                        }
                    }
                }
            }

            if (!colliding)
            {
                if (unit->GetX() < follow_point_x) //left
                {
                    unit->SetX(unit->GetX() - ((unit->GetX()-follow_point_x)/distance) * 1.5f ); // * 1.5f is speed
                }
                if (unit->GetX() > follow_point_x) //right
                {
                    unit->SetX(unit->GetX() - ((unit->GetX()-follow_point_x)/distance) * 1.5f );
                }
                if (unit->GetY() < follow_point_y) //up
                {
                    unit->SetY(unit->GetY() - ((unit->GetY()-follow_point_y)/distance) * 1.5f );
                }
                if (unit->GetY() > follow_point_y) //down
                {
                    unit->SetY(unit->GetY() - ((unit->GetY()-follow_point_y)/distance) * 1.5f );
                }
            }
        } else {
            follow = false;
        }
    prevX = unit->GetX();
    prevY = unit->GetY();
    timeCheck = SDL_GetTicks();
    }
}

int Character::getCharacterX(){
    return unit->GetX();
}

int Character::getCharacterY(){
    return unit->GetY();
}

int Character::getCharacterW(){
    return unit->GetWidth();
}

int Character::getCharacterH(){
    return unit->GetHeight();
}

void Character::attacked(float attacker_attack) //called if attacked by another Character
{
    health = health + defense - attacker_attack;
}

void Character::setFollowPoint(int x, int y)
{
    follow_point_x = x;
    follow_point_y = y;
    follow = true;
}

void Character::Target(Character* passed_attacker)
{
    attacker = passed_attacker;
    targeted = true;
}

