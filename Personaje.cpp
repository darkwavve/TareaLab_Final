#include "Personaje.h"

Personaje::Personaje()
{
    frame=0;
}

Personaje::~Personaje()
{
    //dtor
}

void Personaje::logic(Uint8* teclas_presionadas)
{
    std::cout<<"Test"<<std::endl;
}

void Personaje::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, *textura_actual, NULL, &rectangulo);
    if(frame%25==0)
        textura_actual++;
    if(orientacion=="down")
    {
        if(textura_actual==texturas_down.end())
            textura_actual=texturas_down.begin();
    }

    if(orientacion=="up")
    {
        if(textura_actual==texturas_up.end())
            textura_actual=texturas_up.begin();
    }

    if(orientacion=="left")
    {
        if(textura_actual==texturas_left.end())
            textura_actual=texturas_left.begin();
    }

    if(orientacion=="right")
    {
        if(textura_actual==texturas_right.end())
            textura_actual=texturas_right.begin();
    }
    frame++;
}

bool Personaje::colision(SDL_Rect r1, SDL_Rect r2)
{
    return r1.x + r1.w > r2.x  &&  r1.x < r2.x + r2.w
            && r1.y + r1.h > r2.y && r1.y < r2.y + r2.h;
}
