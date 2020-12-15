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

// int main() {
//   Grid g;
//   int active_r = 1;
//   int active_c = 2;

//   KeyPress kp;
//   while (true) {
//     kp.update_key_press();

//     if (kp.is_left()) {
//       if (active_c > 2) {
//         active_c -= 4;
//         g.highlight(active_c, active_r);
//       }
//     }

//     if (kp.is_right()) {
//       if (active_c < 34) {
//         active_c += 4;
//         g.highlight(active_c, active_r);
//       }
//     }

//     if (kp.is_down()) {
//       if (active_r < 17) {
//         active_r += 2;
//         g.highlight(active_c, active_r);
//       }
//     }

//     if (kp.is_up()) {
//       if (active_r > 1) {
//         active_r -= 2;
//         g.highlight(active_c, active_r);
//       }
//     }

//     if (kp.is_delete()) g.delete_digit(active_c, active_r);

//     int num = kp.get_digit();
//     g.insert_digit(num, active_c, active_r);

//     // show grid here
//     display::display_all(g);
//     usleep(200000);  // add some delay to slow down the loop
//   }
//   return 0;
// }

#include <sudoku/core/puzzle_generator.h>
int main() {
  puzzle_generator::Puzzle p;
  std::vector<std::vector<int>> grid = p.solution();
  // std::vector<std::vector<int>> g{
  //     {3, 0, 6, 5, 0, 8, 4, 0, 0}, {5, 2, 0, 0, 0, 0, 0, 0, 0},
  //     {0, 8, 7, 0, 0, 0, 0, 3, 1}, {0, 0, 3, 0, 1, 0, 0, 8, 0},
  //     {9, 0, 0, 8, 6, 3, 0, 0, 5}, {0, 5, 0, 0, 9, 0, 6, 0, 0},
  //     {1, 3, 0, 0, 0, 0, 2, 5, 0}, {0, 0, 0, 0, 0, 0, 0, 7, 4},
  //     {0, 0, 5, 2, 0, 6, 3, 0, 0}};
  // puzzle_generator::Solver s = puzzle_generator::Solver(g);
  // std::vector<std::vector<int>> grid = s.generate_solution();

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) std::cout << grid[i][j];
    std::cout << std::endl;
  }
}
