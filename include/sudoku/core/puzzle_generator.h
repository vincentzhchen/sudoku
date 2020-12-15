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

#include <tuple>
#include <vector>

namespace puzzle_generator {

class Solver {
 public:
  explicit Solver(std::vector<std::vector<int>> grid);
  std::vector<std::vector<int>> generate_solution(
      bool use_random_guess = false);

 private:
  std::vector<std::vector<int>> _grid;
  std::vector<std::vector<int>> _soln;

  void backtrack_solver(int curr_row = 0, int curr_col = 0,
                        bool use_random_guess = false);
  std::tuple<int, int> find_unfilled(const std::vector<std::vector<int>> &grid,
                                     int curr_col);
};

class Puzzle {
 public:
  Puzzle();
  void generate_puzzle();
  std::vector<std::vector<int>> puzzle();
  std::vector<std::vector<int>> solution();

 private:
  std::vector<std::vector<int>> generate_valid_filled_grid();

  std::vector<std::vector<int>> _puzzle;
  std::vector<std::vector<int>> _solution;
};

}  // namespace puzzle_generator