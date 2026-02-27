#include "draw.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "base_defs.h"
#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

void draw_water(SDL_Renderer *renderer, SDL_Window *window, i8 animation_count);
char *get_random_outer(const char *base);

void draw_field(field_t *field, SDL_Renderer *renderer, SDL_Window *window, i8 animation_count)
{
    draw_water(renderer, window, animation_count);

    draw_text(renderer, "public/Chillax-Medium.ttf", "HALLLLOOO", (SDL_Color){0, 0, 0, 255}, 50, 50);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    const int r = field->radius;
    const int last = r + 1; // border index

    const int tile = 64;

    const int grid_size = (last + 1) * tile; // komplette Breite/Höhe
    const int offset = grid_size / 2;        // Mittelpunkt

    // Preload static textures once
    SDL_Texture *bottom_left = IMG_LoadTexture(renderer, "public/bottom_left_1.png");
    SDL_Texture *bottom_right = IMG_LoadTexture(renderer, "public/bottom_right_1.png");

    for (int x = 0; x <= last; x++)
    {
        for (int y = 0; y <= last; y++)
        {
            SDL_Rect dst = {
                y * tile + w / 2 - offset,
                x * tile + h / 2 - offset,
                tile,
                tile};

            if (x == 0 && y == 0)
            {

                continue;
            }

            if (x == 0 && y == last)
            {
                continue;
            }

            if (x == last && y == 0)
            {
                SDL_RenderCopy(renderer, bottom_left, NULL, &dst);
                continue;
            }

            if (x == last && y == last)
            {

                SDL_RenderCopy(renderer, bottom_right, NULL, &dst);
                continue;
            }

            if (x == last)
            {
                const char *path = (x % 3 == 0)
                                       ? "public/bottom_1.png"
                                       : "public/bottom_2.png";

                SDL_Texture *sprite = IMG_LoadTexture(renderer, path);

                SDL_RenderCopy(renderer, sprite, NULL, &dst);
                SDL_DestroyTexture(sprite);
                continue;
            }

            // Top edge
            if (y == 0)
            {
                SDL_Texture *sprite = IMG_LoadTexture(renderer, "public/left_1.png");

                SDL_RenderCopy(renderer, sprite, NULL, &dst);
                SDL_DestroyTexture(sprite);
                continue;
            }

            // TOP
            if (x == 0)
            {

                continue;
            }

            // Right edge
            if (y == last)
            {
                SDL_Texture *sprite = IMG_LoadTexture(renderer, "public/right_1.png");

                SDL_RenderCopy(renderer, sprite, NULL, &dst);
                SDL_DestroyTexture(sprite);
                continue;
            }

            /* -------------------------
               INNER FIELD (crops)
            ------------------------- */

            int cx = x - 1;
            int cy = y - 1;

            // Safe indexing bc crops is radius × radius
            crop_t crop = field->crops[cy * r + cx];
            SDL_Texture *sprite;

            switch (crop)
            {
            case EMPTY:
                sprite = IMG_LoadTexture(renderer, "public/base_full_field1.png");

                SDL_RenderCopy(renderer, sprite, NULL, &dst);
                break;
            case WHEAT:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                break;
            }

            SDL_DestroyTexture(sprite);
        }
    }

    SDL_DestroyTexture(bottom_left);
    SDL_DestroyTexture(bottom_right);
}

void draw_water(SDL_Renderer *renderer, SDL_Window *window, i8 animation_count)
{
    SDL_Texture *sprite = IMG_LoadTexture(renderer, "public/water_1.png");

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    int offset = animation_count;

    offset = 0;

    for (i8 x = -1; x < h / WATER_SIZE + 2; x++)
    {
        for (i8 y = -1; y < w / WATER_SIZE + 2; y++)
        {
            SDL_Rect dst = {y * WATER_SIZE + offset, x * WATER_SIZE, WATER_SIZE, WATER_SIZE};
            SDL_RenderCopy(renderer, sprite, NULL, &dst);
        }
    }

    SDL_DestroyTexture(sprite);
}

char *get_random_outer(const char *base)
{
    srand(time(NULL));
    int rand_num = rand() % 2;
    char result[256];
    snprintf(result, sizeof(result), "%s%s",
             base,
             rand_num == 0 ? "_1.png" : "_2.png");

    return strdup(result); // HEAP STRING, MUST FREE
}
