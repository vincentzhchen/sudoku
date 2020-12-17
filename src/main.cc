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
  int num_wrong = -1;
  int grid_state = -1;

  KeyPress kp;
  while (true) {
    kp.update_key_press();

    if (kp.is_left()) g.move_left();
    if (kp.is_right()) g.move_right();
    if (kp.is_down()) g.move_down();
    if (kp.is_up()) g.move_up();

    if (kp.is_delete()) g.delete_digit();

    int num = kp.get_digit();
    g.insert_digit(num);

    char l = kp.get_char();
    if (l == 'c') num_wrong = g.check_solution();

    if (l == 'n') {
      system("clear");
      char yn;
      std::cout << "start new game? (Y/n): ";
      std::cin >> yn;
      // if ((yn == 'Y') || (yn == 'y')) {
      //   Grid g2;
      //   active_r = 1;
      //   active_c = 2;
      //   num_wrong = -1;
      //   grid_state = -1;
      // }
    }

    if (l == 'q') {
      system("clear");
      char yn;
      std::cout << "quit game? (Y/n): ";
      std::cin >> yn;
      if ((yn == 'Y') || (yn == 'y')) {
        system("clear");
        break;
      }
    }

    // show grid here
    display::display_all(g);

    std::cout << "SOLUTION CHECK: " << num_wrong << " mistakes." << std::endl;

    grid_state = g.check_solution(true);
    if (grid_state == 0)
      std::cout << "GAME STATE: COMPLETE" << std::endl;
    else
      std::cout << "GAME STATE: ACTIVE" << std::endl;

    usleep(200000);  // add some delay to slow down the loop
  }
  return 0;
}
