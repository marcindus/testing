#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

class Files {
public:
  Files(std::string resultsPath);
  std::set<std::string> listResultsFiles();
  std::string readFile(const std::string &filename);

  std::map<std::string, std::string> readAllFiles();

private:
  std::string resultsPath_;
};
