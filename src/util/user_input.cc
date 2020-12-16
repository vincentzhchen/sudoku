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

#include <util/user_input.h>

bool KeyPress::is_up() { return get_key_press() == keyns::Key::UP; }
bool KeyPress::is_down() { return get_key_press() == keyns::Key::DOWN; }
bool KeyPress::is_left() { return get_key_press() == keyns::Key::LEFT; }
bool KeyPress::is_right() { return get_key_press() == keyns::Key::RIGHT; }
bool KeyPress::is_delete() { return get_key_press() == keyns::Key::DELETE; }

void KeyPress::update_key_press() {
  enable_raw_mode();
  keyns::Key kp;
  if (kbhit()) {
    switch (getch()) {
      case 'w':
      case 'k':
        kp = keyns::Key::UP;
        break;
      case 's':
      case 'j':
        kp = keyns::Key::DOWN;
        break;
      case 'a':
      case 'h':
        kp = keyns::Key::LEFT;
        break;
      case 'd':
      case 'l':
        kp = keyns::Key::RIGHT;
        break;
      case '1':
        kp = keyns::Key::ONE;
        break;
      case '2':
        kp = keyns::Key::TWO;
        break;
      case '3':
        kp = keyns::Key::THREE;
        break;
      case '4':
        kp = keyns::Key::FOUR;
        break;
      case '5':
        kp = keyns::Key::FIVE;
        break;
      case '6':
        kp = keyns::Key::SIX;
        break;
      case '7':
        kp = keyns::Key::SEVEN;
        break;
      case '8':
        kp = keyns::Key::EIGHT;
        break;
      case '9':
        kp = keyns::Key::NINE;
        break;
      case 'x':
        kp = keyns::Key::DELETE;
      case 'c':
        kp = keyns::Key::C;
        break;
      case 'r':
        kp = keyns::Key::R;
        break;
    }
  } else {
    kp = keyns::Key::NONE;
  }
  disable_raw_mode();
  key_press = kp;
}

keyns::Key KeyPress::get_key_press() { return key_press; }

int KeyPress::get_digit() {
  if (key_press == keyns::Key::ONE)
    return 1;
  else if (key_press == keyns::Key::TWO)
    return 2;
  else if (key_press == keyns::Key::THREE)
    return 3;
  else if (key_press == keyns::Key::FOUR)
    return 4;
  else if (key_press == keyns::Key::FIVE)
    return 5;
  else if (key_press == keyns::Key::SIX)
    return 6;
  else if (key_press == keyns::Key::SEVEN)
    return 7;
  else if (key_press == keyns::Key::EIGHT)
    return 8;
  else if (key_press == keyns::Key::NINE)
    return 9;
  else
    return 0;
}

char KeyPress::get_char() {
  if (key_press == keyns::Key::C)
    return 'c';
  else if (key_press == keyns::Key::R)
    return 'r';
  else
    return ' ';
}
