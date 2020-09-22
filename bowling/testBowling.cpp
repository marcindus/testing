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

TEST_F(BowlingTest, perfectGame) {
  rollMany(12, 10, game);
  ASSERT_EQ(300, game.score());
}

TEST_F(BowlingTest, ten9s) {
  for (int i = 0; i < 10; ++i) {
    game.roll(9);
    game.roll(0);
  }
  ASSERT_EQ(90, game.score());
}

TEST_F(BowlingTest, allFiveAndExtraOne) {
  rollMany(21, 5, game);
  ASSERT_EQ(150, game.score());
}

TEST_F(BowlingTest, partialFrame) // 3-|X|4/|5
{
  game.roll(3);
  game.roll(0);
  game.roll(10);
  game.roll(4);
  game.roll(6);
  game.roll(5);
  ASSERT_EQ(43, game.score());
}