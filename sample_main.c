#include "gameframe.h"
#include "svgrgb565.h"
#include "os.h"

void main(void);
colour square_pixel_colour(int,int);
void square_update(void);
void init(void);

game_entity[1] entities;
game_scene scene;


void main(void) {
  os_init();
  init();

  os_add_task(run_frame, 100, 1);
  
  for(;;) {}
}

void init(void) {
  scene.num_entities = 1;

  scene.entities = entities;

  entities[0].x = 100;
  entities[0].y = 100;
  entities[0].width = 10;
  entities[0].height = 10;
  entities[0].transparency_code = 0;
  entities[0].pixel_colour = square_pixel_colour;
  entities[0].update = square_update;

  set_scene(scene);
}

colour square_pixel_colour(int x, int y) {
  return CORNFLOWER_BLUE;
}

void square_update(void) {
  if(get_switch_state(_BV(SWN))) {
    entities[0].y -= 2;
  }

  if(get_switch_state(_BV(SWS))) {
    entities[0].y += 2;
  }

  if(get_switch_state(_BV(SWW))) {
    entities[0].x -= 2;
  }

  if(get_switch_state(_BV(SWE))) {
    entities[0].x += 2;
  }

  if(get_switch_press(_BV(SWC))) {
    init();
  }
}
