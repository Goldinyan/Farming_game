#include "engine.h"
#include <stdio.h>
#include "base_defs.h"

int engine_init(Engine* eng, i32 width, i32 height, i32 fullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return 0;
    }

    eng->window = SDL_CreateWindow(
        "Farming Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (!eng->window) {
        printf("Window Error: %s\n", SDL_GetError());
        return 0;
    }

    if (fullscreen)
        SDL_SetWindowFullscreen(eng->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    eng->renderer = SDL_CreateRenderer(eng->window, -1, SDL_RENDERER_ACCELERATED); // accelerated -> use the gpu
    if (!eng->renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void engine_destroy(Engine* eng)
{
    SDL_DestroyRenderer(eng->renderer);
    SDL_DestroyWindow(eng->window);
    IMG_Quit();
    SDL_Quit();
}

