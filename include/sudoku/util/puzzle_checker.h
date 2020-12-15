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

#pragma once

#include <vector>

namespace puzzle_checker {

bool is_valid(const std::vector<std::vector<int>> &grid, int row, int col,
              int num);
bool exist_in_row(const std::vector<std::vector<int>> &grid, int row, int num);
bool exist_in_col(const std::vector<std::vector<int>> &grid, int col, int num);
bool exist_in_sub_matrix(const std::vector<std::vector<int>> &grid,
                         int start_row, int start_col, int num);

}  // namespace puzzle_checker
