#include "main.hpp"

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    grass = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", 0, 0, 1024, 768); //map
    unit = new Sprite(sdl_setup->GetRenderer(), "images/character.png", 300, 150, 40, 50); //unit to move around
    unit->SetUpAnimation(3,4);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2); //allows for unit to stand directly over target instead of offset

    timeCheck = SDL_GetTicks();

    MouseX = 0;
    MouseY = 0;
    distance = 0;

    follow = false;
    stopAnimation = false;
}

Main::~Main() //Destructor
{
    delete sdl_setup;
    delete grass;
    delete unit;
}

double Main::GetDistance(int x1, int y1, int x2, int y2)
{ //used for unit to take most direct path to target
    double differenceX = x1 - x2;
    double differenceY = y1 - y2;
    double distance = sqrt((differenceX * differenceX) + (differenceY * differenceY));
    return distance;
}

void Main::GameLoop()
{

    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY);

        //draw map and unit in window
        grass->Draw();
        unit->Draw();

        //get angle from unit to destination
        angle = atan2(follow_point_y - unit->GetY(), follow_point_x - unit->GetX());
        angle = angle * (180/3.14159) + 180; //convert angle to degrees

        if (!stopAnimation) //if unit has not reached target yet
        {
            if (135 >= angle && angle > 45) //Walking up
            {
                if (distance > 5) //allow buffer room
                {
                unit->Animation(0,2,3,200);
                } else
                {
                    unit->Animation(1,1,3,200); //Set unit to single state to stop animation
                }
            } else if (225 >= angle && angle > 135) //Walking Left
            {
                if (distance > 5)
                {
                     unit->Animation(0,2,2,200);
                } else
                {
                    unit->Animation(1,1,2,200);
                }
            } else if (315 >= angle && angle > 225) //Walking Down
            {
                if (distance > 5)
                {
                     unit->Animation(0,2,0,200);
                } else
                {
                    unit->Animation(1,1,0,200);
                }
            } else //Walking Right
            {
                if (distance > 5)
                {
                     unit->Animation(0,2,1,200);
                } else
                {
                    unit->Animation(1,1,1,200);
                }
            }
        }

        if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN) //mouse button clicked
            {
                if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT) //specifically, the left mouse button
                {
                    follow_point_x = MouseX; //set target
                    follow_point_y = MouseY; //set target
                    follow = true;
                }
            }

        if (timeCheck+10 < SDL_GetTicks() && follow)
        {
            distance = GetDistance(unit->GetX(), unit->GetY(), follow_point_x, follow_point_y);

            stopAnimation = (distance < 5); //boolean to stop animation within 5 of target

            if (distance != 0)
            {
                if (unit->GetX() < follow_point_x) //left
                {
                    unit->SetX(unit->GetX() - ((unit->GetX()-follow_point_x)/distance) * 1.5f );
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
            } else {
                follow = false;
            }


            timeCheck = SDL_GetTicks();
        }

        sdl_setup->End();

    }
}
