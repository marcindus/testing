#include "Interpreter.hpp"
#include <iostream>
#include <regex>

std::pair<std::string, std::string>
Interpreter::extractRecord(const std::string& input) {
  std::string first, second;
  std::string *output = &first;
  for (const auto &ch : input) {
    if (ch == ':') {
      output = &second;
    } else {
      output->push_back(ch);
    }
  }
  return std::make_pair(first, second);
}

std::vector<int> Interpreter::processLaneRecordToRolls(const std::string& input) {
  std::vector<int> result;
  for (const auto &ch : input) {
    switch (ch) {
    case 'X':
      result.push_back(10);
      break;
    case '/':
      if (not result.empty()) {
        int completition = 10 - result.back();
        result.push_back(completition);
      }
      break;
    case '-':
      result.push_back(0);
      break;
    case '|':
      break;
    default:
      if (std::isdigit(ch)) {
        result.push_back((ch - '0'));
      };
    }
  }
  return result;
}

std::string Interpreter::getGameStatus(const std::string& lane) {
  if (lane.empty())
    return "no game";
  if (isFinished(lane))
    return "game finished";
  return "game in progress";
}

bool Interpreter::isFinished(const std::string& lane) {
  std::vector<std::string> lines = getVector(lane);

  auto isSingleGamerFinished = [&](std::string lane) {
    auto match =
        [&lane](const std::pair<std::string, std::string> &regex) -> bool {
      std::regex re(regex.second);
      std::smatch match;
      return std::regex_search(lane, match, re) && match.size() > 1;
    };
    try {
      return std::any_of(begin(matchFinish), end(matchFinish), match);
    } catch (std::regex_error &e) {
      std::cerr << "Syntax error in the regular expression";
    }
    return false;
  };

  return std::all_of(begin(lines), end(lines), isSingleGamerFinished);
}

std::vector<std::string> Interpreter::getVector(const std::string &lane) const {
  std::stringstream stream(lane);
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(stream, line)) {
    lines.emplace_back(line);
  }
  return lines;
}
