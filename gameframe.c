#include "gameframe.h"

game_scene *scene;

void set_scene(game_scene *next) {
  scene = next;
}

int run_frame(int status) {
  for(int i = 0; i < scene->num_entities; i++) {
    game_entity *current = entities + i;

    int prev_x = current->x;
    int prev_y = current->y;

    current->update();

    
  }
}
