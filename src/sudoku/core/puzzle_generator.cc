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

#include <sudoku/core/puzzle_generator.h>
#include <sudoku/util/puzzle_checker.h>

#include <algorithm>
#include <ctime>

namespace puzzle_generator {

Solver::Solver(std::vector<std::vector<int>> grid) { _grid = grid; }

std::vector<std::vector<int>> Solver::generate_solution(bool use_random_guess) {
  backtrack_solver(use_random_guess = use_random_guess);
  return _soln;
}

void Solver::backtrack_solver(int curr_row, int curr_col,
                              bool use_random_guess) {
  std::tuple<int, int> unfilled = find_unfilled(_grid, curr_row);
  int unfilled_row = std::get<0>(unfilled);
  int unfilled_col = std::get<1>(unfilled);

  if (unfilled_row == -1) {
    _soln = _grid;
    return;
  }

  std::vector<int> num{1, 2, 3, 4, 5, 6, 7, 8, 9};
  if (use_random_guess) {
    std::srand(std::time(0));  // use current time as seed for random generator
    std::random_shuffle(num.begin(), num.end());
  }

  for (int i = 0; i < 9; i++) {
    if (puzzle_checker::is_valid(_grid, unfilled_row, unfilled_col, num[i])) {
      _grid[unfilled_row][unfilled_col] = num[i];  // make a change
      backtrack_solver(unfilled_row, unfilled_col,
                       use_random_guess);     // recurse
      _grid[unfilled_row][unfilled_col] = 0;  // undo change
    }
  }
}

/**
 * Starting from current row, find next unfilled cell.
 */
std::tuple<int, int> Solver::find_unfilled(
    const std::vector<std::vector<int>> &grid, int curr_row) {
  for (int row = curr_row; row < 9; row++)
    for (int col = 0; col < 9; col++)
      if (grid[row][col] == 0) return std::make_tuple(row, col);
  return std::make_tuple(-1, -1);
}

Puzzle::Puzzle() { generate_puzzle(); }

std::vector<std::vector<int>> Puzzle::puzzle() { return _puzzle; }
std::vector<std::vector<int>> Puzzle::solution() { return _solution; }

std::vector<std::vector<int>> Puzzle::generate_valid_filled_grid() {
  // start with empty grid
  std::vector<std::vector<int>> g(9, {0, 0, 0, 0, 0, 0, 0, 0, 0});

  std::srand(std::time(0));  // use current time as seed for random generator

  // fill all diagonal 3x3 matrices randomly
  std::vector<int> num{1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::random_shuffle(num.begin(), num.end());
  for (int i = 0; i < 9; i++) {
    g[i / 3][i % 3] = num[i];
  }

  std::random_shuffle(num.begin(), num.end());
  for (int i = 0; i < 9; i++) {
    g[i / 3 + 3][i % 3 + 3] = num[i];
  }

  std::random_shuffle(num.begin(), num.end());
  for (int i = 0; i < 9; i++) {
    g[i / 3 + 6][i % 3 + 6] = num[i];
  }

  // run the solver against the matrix to create a valid sudoku
  puzzle_generator::Solver s = puzzle_generator::Solver(g);
  std::vector<std::vector<int>> grid = s.generate_solution();
  return grid;
}

void Puzzle::generate_puzzle() {
  // make valid filled sudoku
  _solution = generate_valid_filled_grid();

  // delete random cells to create the puzzle
}

}  // namespace puzzle_generator
