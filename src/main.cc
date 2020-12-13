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
#include <sudoku/util/display.h>
#include <unistd.h>
#include <util/user_input.h>

#include <iostream>

int main() {
  Grid g;
  int active_r = 1;
  int active_c = 2;

  KeyPress kp;
  while (true) {
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
    g.insert_digit(num, active_c, active_r);

    // show grid here
    display::display_all(g);
    usleep(200000);  // add some delay to slow down the loop
  }
  return 0;
}
