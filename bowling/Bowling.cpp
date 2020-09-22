#include "Bowling.hpp"

void Bowling::roll(int pins) { rolls[currentRoll++] = pins; }
int Bowling::score() {
  int score = 0;
  int firstInFrame = 0;
  for (int frame = 0; frame < 10; ++frame) {
    if (isStrike(firstInFrame)) { // strike
      score += 10 + nextTwoBallsForStrike(firstInFrame);
      firstInFrame++;
    } else if (isSpare(firstInFrame)) {
      score += 10 + nextBallForSpare(firstInFrame);
      firstInFrame += 2;
    } else {
      score += rolls[firstInFrame] + rolls[firstInFrame + 1];
      firstInFrame += 2;
    }
  }
  return score;
}
bool Bowling::isStrike(int firstInFrame) const {
  return rolls[firstInFrame] == 10;
}
bool Bowling::isSpare(int firstInFrame) const {
  return rolls[firstInFrame] + rolls[firstInFrame + 1] == 10;
}
int Bowling::nextTwoBallsForStrike(int firstInFrame) const {
  return rolls[firstInFrame+1] + rolls[firstInFrame + 2];
}
int Bowling::nextBallForSpare(int firstInFrame) const {
  return rolls[firstInFrame + 2];
}