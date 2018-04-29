#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <sdtlib.h>

typedef uint_16 colour;

// constants

// structs
typedef struct game_scene {
  int target_frame_time, num_entities;
  game_entity *entities;
}

typedef struct game_entity {
  int x, y, width, height;

  /* returns the pixel colour of the sprite of this entity at coords given, 
     origin being top left corner of the sprite */
  colour (*pixel_colour)(int x, int y);

  // defines the behaviour of this entity each cycle of the game loop
  void (*update)(void);
} game_entity;

// functions
void start(game_scene);
void stop(void);


#endif