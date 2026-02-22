#include "draw.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void draw_water(SDL_Renderer *renderer, SDL_Window *window, i8 animation_count);

void draw_field(field_t *field, SDL_Renderer *renderer, SDL_Window *window, i8 animation_count)
{
    draw_water(renderer, window, animation_count);

    for (int x = 0; x < field->radius; x++)
    {
        for (int y = 0; y < field->radius; y++)
        {

            crop_t crop = field->crops[y * field->radius + x];
            SDL_Rect rect = {x * 10 + 100, y * 10 + 100, 5, 5};

            /*  SDL_Texture *sprite = IMG_LoadTexture(renderer, "public/Player1.png");

              SDL_Rect dst = {y * 16, x * 16, 16, 16}; // 16 x 16
              SDL_RenderCopy(renderer, sprite, NULL, &dst); */

            switch (crop)
            {
            case EMPTY:
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray for empty
                break;
            case WHEAT:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow for wheat
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for unknown crops
                break;
            }

            SDL_RenderFillRect(renderer, &rect); // Draw the crop
        }
    }
};

void draw_water(SDL_Renderer *renderer, SDL_Window *window, i8 animation_count)
{
    SDL_Texture *sprite = IMG_LoadTexture(renderer, "public/water_1.png");

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int offset = animation_count;

    // offset = 0;

    for (i8 x = -1; x < h / 64 + 2; x++)
    {
        for (i8 y = -1; y < w / 64 + 2; y++)
        {
            SDL_Rect dst = {y * 64 + offset , x * 64 , 64, 64};
            SDL_RenderCopy(renderer, sprite, NULL, &dst);
        }
    }
}
