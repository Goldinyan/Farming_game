#include "SDL2/SDL_render.h"
#include "base_defs.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

void draw_text(SDL_Renderer *renderer, const char *path, const char *text, SDL_Color color, i8 x, i8 y)
{
    TTF_Init();

    TTF_Font *font = TTF_OpenFont(path, 32);

    SDL_Surface *surf = TTF_RenderText_Solid(font, text, color);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    SDL_Rect dst = {x, y, 0, 0};
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
}
