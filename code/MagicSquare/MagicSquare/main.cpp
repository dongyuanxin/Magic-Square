#include "magic_square.h"

int main() {
  for (int i = 0; i < 14; ++i) {
    MagicSquare magic_square(i);
    magic_square.print();
    magic_square.print_matrix();
  }

  return 0;
}
