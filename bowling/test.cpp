#include "bowling.hpp"

#include <gtest/gtest.h>

class BowlingParser : public ::testing::Test {
public:
  Interpreter interpreter;
};


struct TestData
{
    TestData(std::vector<int> left_, std::vector<int> right_, std::vector<int> result_)
        : left{left_}, right{right_}, result{result_} {};

    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> result;
};

class Merge : public ::testing::TestWithParam<TestData>
{
};

TEST_P(Merge, ShouldMergeArrays)
{
    EXPECT_EQ(test_merge(GetParam().left, GetParam().right), GetParam().result);
}

INSTANTIATE_TEST_SUITE_P(MergeTest,
                         Merge,
                         ::testing::Values(TestData({1}, {1}, {1, 1}),
                                           TestData({1, 2, 3}, {4, 5, 6}, {1, 2, 3, 4, 5, 6}),
                                           TestData({2, 5, 7, 8}, {2, 4, 7, 12, 32}, {2, 2, 4, 5, 7, 7, 8, 12, 32}),
                                           TestData({}, {}, {})));

X|X|X|X|X|X|X|X|X|X||XX Total score == 10 frames x 30 == 300

9-|9-|9-|9-|9-|9-|9-|9-|9-|9-|| Total score == 10 frames x 9 == 90

5/|5/|5/|5/|5/|5/|5/|5/|5/|5/||5 Total score == 10 frames x 15 == 150

X|7/|9-|X|-8|8/|-6|X|X|X||81 Total score == 167

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
#include "Bowls.hpp"

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void rollMany(int n, int pins, Bowls &game) {
  for (int i = 0; i < n; ++i) {
    game.roll(pins);
  }
}

void rollSpare(Bowls &game) {
  game.roll(5);
  game.roll(5);
}

class BowlingTest : public ::testing::Test {
public:
  Bowls game;
};

TEST_F(BowlingTest, gutterGame) {
  rollMany(20, 0, game);
  ASSERT_EQ(0, game.score());
}

TEST_F(BowlingTest, allOnes) {
  rollMany(20, 1, game);
  ASSERT_EQ(20, game.score());
}

TEST_F(BowlingTest, oneSpare) {
  rollSpare(game);
  game.roll(3);
  rollMany(17, 0, game);
  ASSERT_EQ(16, game.score());
}

TEST_F(BowlingTest, oneStrike) {
  game.roll(10); // strike
  game.roll(3);
  game.roll(4);
  rollMany(16, 0, game);
  ASSERT_EQ(24, game.score());
}

