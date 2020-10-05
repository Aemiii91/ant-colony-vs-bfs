#include <curl/curl.h>
#include <iostream>
#include "test.h"
#include "poi.h"
#include "openrouteapi.h"

using namespace std;



int main (int argc, char **argv) {
    curl_global_init(CURL_GLOBAL_ALL);
    OpenRouteApi openRoute;
    std::cout << openRoute.GetWalkingMatrix() << std::endl;
    curl_global_cleanup();
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
        std::cout << "POI FILE: Something went wrong with opening the file" << std::endl;
    }
    
    return 0;
}
