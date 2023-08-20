// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Test that invalid drops are thrown") {
  Board test;
  InitBoard(test);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, -1), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 100), std::runtime_error);
}

TEST_CASE("Test that attempting to drop into a full column is thrown") {

  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 0), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 0), std::runtime_error);

  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 3), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 3), std::runtime_error);

  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  DropDiskToBoard(test, DiskType::kPlayer1, 6);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer1, 6), std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(test, DiskType::kPlayer2, 6), std::runtime_error);
}

TEST_CASE("Check empty board for winners") {
  Board test;
  InitBoard(test);
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Test vertical winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  REQUIRE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
}


TEST_CASE("Test almost vertical winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
}

TEST_CASE("Test horizontal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 4);
  DropDiskToBoard(test, DiskType::kPlayer1, 5);
  REQUIRE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("Test almost horizontal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 4);
  DropDiskToBoard(test, DiskType::kPlayer1, 5);
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("Test right diagonal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  
  REQUIRE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Test almost right diagonal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 3);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Test left diagonal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  
  REQUIRE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kLeftDiag));
}

TEST_CASE("Test almost left diagonal winners") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kLeftDiag));
}

TEST_CASE("Test check for winner") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 3);
  DropDiskToBoard(test, DiskType::kPlayer2, 2);
  DropDiskToBoard(test, DiskType::kPlayer1, 2);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 1);
  DropDiskToBoard(test, DiskType::kPlayer1, 1);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer2, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  
  REQUIRE(CheckForWinner(test, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer2));
}

TEST_CASE("Testing BoardLocationInBounds") {
  Board test;
  InitBoard(test);
  REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(-1, 5));
  REQUIRE_FALSE(BoardLocationInBounds(5, -1));
  REQUIRE_FALSE(BoardLocationInBounds(100, -1));
  REQUIRE_FALSE(BoardLocationInBounds(100, 100));
  REQUIRE_FALSE(BoardLocationInBounds(100, 3));
  REQUIRE_FALSE(BoardLocationInBounds(3, 100));
  REQUIRE_FALSE(BoardLocationInBounds(-1, 100));
  REQUIRE(BoardLocationInBounds(3, 3));
}

TEST_CASE("Testing 3 on an edge") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  DropDiskToBoard(test, DiskType::kPlayer1, 0);
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer1));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer1, WinningDirection::kVertical));
  DropDiskToBoard(test, DiskType::kPlayer2, 6);
  DropDiskToBoard(test, DiskType::kPlayer2, 6);
  DropDiskToBoard(test, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(CheckForWinner(test, DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(test, DiskType::kPlayer2, WinningDirection::kVertical));
}

//TEST_CASE("Testing diagonal cases on the edge of the board") {
  //Board test;
  //InitBoard(test);
  //Drop
//}
/////////////////////////////////////////////////////////////////////////////////////////////
