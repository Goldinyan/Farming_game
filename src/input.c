#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "draw.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



void track_input(i8 x, i8 y, view_t view, mouse_type_t mouse_type, state_t *state)
{
    if (view == SKILL_TREE)
    {
        for (i8 i = 0; i > state->skills.lenght; i++)
        {

            i8 s_x = state->skills[i].x;
            i8 s_y = state->skills[i].y;

            if (fabs(s_x - x) > 20)
                continue;

            if (x > s_x && x < s_x + SKILL_WIDTH && y > s_y && y < s_y + SKILLSWIDTH)
            {
                if (mouse_type == HOVER)
                {
                    show_hover(i);
                }

                if(mouse_type ==)
            }
        }
    }
}
