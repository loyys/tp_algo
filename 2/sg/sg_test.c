#include <stdlib.h>
#include "sg.h"

#define WIDTH   600
#define HEIGHT  400

int main(void) {
  sg_open(WIDTH, HEIGHT, BLACK, WHITE, "Simple Graph Test");
  do {
    sg_set_title("Simple Graph Test. Hit any key to continue");
    sg_set_fgcolor(WHITE);
    sg_draw_line(0, 0, WIDTH, HEIGHT);
    sg_get_key();
    sg_set_fgcolor(RED);
    for (int k = 0; k < HEIGHT; ++k) {
      sg_draw_point(k, HEIGHT - k);
    }
    {
      int x = WIDTH / 2;
      int y = HEIGHT / 2;
      int dx = x / 2;
      int dy = y / 2;
      sg_set_fgcolor(RED);
      sg_get_key();
      sg_draw_rectangle(x, y, (unsigned int) dx, (unsigned int) dy);
      sg_get_key();
      sg_set_fgcolor(LIME);
      sg_fill_rectangle(x + dx, y + dy, (unsigned int) dx, (unsigned int) dy);
      sg_get_key();
      sg_set_fgcolor(MAGENTA);
      sg_fill_rectangle(x + rand() % dx, y + rand() % dy,
          (unsigned int) dx, (unsigned int) dy);
      sg_get_key();
    }
    sg_set_fgcolor(BLACK);
    sg_set_title(
        "Simple Graph Test. Hit 'q' to quit, any other key to continue");
    while (!sg_key_event()) {
      int x = rand() % WIDTH;
      int y = rand() % HEIGHT;
      sg_draw_point(x, y);
    }
  } while (sg_get_key() != 'q');
  sg_close();
  return EXIT_SUCCESS;
}
