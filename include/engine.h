// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "base_defs.h"

typedef struct Engine {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Engine;

int engine_init(Engine* eng, i32 width, i32 height, i32 fullscreen);
void engine_destroy(Engine* eng);

#endif

