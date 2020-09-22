#include "Files.hpp"
#include "Printer.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

void printHelp();
void processGame(const std::string &directory, const std::string &file);
int main(int argc, char **argv) {
  switch (argc) {
  case 2: {
    if (argv[1] == std::string("-h")) {
      printHelp();
    } else {
      processGame(std::string(argv[1]), "");
    }
    break;
  }
  case 3: {
    processGame(std::string(argv[1]), std::string(argv[2]));
    break;
  }
  default:
    printHelp();
  }
}

void processGame(const std::string &directory, const std::string &file) {
  Files files(directory);
  Printer printer;

  auto results = files.readAllFiles();
  auto summary = printer.generateSummary(results);

  if (file.empty()) {
    printer.printSummary(summary, std::cout);
  } else {
    std::ofstream save;
    save.open(file, std::ios::out | std::ios::trunc);
    printer.printSummary(summary, save);
    save.close();
  }
}

void printHelp() {
  std::cout << "Here is Bowling game results processor\n"
               "Usage is ./bowling inputDirectory results.txt\n"
               "If you omit second parameter with file name,\n"
               "results will be printed on the screen\n";
}
