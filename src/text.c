#include "SDL2/SDL_render.h"
#include "base_defs.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void draw_text(SDL_Renderer *renderer, const char *path, const char *text, SDL_Color color, int x, int y)
{
    // TTF_Init NICHT hier!
    TTF_Font *font = TTF_OpenFont(path, 32);
    if (!font)
    {
        printf("TTF_OpenFont error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface *surf = TTF_RenderText_Solid(font, text, color);
    if (!surf)
    {
        printf("TTF_RenderText_Solid error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (!tex)
    {
        printf("SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect dst = {x, y, 0, 0};
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    SDL_RenderCopy(renderer, tex, NULL, &dst);

    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
}
