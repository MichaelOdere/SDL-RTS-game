#ifndef TEXT_HPP
#define TEXT_HPP

#include "imports.hpp"

class TextMessage
{
public:

    TextMessage(SDL_Renderer* passed_renderer, std::string message, int x, int y);
    ~TextMessage();

    SDL_Texture *image;
    SDL_Rect rect;
    SDL_Rect crop;
    void Draw(std::string message);
    void SetX(float x);
    void SetY(float y);
    void SetPosition(float x, float y);
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
    void SetOrigin(float x, float y);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture* renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer);

private:

    float X_pos;
    float Y_pos;
    float origin_x;
    float origin_y;
    SDL_Texture* textTexture;
    SDL_Renderer* renderer;
};

#endif // TEXT_HPP
