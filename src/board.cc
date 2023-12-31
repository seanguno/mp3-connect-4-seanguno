#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
  b.board[0][0] = DiskType::kEmpty;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("Invalid column.");
  }
  int row = 0;
  for (int i = Board::kBoardHeight - 1; i > -1; --i) {
    if (b.board[i][col] != DiskType::kEmpty) {
      row = i + 1;
      break;
    }
  }
  if (row == Board::kBoardHeight) {
    throw std::runtime_error("This column is full!");
  }
  
  b.board[row][col] = disk;
}



bool CheckHorizontal(Board& b, DiskType disk) {
  for (int row = 0; row < Board::kBoardHeight; ++row) {
    for (int col = 0; col < Board::kBoardWidth - 3; ++col) {
      if (b.board[row][col] == disk && b.board[row][col + 1] == disk && b.board[row][col + 2] == disk && b.board[row][col + 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool CheckVertical(Board& b, DiskType disk) {
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    for (int row = 0; row < Board::kBoardHeight - 3; ++row) {
      if (b.board[row][col] == disk && b.board[row + 1][col] == disk && b.board[row + 2][col] == disk && b.board[row + 3][col] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool CheckRightDiag(Board& b, DiskType disk) {
  for (int col = 0; col < Board::kBoardWidth - 3; ++col) {
    for (int row = 0; row < Board::kBoardHeight - 3; ++row) {
      if (b.board[row][col] == disk && b.board[row + 1][col + 1] == disk && b.board[row + 2][col + 2] == disk && b.board[row + 3][col + 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool CheckLeftDiag(Board& b, DiskType disk) {
  for (int col = Board::kBoardWidth - 1; col > 2; --col) {
    for (int row = 0; row < Board::kBoardHeight - 3; ++row) {
      if (b.board[row][col] == disk && b.board[row + 1][col - 1] == disk && b.board[row + 2][col - 2] == disk && b.board[row + 3][col - 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  switch (to_check) {
    case WinningDirection::kHorizontal:
      if (CheckHorizontal(b, disk)) {
        return true;
      }
      break;
    case WinningDirection::kVertical:
      if (CheckVertical(b, disk)) {
        return true;
      }
      break;
    case WinningDirection::kLeftDiag:
      if (CheckLeftDiag(b, disk)) {
        return true;
      }
      break;
    case WinningDirection::kRightDiag:
      if (CheckRightDiag(b, disk)) {
        return true;
      }
  }
  return false;
}

bool CheckForWinner(Board& b, DiskType disk) {
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if (row < 0 || row > Board::kBoardHeight - 1) {
    return false;
  }
  if (col < 0 || col > Board::kBoardWidth - 1) {
    return false;
  }
  return true;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
