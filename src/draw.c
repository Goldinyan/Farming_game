#include "draw.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void draw_water(SDL_Renderer *renderer, SDL_Window *window, i8 animation_count);
char *get_random_outer(const char *base);

void draw_field(field_t *field, SDL_Renderer *renderer, SDL_Window *window, i8 animation_count)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    draw_water(renderer, window, animation_count);

    const int r = field->radius;

    const int tile = 64;
    const int offset_w = w / 2 - ((r - 1) * 64);
    const int offset_h = h / 2 - ((r - 1) * 64);

    const int last = r + 1; // border index

    // Preload textures once
    SDL_Texture *bottom_left = IMG_LoadTexture(renderer, "public/bottom_left_1.png");
    SDL_Texture *bottom_right = IMG_LoadTexture(renderer, "public/bottom_right_1.png");
    SDL_Texture *empty_field = IMG_LoadTexture(renderer, "public/base_full_field1.png");

    for (int x = 0; x <= last; x++)
    {
        for (int y = 0; y <= last; y++)
        {
            SDL_Rect dst = {y * tile + offset_w, x * tile + offset_h, tile, tile};

            /* -------------------------
               CORNERS
            ------------------------- */

            if (x == 0 && y == 0)
                continue; // top-left (empty for now)

            if (x == last && y == last)
            {
                SDL_RenderCopy(renderer, bottom_right, NULL, &dst);
                continue;
            }

            if (x == last && y == 0)
            {
                SDL_RenderCopy(renderer, bottom_left, NULL, &dst);
                continue;
            }

            if (x == last && y == last)
                continue; // top-right (empty for now)

            /* -------------------------
               EDGES
            ------------------------- */

            // Bottom edge
            if (x == last)
            {
                const char *path = (y % 3 == 0)
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

            // Left edge
            if (x == 0)
                continue;

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

            // Safe indexing: crops is radius × radius
            crop_t crop = field->crops[cy * r + cx];

            switch (crop)
            {
            case EMPTY:
                SDL_RenderCopy(renderer, empty_field, NULL, &dst);
                break;
            case WHEAT:
                break;
            default:
                break;
            }
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

    // int offset = animation_count;

    // offset = 0;

    for (i8 x = -1; x < h / 64 + 2; x++)
    {
        for (i8 y = -1; y < w / 64 + 2; y++)
        {
            SDL_Rect dst = {y * 64, x * 64, 64, 64};
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
