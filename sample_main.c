#include "gameframe.h"
#include "svgrgb565.h"

void main(void);
colour square_pixel_colour(int,int);
void square_update(void);
void init(void);

game_entity[1] entities;
game_scene scene;


void main(void) {
  for(;;) {
    init();
  }
}

void init(void) {
  scene.target_frame_time = 100;
  scene.num_entities = 1;

  scene.entities = entities;

  entities[0].x = 100;
  entities[0].y = 100;
  entities[0].width = 10;
  entities[0].height = 10;
  entities[0].pixel_colour = square_pixel_colour;

  start(scene);
}

colour square_pixel_colour(int x, int y) {
  return CORNFLOWER_BLUE;
}

void square_update(void) {
  if(up_pressed) {
    entities[0].y -= 2;
  }

  if(down_pressed) {
    entities[0].y += 2;
  }

  if(left_pressed) {
    entities[0].x -= 2;
  }

  if(right_pressed) {
    entities[0].x += 2;
  }

  if(middle_pressed) {
    stop();
  }
}
