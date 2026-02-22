#include "draw.h"
#include <stdio.h>

#include <SDL2/SDL.h>

void draw_field(field_t *field, SDL_Renderer *renderer)
{
    for (int x = 0; x < field->radius; x++)
    {
        for (int y = 0; y < field->radius; y++)
        {

            crop_t crop = field->crops[y * field->radius + x];
            SDL_Rect rect = {x * 10 + 100, y * 10 + 100, 5, 5}; 

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
