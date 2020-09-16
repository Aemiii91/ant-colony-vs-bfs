#include "poi.h"

using namespace std;

// should be fairly generic, input file could be parsed as an argument
// todo: write unit test
// furthermore, this has only been tested on https://www.kaggle.com/ehallmar/points-of-interest-poi-database
void PoiImport::ImportPoi(fstream *fileStream) {
    poi tempPoi;
    std::string::size_type sz;
    string line;
    string ignore;
    // retrieves headers first and then dumps them
    getline(*fileStream, ignore);

    while (getline(*fileStream, line)) {
        int i = 0;
        string stringarr[7];
        stringstream ss(line);
        while (ss >> std::ws) {
            string csvElement;

            if (ss.peek() == '"') {
                ss >> std::quoted(csvElement);
                string discard;
                getline(ss, discard, ',');
            } else {
                getline(ss, csvElement, ',');
            }
            stringarr[i] = csvElement;
            i++;
        }
        tempPoi.name = stringarr[0];
        tempPoi.lattitude_radian = stod(stringarr[1], &sz);
        tempPoi.longitude_radian = stod(stringarr[2], &sz);
        tempPoi.num_links = stoi(stringarr[3], &sz);
        tempPoi.links = stringarr[4];
        tempPoi.num_categories = stoi(stringarr[5], &sz);
        tempPoi.categories = stringarr[6];
        importedPoi.push_back(tempPoi);
    }
}