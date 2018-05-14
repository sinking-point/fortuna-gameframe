#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <stdlib.h>
#include "os.h"

typedef uint16_t colour;

// constants

// structs
typedef struct game_entity {
  int x, y, width, height, changed;

  // colour that should be interpreted as transparent
  colour transparency_code;

  /* returns the pixel colour of the sprite of this entity at coords given, 
     origin being top left corner of the sprite */
  colour (*pixel_colour)(int x, int y);

  // defines the behaviour of this entity each cycle of the game loop
  void (*update)(void);
} game_entity;

typedef struct game_scene {
  int num_entities;
  game_entity *entities;
} game_scene;

// functions

//changes the current scene
void set_scene(game_scene*);

// runs a frame of gameplay
int run_frame(int);


#endif
