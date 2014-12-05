#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "Personaje.h"

class PersonajeJugador : public Personaje
{
    public:
        int mp;
        SDL_Texture *fireball_texture_up;
        SDL_Texture *fireball_texture_down;
        SDL_Texture *fireball_texture_left;
        SDL_Texture *fireball_texture_right;
        SDL_Texture *fireball_texture_actual;
        SDL_Rect fireball_rect;
        bool fireball_activado;
        int fireball_cooldown;
        int fireball_frame_actual;
        string fireball_orientacion;
        PersonajeJugador(int x, int y,
                          SDL_Renderer* renderer,
                          list<Personaje*>*personajes);
        void logic(Uint8* teclas_presionadas);
        virtual void render(SDL_Renderer* renderer);
        virtual ~PersonajeJugador();
    protected:
    private:
};

#endif // PERSONAJEJUGADOR_H
