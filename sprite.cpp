#include "sprite.hpp"

Sprite::Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CollisionRectangle passed_collision_rect) //Constructor
{
    renderer = passed_renderer;
    image = NULL;
    image = IMG_LoadTexture(renderer, FilePath.c_str());
    collision_rect = passed_collision_rect;
    collisionSDLRect = collision_rect.GetRectangle();

    if (image == NULL) //error checking
    {
        std::cout << "Could not load image" << std::endl;
    }

    barracksImage = IMG_LoadTexture(renderer, "images/barracks.png");

    collisionImage20 = IMG_LoadTexture(renderer, "images/collision_rectangleGREEN.png");
    collisionImage19= IMG_LoadTexture(renderer, "images/collision_rectangle19.png");
    collisionImage18 = IMG_LoadTexture(renderer, "images/collision_rectangle18.png");
    collisionImage17 = IMG_LoadTexture(renderer, "images/collision_rectangle17.png");
    collisionImage16 = IMG_LoadTexture(renderer, "images/collision_rectangle16.png");
    collisionImage15 = IMG_LoadTexture(renderer, "images/collision_rectangle15.png");
    collisionImage14= IMG_LoadTexture(renderer, "images/collision_rectangle14.png");
    collisionImage13 = IMG_LoadTexture(renderer, "images/collision_rectangle13.png");
    collisionImage12 = IMG_LoadTexture(renderer, "images/collision_rectangle12.png");
    collisionImage11 = IMG_LoadTexture(renderer, "images/collision_rectangle11.png");
    collisionImage10 = IMG_LoadTexture(renderer, "images/collision_rectangle10.png");
    collisionImage9= IMG_LoadTexture(renderer, "images/collision_rectangle9.png");
    collisionImage8 = IMG_LoadTexture(renderer, "images/collision_rectangle8.png");
    collisionImage7 = IMG_LoadTexture(renderer, "images/collision_rectangle7.png");
    collisionImage6 = IMG_LoadTexture(renderer, "images/collision_rectangle6.png");
    collisionImage5 = IMG_LoadTexture(renderer, "images/collision_rectangle5.png");
    collisionImage4 = IMG_LoadTexture(renderer, "images/collision_rectangle4.png");
    collisionImage3 = IMG_LoadTexture(renderer, "images/collision_rectangle3.png");
    collisionImage2 = IMG_LoadTexture(renderer, "images/collision_rectangle2.png");
    collisionImage1 = IMG_LoadTexture(renderer, "images/collision_rectangle1.png");

    collisionImage = collisionImage20;

    //location and size
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

    //cropped location and size (used for sprite animation)
    crop.x = 0;
    crop.y = 0;
    crop.w = img_width;
    crop.h = img_height;

    //position as double (for distance function)
    X_pos = x;
    Y_pos = y;

    //allows for unit to stand directly on top of target, instead of offset
    origin_x = 0;
    origin_y = 0;

    currentFrame = 0;
    animationDelay = 0;
    amount_frame_x = 0;
    amount_frame_y = 0;
}

Sprite::~Sprite() //Destructor
{
        SDL_DestroyTexture(image);
}

void Sprite::SetUpAnimation(int passed_amount_x, int passed_amount_y)
{
    amount_frame_x = passed_amount_x;
    amount_frame_y = passed_amount_y;
}

void Sprite::Animation(int beginFrame, int endFrame, int row, float speed)
{
    while (animationDelay+speed < SDL_GetTicks()) //cycle through cropped frames of image
    {

        if (endFrame <= currentFrame)
        {
            currentFrame = beginFrame;
        } else {
        currentFrame++;
        }

        crop.x = currentFrame * (img_width/amount_frame_x);
        crop.y = row * (img_height/amount_frame_y);
        crop.w = img_width/amount_frame_x;
        crop.h = img_height/amount_frame_y;

        animationDelay = SDL_GetTicks();
    }
}

void Sprite::Draw()
{
    collision_rect.SetX(rect.x);
    collision_rect.SetY(rect.y);
    collisionSDLRect = collision_rect.GetRectangle();

    SDL_RenderCopy(renderer, image, &crop, &rect);
}

void Sprite::SetX(float x)
{
    X_pos = x;
    rect.x = int(X_pos - origin_x);
}
void Sprite::SetY(float y)
{
    Y_pos = y;
    rect.y = int(Y_pos - origin_y);
}
void Sprite::SetPosition(float x, float y)
{
    X_pos = x;
    Y_pos = y;
    rect.x = int(X_pos - origin_x);
    rect.y = int(Y_pos - origin_y);
}

float Sprite::GetX()
{
    return X_pos;
}
float Sprite::GetY()
{
    return Y_pos;
}

void Sprite::SetOrigin(float x, float y)
{
    origin_x = x;
    origin_y = y;

    SetPosition(GetX(), GetY());
}

int Sprite::GetWidth()
{
    return rect.w;
}

int Sprite::GetHeight()
{
    return rect.h;
}

void Sprite::DisplayRectangle(float health_percent) //called when Character, Building or Gold is selected
{
    if (health_percent < 0.95)
    {
        collisionImage = collisionImage19;
    }
    if (health_percent < 0.90 )
    {
        collisionImage = collisionImage18;
    }
    if (health_percent < 0.85 )
    {
        collisionImage = collisionImage17;
    }
    if (health_percent < 0.80 )
    {
        collisionImage = collisionImage16;
    }
    if (health_percent < 0.75)
    {
        collisionImage = collisionImage15;
    }
    if (health_percent < 0.70 )
    {
        collisionImage = collisionImage14;
    }
    if (health_percent < 0.65 )
    {
        collisionImage = collisionImage13;
    }
    if (health_percent < 0.60 )
    {
        collisionImage = collisionImage12;
    }
    if (health_percent < 0.55)
    {
        collisionImage = collisionImage11;
    }
    if (health_percent < 0.50 )
    {
        collisionImage = collisionImage10;
    }
    if (health_percent < 0.45 )
    {
        collisionImage = collisionImage9;
    }
    if (health_percent < 0.40 )
    {
        collisionImage = collisionImage8;
    }
    if (health_percent < 0.35)
    {
        collisionImage = collisionImage7;
    }
    if (health_percent < 0.30 )
    {
        collisionImage = collisionImage6;
    }
    if (health_percent < 0.25 )
    {
        collisionImage = collisionImage5;
    }
    if (health_percent < 0.20 )
    {
        collisionImage = collisionImage4;
    }
    if (health_percent < 0.15)
    {
        collisionImage = collisionImage3;
    }
    if (health_percent < 0.10 )
    {
        collisionImage = collisionImage2;
    }
    if (health_percent < 0.05 )
    {
        collisionImage = collisionImage1;
    }
    SDL_RenderCopy(renderer, collisionImage, NULL, &collisionSDLRect); //displays rectangle
}

bool Sprite::isColliding(CollisionRectangle collider)
{
    return (collision_rect.GetRectangle().x + collision_rect.GetRectangle().w > collider.GetRectangle().x &&
             collision_rect.GetRectangle().y + collision_rect.GetRectangle().h > collider.GetRectangle().y &&
             collision_rect.GetRectangle().x < collider.GetRectangle().w + collider.GetRectangle().x &&
             collision_rect.GetRectangle().y < collider.GetRectangle().y + collider.GetRectangle().h);
}

bool Sprite::isCollidingBuilding(CollisionRectangle collider)
{
    return (collision_rect.GetRectangle().x + collision_rect.GetRectangle().w > collider.GetRectangle().x+10 && //+10 to allow for a small collision so that units may attack buildings
             collision_rect.GetRectangle().y + collision_rect.GetRectangle().h > collider.GetRectangle().y+10 &&
             collision_rect.GetRectangle().x+10 < collider.GetRectangle().w + collider.GetRectangle().x &&
             collision_rect.GetRectangle().y+10 < collider.GetRectangle().y + collider.GetRectangle().h);
}

void Sprite::changeImage(std::string new_FilePath)
{
    image = IMG_LoadTexture(renderer, new_FilePath.c_str());
}

void Sprite::changeBarracksImage()
{
    image = barracksImage;
}

void Sprite::setCollisionImage()
{
    collisionImage = collisionImage20;
}
