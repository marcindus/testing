#pragma once

#include <array>

class Bowls {
private:
  std::array<int, 21> rolls{};
  int currentRoll = 0;

public:
  void roll(int i);
  int score();
  [[nodiscard]] bool isSpare(int firstInFrame) const;
  [[nodiscard]] bool isStrike(int firstInFrame) const;
  [[nodiscard]] int nextTwoBallsForStrike(int firstInFrame) const;
  [[nodiscard]] int nextBallForSpare(int firstInFrame) const;
};