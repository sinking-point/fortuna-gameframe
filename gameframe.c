#include "gameframe.h"

game_scene *scene;

void set_scene(game_scene *next) {
  scene = next;
}

int run_frame(int status) {
  game_entity[scene->num_entities] prev_states;
  game_scene prev_scene;
  prev_scene.num_entities = scene->num_entities;
  prev_scene.entities = prev_states;
  
  for(int i = 0; i < scene->num_entities; i++) {
    game_entity *current = entities + i;

    prev_states[i] = *current;

    current->update();
  }

  for(int i = 0; i < scene->num_entities; i++) {
    if(scene->entities[i] != prev_states.entities[i]) {
      
    }
  }
}

void update_block(game_scene prev_scene, int x, int y, int width, int height) {
  for(int i = x; i < x + width; i++) {
    for(int j = y; j < y + height; j++) {
      colour new = get_colour(*scene, i, j);

      if(new != get_colour(prev_scene, i, j)) {
        push_pixel(i, j, new);
      }
    }
  }
}

colour get_colour(game_scene to_paint, int x, int y) {
  for(int i = to_paint.num_entities - 1; i >= 0; i--) {
    if(contains(to_paint.entities[i], x, y)) {
      colour c = to_paint.entities[i].pixel_colour(x - to_paint.entities[i].x, y - to_paint.entities[i].y);

      if(c != to_paint.entities[i].transparency_code) {
        return c;
      }
    }
  }

  return 0;
}
