// Sudoku console game.
// Copyright (C) 2020  Vincent Chen

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <sudoku/core/grid.h>
#include <unistd.h>
#include <util/user_input.h>

#include <iostream>

int main() {
  system("clear");

  Grid g;
  for (size_t i = 0; i < g.matrix.size(); i++) {
    for (size_t j = 0; j < g.matrix[0].size(); j++) {
      unsigned int y = g.highlight_y();
      unsigned int x = g.highlight_x();
      if ((i == y) && (j == x)) {
        std::cout << "\033[1;" << g.color_overlay[i][j] << ";7"
                  << "m" << g.matrix[i][j] << "\033[0m";
      } else {
        std::cout << "\033[1;" << g.color_overlay[i][j] << "m" << g.matrix[i][j]
                  << "\033[0m";
      }
    }
    std::cout << std::endl;
  }

  int active_r = 1;
  int active_c = 2;

  KeyPress kp;
  while (true) {
    system("clear");
    kp.update_key_press();

    if (kp.is_left()) {
      if (active_c > 2) {
        active_c -= 4;
        g.highlight(active_c, active_r);
      }
    }

    if (kp.is_right()) {
      if (active_c < 34) {
        active_c += 4;
        g.highlight(active_c, active_r);
      }
    }

    if (kp.is_down()) {
      if (active_r < 17) {
        active_r += 2;
        g.highlight(active_c, active_r);
      }
    }

    if (kp.is_up()) {
      if (active_r > 1) {
        active_r -= 2;
        g.highlight(active_c, active_r);
      }
    }

    if (kp.is_delete()) g.delete_digit(active_c, active_r);

    int num = kp.get_digit();
    if ((num != 0) && (g.color_overlay[active_r][active_c] == 35)) {
      char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
      g.matrix[active_r][active_c] = digits[num];
    }

    for (size_t i = 0; i < g.matrix.size(); i++) {
      for (size_t j = 0; j < g.matrix[0].size(); j++) {
        unsigned int y = g.highlight_y();
        unsigned int x = g.highlight_x();
        if ((i == y) && (j == x)) {
          std::cout << "\033[1;" << g.color_overlay[i][j] << ";7"
                    << "m" << g.matrix[i][j] << "\033[0m";
        } else {
          std::cout << "\033[1;" << g.color_overlay[i][j] << "m"
                    << g.matrix[i][j] << "\033[0m";
        }
      }
      std::cout << std::endl;
    }

    usleep(200000);
  }
  return 0;
}
