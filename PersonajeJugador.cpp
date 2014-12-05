#include "PersonajeJugador.h"

PersonajeJugador::PersonajeJugador(int x, int y,
                                    SDL_Renderer* renderer,
                                    list<Personaje*>*personajes)
{
    mp = 100;
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;

    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personaje/down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_down.push_back(textura);

    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personaje/down2.png"));

    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up1.png"));
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left2.png"));

    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right1.png"));
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right2.png"));

    orientacion="down";
    fireball_orientacion = "right";

    textura_actual=texturas_down.begin();

    fireball_texture_right = IMG_LoadTexture(renderer,"assets/fireball3.png");
    fireball_texture_left = IMG_LoadTexture(renderer,"assets/fireball.png");
    fireball_texture_up = IMG_LoadTexture(renderer,"assets/fireball1.png");
    fireball_texture_down = IMG_LoadTexture(renderer,"assets/fireball2.png");

    fireball_texture_actual = fireball_texture_left;

    SDL_QueryTexture(fireball_texture_actual, NULL, NULL,
                        &this->fireball_rect.w,
                        &this->fireball_rect.h);
            fireball_activado=false;

    fireball_cooldown = 100;
    fireball_frame_actual = 0;
    cout<<"MP: "<<mp<<"/100"<<endl;
}

PersonajeJugador::~PersonajeJugador()
{
    //dtor
}

void PersonajeJugador::logic(Uint8* teclas_presionadas)
{
    SDL_Rect temp = this->rectangulo;

    if(fireball_activado)
        fireball_frame_actual++;
    if(fireball_frame_actual>=fireball_cooldown)
        fireball_activado=false;

    if(teclas_presionadas[SDL_SCANCODE_SPACE] && !fireball_activado)
    {
        if(mp > 0 )
        {
            mp -= 10;
            cout<<"MP: "<<mp<<"/100"<<endl;
            fireball_orientacion=orientacion;
            fireball_activado=true;
            fireball_frame_actual=0;
            fireball_rect.x = rectangulo.x;
            fireball_rect.y = rectangulo.y;

            if(orientacion=="right")
            {
                fireball_rect.x+=rectangulo.w;
            }
            if(orientacion=="left")
            {
                fireball_rect.x-=rectangulo.w;
            }
            if(orientacion=="up")
            {
                fireball_rect.y-=rectangulo.h;
            }
            if(orientacion=="down")
            {
                fireball_rect.y+=rectangulo.h;
            }
        }

        if(mp == 0)
        {
            cout<<"MP INSUFICIENTE"<<endl;
        }
    }
    if( teclas_presionadas[ SDL_SCANCODE_UP ] )
    {
        rectangulo.y-=1;
        if(orientacion!="up")
            textura_actual=texturas_up.begin();
        orientacion="up";
    }
    if( teclas_presionadas[ SDL_SCANCODE_DOWN ] )
    {
        rectangulo.y+=1;
        if(orientacion!="down")
            textura_actual=texturas_down.begin();
        orientacion="down";
    }
    if( teclas_presionadas[ SDL_SCANCODE_RIGHT ] )
    {
        rectangulo.x+=1;
        if(orientacion!="right")
            textura_actual=texturas_right.begin();
        orientacion="right";
    }
    if( teclas_presionadas[ SDL_SCANCODE_LEFT ] )
    {
        rectangulo.x-=1;
        if(orientacion!="left")
            textura_actual=texturas_left.begin();
        orientacion="left";
    }

    for(list<Personaje*>::iterator i = personajes->begin();
            i!=personajes->end();
            i++)
    {
        if(this==(*i))
            continue;
        if(colision(this->fireball_rect, (*i)->rectangulo))
        {
            personajes->erase(i);
            fireball_activado=false;
            break;
        }
    }

    if(fireball_activado)
    {
        if(orientacion=="up")
        {
            fireball_texture_actual = fireball_texture_up;
            fireball_rect.y-=5;
        }
        if(orientacion=="down")
        {
                fireball_texture_actual = fireball_texture_down;
            fireball_rect.y+=5;
        }
        if(orientacion=="left")
        {
            fireball_texture_actual = fireball_texture_left;
            fireball_rect.x-=5;
        }
        if(orientacion=="right")
        {
            fireball_texture_actual = fireball_texture_right;
            fireball_rect.x+=5;
        }
    }
}

void PersonajeJugador::render(SDL_Renderer* renderer)
{
    Personaje::render(renderer);
    if(fireball_activado)
    {
        SDL_RenderCopy(renderer,fireball_texture_actual, NULL,&fireball_rect);
    }
}




