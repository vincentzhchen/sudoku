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

#include <sudoku/util/display.h>

#include <iostream>
#include <vector>

namespace display {

void display_all(Grid grid) {
  std::vector<std::vector<char>> &m = grid.matrix();
  std::vector<std::vector<int>> &c = grid.color_overlay();

  system("clear");
  for (int i = 0; i < grid.height(); i++) {
    for (int j = 0; j < grid.width(); j++) {
      if ((i == grid.highlight_y()) && (j == grid.highlight_x())) {
        std::cout << "\033[1;" << c[i][j] << ";7"
                  << "m" << m[i][j] << "\033[0m";
      } else {
        std::cout << "\033[1;" << c[i][j] << "m" << m[i][j] << "\033[0m";
      }
    }
    std::cout << std::endl;
  }
}

}  // namespace display
