#include <iostream>
#include "test.h"
#include "poi.h"
#include "boostGraph/wGraph.h"
#include <boost/graph/depth_first_search.hpp>


using namespace std;
int main (int argc, char **argv) {
    std::cout << "testing opening of filestream" << std::endl; 
    wGraph graph;
    for (int i = 0; i < 10; ++i) {
        nodeData temp("1");
        graph.nodeList.push_back(temp);
        edgeData ed(i, (rand() % 9), 12 );
        graph.edgeList.push_back(ed);
    }  
    graph.populateGraph();  


    PoiImport imp;
    fstream fileStream;
    string filepath = argv[argc-1];

    fileStream.open(filepath);
    
    if(fileStream.is_open()) {
        std::cout << "filestream is good, importing dataset" << std::endl;
        imp.ImportPoi(&fileStream);
        std::cout << "imported poi count: " << imp.importedPoi.size() << std::endl;
    }
    else {

        std::cout << "Something went wrong with opening the file" << std::endl;
    }
     
    return 0;
}
