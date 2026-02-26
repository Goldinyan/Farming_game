#include "draw.h"
#include "engine.h"
#include "state.h"
#include <stdio.h>

state_t init_state();

int main(void)
{
    Engine eng;
    state_t state = init_state();

    if (!engine_init(&eng, 800, 600, 1))
    {
        return 1;
    }

    i8 animation_count = 0;
    i8 animation_speed = 0; // Change frame every 2 ticks

    int running = 1;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = 0;
        }

        animation_count = (animation_count + 1) % WATER_SIZE;

        SDL_RenderClear(eng.renderer); // clears to black

        draw_field(&state.field, eng.renderer, eng.window, animation_count);

        SDL_RenderPresent(eng.renderer); // shows the screen

        SDL_Delay(16); // ~60 FPS
    }

    engine_destroy(&eng);

    return 0;
}

state_t init_state()
{
    state_t state;

    state.view = FARM;
    state.currencies.money = 0;
    state.resources.base_wheat = 0;
    state.field.radius = 5;
    state.field.crops = calloc(state.field.radius * state.field.radius, sizeof(crop_t));
    state.field.crops[10] = WHEAT;
    return state;
}
