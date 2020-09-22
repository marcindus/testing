#pragma once

#include <array>

class Bowling {
private:
  std::array<int, 21> rolls{};
  int currentRoll = 0;

public:
  void roll(int i);
  int score();
  bool isSpare(int firstInFrame) const;
  bool isStrike(int firstInFrame) const;
  int nextTwoBallsForStrike(int firstInFrame) const;
  int nextBallForSpare(int firstInFrame) const;
};