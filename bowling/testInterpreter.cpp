#include "Interpreter.hpp"

#include <gtest/gtest.h>

class InterpreterTest : public ::testing::Test {
public:
  Interpreter interpreter;
};

TEST_F(InterpreterTest, divideToNameAndRecord) {
  auto input = "Michael:X|7/|9-|X|-8|8/|-6|X|X|X||81";
  auto expectedResult = std::make_pair<std::string, std::string>(
      "Michael", "X|7/|9-|X|-8|8/|-6|X|X|X||81");
  ASSERT_EQ(expectedResult, interpreter.extractRecord(input));
}

TEST_F(InterpreterTest, allTens) {
  auto input = "Michael:X|X|X|";
  std::vector<int> expectedResult{10, 10, 10};
  ASSERT_EQ(expectedResult, interpreter.processLaneRecordToRolls(input));
}

TEST_F(InterpreterTest, strike) {
  auto input = "Michael:5/|1/";
  std::vector<int> expectedResult{5, 5, 1, 9};
  ASSERT_EQ(expectedResult, interpreter.processLaneRecordToRolls(input));
}

TEST_F(InterpreterTest, miss) {
  auto input = "Michael:9-|9-|";
  std::vector<int> expectedResult{9, 0, 9, 0};
  ASSERT_EQ(expectedResult, interpreter.processLaneRecordToRolls(input));
}

TEST_F(InterpreterTest, statusIsNoGame) {
  ASSERT_EQ("no game", interpreter.getGameStatus(""));
}

TEST_F(InterpreterTest, statusIsGameFinishedWithoutBonusBalls) {
  auto game = "Michael:9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||";
  ASSERT_EQ("game finished", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusIsGameFinishedWithBonusBallsAlmoustPerfectGame) {
  auto game = "Michael:9-|9-|9-|9-|9-|9-|9-|9-|9-|X||XX";
  ASSERT_EQ("game finished", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusIsGameFinishedWithBonusBallsWithSpare) {
  auto game = R"(Michael:9-|9-|9-|9-|9-|9-|9-|9-|9-|X||8/)";
  ASSERT_EQ("game finished", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusIsGameFinishedWithBonusBallsWithMiss) {
  auto game = R"(Michael:9-|9-|9-|9-|9-|9-|9-|9-|9-|X||7-)";
  ASSERT_EQ("game finished", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusIsGameFinishedWithBonusBalls) {
  auto game = R"(Michael:9-|9-|9-|9-|9-|9-|9-|9-|9-|X||34)";
  ASSERT_EQ("game finished", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusIsGameInProgress) {
  auto game = R"(Michael:9-|9-|9-|9-|)";
  ASSERT_EQ("game in progress", interpreter.getGameStatus(game));
}

TEST_F(InterpreterTest, statusForMultilineInputOneInProgressOneDone) {
  auto game = "Michael:X|7/|9-|X|-8|8/|-6|X|X|X||81\n"
              "Radek:9-|9-|9-|9-|9-|9-|9-|9-|9-|";
  ASSERT_EQ("game in progress", interpreter.getGameStatus(game));
}
