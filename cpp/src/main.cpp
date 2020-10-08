#include <boost/graph/depth_first_search.hpp>
#include <ctime>
#include <iostream>
#include <random>

#include "graph/graph.h"
#include "poi.h"
#include "test.h"
using namespace std;
int main(int argc, char **argv) {
  std::cout << "testing opening of filestream" << std::endl;

  Graph g;
  g.ImFastLetMeShowYou();
  PoiImport imp;
  fstream fileStream;
  string filepath = argv[argc - 1];

  fileStream.open(filepath);

  if (fileStream.is_open()) {
    std::cout << "filestream is good, importing dataset" << std::endl;
    imp.ImportPoi(&fileStream);
    std::cout << "imported poi count: " << imp.importedPoi.size() << std::endl;
  } else {
    std::cout << "Something went wrong with opening the file" << std::endl;
  }

  return 0;
}
