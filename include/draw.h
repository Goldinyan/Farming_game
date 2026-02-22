#ifndef DRAW_H
#define DRAW_H

#include "SDL2/SDL_video.h"
#include "state.h"
#include <SDL2/SDL.h>

void draw_field(field_t *field, SDL_Renderer *renderer, SDL_Window *window, i8 animation_count);


#endif /* ifndef DRAW_H
 */
