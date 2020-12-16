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

#include <sudoku/util/data_conversion.h>

#include <unordered_map>

namespace dtype_converter {

std::vector<std::vector<char>> int_to_char(
    const std::vector<std::vector<int>> &grid) {
  std::vector<std::vector<char>> g(
      9, {'.', '.', '.', '.', '.', '.', '.', '.', '.'});

  std::unordered_map<int, char> digit_map = {
      {0, '.'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'},
      {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
  };

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) g[i][j] = digit_map[grid[i][j]];

  return g;
}

// std::vector<std::vector<int>> char_to_int(
//     const std::vector<std::vector<char>> &grid) {}

}  // namespace dtype_converter
