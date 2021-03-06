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
#include <random>

namespace puzzle_generator {

Solver::Solver(std::vector<std::vector<int>> grid) { _grid = grid; }

void Solver::execute(bool use_random_guess) {
  backtrack_solver(use_random_guess);
}

/**
 * Solver that solves using backtracking.
 */
int Solver::backtrack_solver(bool use_random_guess) {
  // the grid is not unique if there is already more than 1 solution
  // so return at this point, no need to find the rest
  if (_num_soln > 1) {
    return _num_soln;
  }

  int row, col;
  for (int i = 0; i < 81; i++) {
    row = i / 9;
    col = i % 9;
    if (_grid[row][col] == 0) {
      std::vector<int> num{1, 2, 3, 4, 5, 6, 7, 8, 9};
      if (use_random_guess) {
        // use current time as seed for random generator
        std::srand(std::time(0));
        std::random_shuffle(num.begin(), num.end());
      }
      for (int i = 0; i < 9; i++) {
        if (puzzle_checker::is_valid(_grid, row, col, num[i])) {
          _grid[row][col] = num[i];        // make change
          int count = backtrack_solver();  // recurse
          if (count > _num_soln) {
            _num_soln = count;
            _soln = _grid;        // store solution
            _grid[row][col] = 0;  // backtrack even when solved for new paths
          } else {
            _grid[row][col] = 0;  // backtrack
          }
        }
      }  // end loop to try out each digit
      return _num_soln;
    }  // end if (_grid[row][col] == 0)
  }
  return _num_soln + 1;  // add a solution if whole backtrack was successful
}

std::vector<std::vector<int>> Solver::solution() { return _soln; }
int Solver::num_solutions() { return _num_soln; }

Puzzle::Puzzle(int difficulty) {
  _difficulty = difficulty;
  generate_puzzle();
}

std::vector<std::vector<int>> Puzzle::puzzle() { return _puzzle; }
std::vector<std::vector<int>> Puzzle::solution() { return _solution; }

/**
 * Generate a valid filled sudoku grid by running a solver on a seed grid.
 * The seed grid is not completely empty; the diagonal 3x3 matrices are
 * randomly filled first because they do not affect their respective columns
 * and rows.  The solver fills the remaining empty cells.
 */
void Puzzle::generate_valid_filled_grid() {
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
  s.execute(true);
  _solution = s.solution();
}

void Puzzle::remove_values() {
  int attempts = 0;

  _puzzle = _solution;

  while (attempts < _difficulty) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> uniform(0, 8);

    // randomly find a nonzero cell
    int row = uniform(generator);
    int col = uniform(generator);
    while (_puzzle[row][col] == 0) {
      row = uniform(generator);
      col = uniform(generator);
    }

    // cache the original value in case removing makes invalid puzzle
    int cache = _puzzle[row][col];
    _puzzle[row][col] = 0;

    // solve the puzzle with the removed value
    puzzle_generator::Solver s = puzzle_generator::Solver(_puzzle);
    s.execute(true);

    // add an attemp and restore the value if an invalid puzzle is produced
    if (s.num_solutions() != 1) {
      _puzzle[row][col] = cache;
      attempts++;
    }
  }
}

void Puzzle::generate_puzzle() {
  // make valid filled sudoku
  generate_valid_filled_grid();

  // delete random cells to create the puzzle
  remove_values();
}

}  // namespace puzzle_generator
