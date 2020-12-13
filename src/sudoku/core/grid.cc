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

#include <sudoku/constants/color.h>
#include <sudoku/core/grid.h>

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

void Grid::setup_frame() {
  std::string s_border = "+---+---+---+---+---+---+---+---+---+";
  std::vector<char> border(s_border.begin(), s_border.end());

  std::string s_mid = "|   |   |   |   |   |   |   |   |   |";
  std::vector<char> mid(s_mid.begin(), s_mid.end());

  matrix.reserve(height());
  for (int i = 0; i < height(); i++)
    if (i % 2 == 0)
      matrix.push_back(border);
    else
      matrix.push_back(mid);
}

void Grid::setup_puzzle() {
  std::vector<std::vector<char>> p{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  puzzle = p;

  for (int i = 1; i < height(); i += 2) {
    for (int j = 2; j < width(); j += 4) {
      matrix[i][j] = puzzle[i / 2][j / 4];
    }
  }
}

void Grid::setup_color() {
  std::vector<int> base_color(width(), color::BLACK);
  std::vector<std::vector<int>> color_grid(height(), base_color);
  color_overlay = color_grid;

  for (int i = 0; i < height(); i++) {
    for (int j = 0; j < width(); j++) {
      // yellow for missing values
      if (matrix[i][j] == '.') color_overlay[i][j] = color::MAGENTA;
      // white otherwise
      else if ((matrix[i][j] != ' ') && (matrix[i][j] != '|') &&
               (matrix[i][j] != '+') && (matrix[i][j] != '-'))
        color_overlay[i][j] = color::WHITE;

      // blue for the borders
      if ((i % 6 == 0) || (j % 12 == 0)) color_overlay[i][j] = color::BLUE;
    }
  }
}

void Grid::highlight(int x, int y) {
  _highlight_x = x;
  _highlight_y = y;
}

void Grid::delete_digit(int x, int y) {
  if (color_overlay[_highlight_y][_highlight_x] == color::MAGENTA)
    matrix[y][x] = '.';
}
