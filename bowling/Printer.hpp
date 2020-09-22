#pragma once

#include <string>

#include "Bowls.hpp"
#include "Interpreter.hpp"

class Printer {
public:
  std::string extractLaneName(const std::string &name);
  std::stringstream
  generateSummary(const std::map<std::string, std::string> &results);

  std::string summarizeLane(const std::string &lane);

  void printSummary(std::stringstream &input, std::ostream &output);

private:
  Interpreter interpreter;
};
