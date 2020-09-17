#include <iostream>
#include "test.h"
#include "poi.h"

using namespace std;

int main (int argc, char **argv) {
    std::cout << "testing opening of filestream" << std::endl;
    
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
