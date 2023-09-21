#include <stdlib.h>
#include "fractal.h"
#include "sg.h"

#define SIZE_DEFAULT 640

int main(void) {
  sg_open(SIZE_DEFAULT, SIZE_DEFAULT, BLACK, WHITE, "Recursive graphs");
  if (fitted_squares("Fitted squares", SIZE_DEFAULT, 24) == 0
      && fitted_triangles("Fitted squares", SIZE_DEFAULT, 24) == 0
      //&& ...
      ) {
  }
  sg_close();
  return EXIT_SUCCESS;
}
