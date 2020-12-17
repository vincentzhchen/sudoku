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
#include <sudoku/core/puzzle_generator.h>
#include <sudoku/util/data_conversion.h>

#include <string>

Grid::Grid() {
  // setup frame
  setup_frame();

  // initialize a puzzle
  setup_puzzle();

  // add color
  setup_color();
}

const int Grid::height() { return _height; }
const int Grid::width() { return _width; }
int Grid::highlight_x() { return _highlight_x; }
int Grid::highlight_y() { return _highlight_y; }
std::vector<std::vector<char>> &Grid::matrix() { return _matrix; }
std::vector<std::vector<char>> &Grid::puzzle() { return _puzzle; }
std::vector<std::vector<int>> &Grid::color_overlay() { return _color_overlay; }

void Grid::setup_frame() {
  std::string s_border = "+---+---+---+---+---+---+---+---+---+";
  std::vector<char> border(s_border.begin(), s_border.end());

  std::string s_mid = "|   |   |   |   |   |   |   |   |   |";
  std::vector<char> mid(s_mid.begin(), s_mid.end());

  _matrix.reserve(height());
  for (int i = 0; i < height(); i++)
    if (i % 2 == 0)
      _matrix.push_back(border);
    else
      _matrix.push_back(mid);
}

void Grid::setup_puzzle() {
  puzzle_generator::Puzzle p(5);
  _puzzle = dtype_converter::int_to_char(p.puzzle());
  _solution = dtype_converter::int_to_char(p.solution());

  for (int i = 1; i < height(); i += 2) {
    for (int j = 2; j < width(); j += 4) {
      _matrix[i][j] = _puzzle[i / 2][j / 4];
    }
  }
}

void Grid::setup_color() {
  std::vector<int> base_color(width(), _base_color);
  std::vector<std::vector<int>> color_grid(height(), base_color);
  _color_overlay = color_grid;

  for (int i = 0; i < height(); i++) {
    for (int j = 0; j < width(); j++) {
      // yellow for missing values
      if (_matrix[i][j] == '.') _color_overlay[i][j] = _missing_val_color;
      // white otherwise
      else if ((_matrix[i][j] != ' ') && (_matrix[i][j] != '|') &&
               (_matrix[i][j] != '+') && (_matrix[i][j] != '-'))
        _color_overlay[i][j] = _given_val_color;

      // blue for the borders
      if ((i % 6 == 0) || (j % 12 == 0)) _color_overlay[i][j] = _border_color;
    }
  }
}

void Grid::highlight() {
  _highlight_x = _active_c;
  _highlight_y = _active_r;
}

void Grid::move_up() {
  if (_active_r > 1) {
    _active_r -= 2;
    highlight();
  }
}

void Grid::move_down() {
  if (_active_r < 17) {
    _active_r += 2;
    highlight();
  }
}

void Grid::move_left() {
  if (_active_c > 2) {
    _active_c -= 4;
    highlight();
  }
}

void Grid::move_right() {
  if (_active_c < 34) {
    _active_c += 4;
    highlight();
  }
}

void Grid::insert_digit(int digit) {
  int y = _active_r;
  int x = _active_c;
  if ((digit != 0) && (_color_overlay[y][x] == _missing_val_color)) {
    _matrix[y][x] = _digits[digit];
  }
}

void Grid::delete_digit() {
  int y = _active_r;
  int x = _active_c;
  if (_color_overlay[_highlight_y][_highlight_x] == _missing_val_color)
    _matrix[y][x] = '.';
}

int Grid::check_solution(bool include_missing) {
  int count = 0;

  if (!include_missing) {
    for (int i = 1; i < height(); i += 2)
      for (int j = 2; j < width(); j += 4)
        if (_matrix[i][j] != '.')
          if (_matrix[i][j] != _solution[i / 2][j / 4]) count++;
  } else {
    for (int i = 1; i < height(); i += 2)
      for (int j = 2; j < width(); j += 4)
        if (_matrix[i][j] != _solution[i / 2][j / 4]) count++;
  }

  return count;
}
