// The implementation of the Board.h file
#include "Board.h"
#include "Tile.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
// default constructor

// constructor called
Board::Board(int width, int height, int mines) {
  board_width = width;
  board_height = height;
  size = new Tile[width * height];
  place_mine(mines);

  update_counts();
}

void Board::place_mine(int mines) {
  srand((unsigned)time(NULL));

  // now placing the mines
  // chose a random index and replace it -1  as a mine
  // repeat this process until we have placed all the mines
  //  use the rand function to generate a random number

  for (int i = 0; i < mines; i++) {
    // chose a random index and replace it  with -1  as a mine
    int index = rand() % (board_width * board_height);
    if (size[index].get_value() != 8) {
      size[index].set_value(8);
    } else {
      mines++;
    }
  }
}
void Board::update_counts() {
  // update the counts for the tiles
  // using a for loop to go through the tiles
  for (int i = 0; i < board_width * board_height; i++) {

    // if the tile is a mine

    //     // converting one demisional array into two dimensional array
    if (size[i].get_value() == 8) {
      int row = i / board_width;
      int column = i % board_width;
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          int adj_row = row + x;
          int adj_col = column + y;
          if (adj_row >= 0 && adj_row < board_height && adj_col >= 0 &&
              adj_col < board_width) {
            int adj_index = adj_row * board_width + adj_col;
            if (size[adj_index].get_value() != 8) {
              size[adj_index].set_value(size[adj_index].get_value() + 1);
            }
          }
        }
      }
    }
  }
}
// reveal the tile at the given index
void Board::reveal(int x, int y) {

  for (int i = 0; i < board_width * board_height; i++) {
    int row = i / board_width;
    int column = i % board_width;
    if (row == x && column == y) {
      // check if the tile is a mine
      if (size[i].get_value() == 8) {
        for (int i = 0; i < board_width * board_height; i++) {
          // reveal all the tiles
          size[i].set_revealed(true);
          set_lost(true);
        }

      } else {
        size[i].set_revealed(true);
        revealed_count++;
      }
    }
  }
}
void Board::get_count(int count) { revealed_count = count; }
void Board::set_lost(bool check) { has_lost = check; }

// return true if the tile at the given index is a mine

// displaying the board pattern
void Board::print() {
  int row = 0;
  std::cout << "  ";
  for (int j = 0; j < board_width; j++) {
    std::cout << "  " << j << " ";
  }
  std::cout << std::endl;
  std::cout << "  ";
  for (int j = 0; j < board_width; j++) {
    std::cout << "|---";
  }
  std::cout << "|" << std::endl;
  std::cout << row << " ";
  for (int i = 0; i < board_width * board_height; i++) {

    if (i % board_width == board_width - 1) {
      row++;
      std::cout << "| ";
      size[i].display();
      std::cout << " ";
      std::cout << "|\n";
      std::cout << "  ";
      for (int j = 0; j < board_width; j++) {
        std::cout << "|---";
      }
      std::cout << "|" << std::endl;
      if (row != board_height) {
        std::cout << row << " ";
      }
    } else {

      std::cout << "| ";
      size[i].display();
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}
