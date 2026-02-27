#ifndef TEXT_H
#define TEXT_H

#include "base_defs.h"
#include <SDL2/SDL.h>

void draw_text(SDL_Renderer *renderer, const char *path, const char *text, SDL_Color color, i8 x, i8 y);

#endif // !TEXT_H
