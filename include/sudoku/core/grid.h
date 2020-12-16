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

#include <sudoku/constants/color.h>

#include <vector>

class Grid {
 public:
  Grid();
  std::vector<std::vector<char>> &matrix();
  std::vector<std::vector<char>> &puzzle();
  std::vector<std::vector<int>> &color_overlay();
  const int height();
  const int width();
  int highlight_x();
  int highlight_y();
  void highlight(int x, int y);
  void insert_digit(int digit, int x, int y);
  void delete_digit(int x, int y);
  int check_solution(bool include_missing = false);

 private:
  // sudoku board dimension is fixed
  const int _height = 19;
  const int _width = 37;

  // always have cursor on first number
  int _highlight_x = 2;
  int _highlight_y = 1;

  // color scheme
  const int _base_color = color::BLACK;
  const int _border_color = color::BLUE;
  const int _missing_val_color = color::MAGENTA;
  const int _given_val_color = color::WHITE;

  // lookup
  char _digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  std::vector<std::vector<char>> _matrix;
  std::vector<std::vector<char>> _puzzle;
  std::vector<std::vector<char>> _solution;
  std::vector<std::vector<int>> _color_overlay;

  void setup_frame();
  void setup_color();
  void setup_puzzle();
};
