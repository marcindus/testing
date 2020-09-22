#include "Printer.hpp"

#include <gtest/gtest.h>

class PrinterTest : public ::testing::Test {
public:
  Printer printer;

  std::map<std::string, std::string> inputContent{
      {"lane1.txt", "Name1:X|4-|3\n"
                    "Name2:34|X|0-\n"
                    ":X|22|33"},
      {"lane2.txt", ""},
      {"lane3.txt", "Michael:X|7/|9-|X|-8|8/|-6|X|X|X||81\n"
                           "Radek:9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||"}};
};

TEST_F(PrinterTest, laneNameIsFormatedWithUpperLetterAndSpace) {
  auto input = "lane1.txt";
  auto expectedResult = "Lane 1";
  ASSERT_EQ(expectedResult, printer.extractLaneName(input));
}

TEST_F(PrinterTest, oneLaneRecordIsSummarizedWithResults) {
  auto input = inputContent["lane1.txt"];
  auto expectedOutput = "Name1 21\nName2 17\n24\n";
  ASSERT_EQ(expectedOutput, printer.summarizeLane(input));
}

TEST_F(PrinterTest, lanesArePrintedAndDecoratedPlusResults) {
  std::stringstream expectedOutput;
  expectedOutput << "### Lane 1: game in progress ###\n"
                    "Name1 21\n"
                    "Name2 17\n"
                    "24\n"
                    "### Lane 2: no game ###\n"
                    "### Lane 3: game finished ###\n"
                    "Michael 167\nRadek 90\n";
  ASSERT_EQ(expectedOutput.str(), printer.generateSummary(inputContent).str());
}

TEST_F(PrinterTest, SummaryIsDirectedToOutputStream) {
  std::stringstream input;
  input << "Hello World";
  std::ostringstream output;
  printer.printSummary(input, output);
  ASSERT_EQ(input.str(), output.str());
}
