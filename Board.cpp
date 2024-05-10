#include "Board.h"
#include <array>
#include <cstdlib>
#include <iostream>

Board::Board() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      board[i][j] = 0; // intiliazing with 0
    }
  }
  place_mines();
}
void Board::place_mines() {
  srand(static_cast<unsigned>(time(nullptr)));

  int rem_mines = mine_count;
  while (rem_mines > 0) {
    int x = rand() % 8;
    int y = rand() % 8;
    if (board[x][y] == 0) {
      board[x][y] = 1;
      rem_mines--;
    }
  }
}

void Board::print() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (board[i][j] == 1) {
        std::cout << " "
                  << "1";

      } else {
        std::cout << " "
                  << "0";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
