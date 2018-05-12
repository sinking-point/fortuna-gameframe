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
    
    if(*current != prev_states.entities[i]) {
      current->changed = 1;
    } else {
      current->changed = 0;
    }
  }

  for(int i = 0; i < scene->num_entities; i++) {
    if(scene->entities[i].changed) {
      // clean up old pos
      update_block(&prev_scene, prev_scene.entities[i].x, prev_scene.entities[i].y, prev_scene.entities[i].width, prev_scene.entities[i].height, i, 1);

      // draw entity in new position
      update_block(&prev_scene, scene->entities[i].x, scene->entities[i].y, scene->entities[i].width, scene->entities[i].height, i, 0);
    }
  }
}

int been_drawn(game_scene *prev_scene, int x, int y, int index, int cleaning) {
  // if it's in a lower moving object's previous or current pos or in own previous pos, yes. otherwise no.

  if(!cleaning && in(prev_scene->entities[index], x, y)) {
    return 1;
  }

  for(int i = 0; i < index; i++) {
    if(scene->entities[i].changed && (in(prev_scene->entities[i], x, y) || in(scene->entities[i], x, y))) {
      return 1;
    }
  }

  return 0;
}


void update_block(game_scene *prev_scene, int x, int y, int width, int height, int index, int cleaning) {
  for(int i = x; i < x + width; i++) {
    for(int j = y; j < y + height; j++) {
      if(been_drawn(prev_scene,i,j,index,cleaning)) {
        continue;
      }
      
      colour new = get_colour(scene, i, j);

      if(new != get_colour(prev_scene, i, j)) {
        push_pixel(i, j, new);
      }
    }
  }
}

colour get_colour(game_scene *to_paint, int x, int y) {
  for(int i = to_paint->num_entities - 1; i >= 0; i--) {
    if(contains(to_paint->entities[i], x, y)) {
      colour c = to_paint->entities[i].pixel_colour(x - to_paint->entities[i].x, y - to_paint->entities[i].y);

      if(c != to_paint->entities[i].transparency_code) {
        return c;
      }
    }
  }

  return 0;
}

push_pixel(int x, int y, colour c) {
  rectangle r = {x,x,y,y};
  fill_rectangle(r,c);
}
