#include "Files.hpp"

#include <gtest/gtest.h>

class FilesTest : public ::testing::Test {
public:
  Files files{"../results"};

  std::map<std::string, std::string> expectedContent{
      {"lane1.txt", "Name1:X|4-|3\n"
                    "Name2:34|X|0-\n"
                    ":X|22|33"},
      {"lane2.txt", ""},
      {"lane3.txt", "Michael:X|7/|9-|X|-8|8/|-6|X|X|X||81\n"
                    "Radek:9-|9-|9-|9-|9-|9-|9-|9-|9-|9-||"}};
};

TEST_F(FilesTest, ListAllFilesInDirectory) {
  std::set<std::string> expectedResult;
  for (const auto &el : expectedContent)
    expectedResult.emplace(el.first);
  ASSERT_EQ(expectedResult, files.listResultsFiles());
}

TEST_F(FilesTest, ReadFileContent) {
  auto filename = "lane1.txt";
  auto fileContent = expectedContent[filename];
  ASSERT_EQ(fileContent, files.readFile(filename));
}

TEST_F(FilesTest, ReadAllFilescontent) {
  std::map<std::string, std::string> result = files.readAllFiles();
  ASSERT_EQ(expectedContent, result);
}
