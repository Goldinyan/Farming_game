#ifndef STATE_H
#define STATE_H

#include "base_defs.h"

typedef enum {
    CLICK, HOVER, RIGHTCLICK,
} mouse_type_t

typedef enum
{
    FARM,
    SKILL_TREE,
    INVENTORY,
    SHOP,
    SETTINGS,
    BARN
} view_t;

typedef enum
{
    EMPTY,
    WHEAT,
} crop_t;

typedef struct
{
    u8 id;
    char *name;
    char *description;
    char *icon_path;
    crop_t crop;
    i64 amount;
    char unlocked;
    char available;
    u8 id_for_availability;
} skill_t;

typedef struct
{
    skill_t *skills;
    i8 skill_lenght;
} skills_t;

typedef enum
{
    POTION_XX,
} item_t;

typedef struct
{
    u64 base_wheat;
} resource_t;

typedef struct
{
    i64 money;
} currencies_t;

typedef struct {
  u8 id;
  char *name;
  char *description;
  char *icon_path;
  char unlocked;
  char available;
  u8 id_for_availability;

  u32 strenght;
  u8 area;

} hoe_t;

typedef struct {
  i32 radius;
  crop_t* crops;
  
} field_t;

typedef struct
{
    view_t view;
    item_t *items;
    currencies_t currencies;
    resource_t resources;
    skills_t skills;
    hoe_t *hoes;
    u8 selected_hoe;
    field_t field;
} state_t;

#endif // !STATE.H
