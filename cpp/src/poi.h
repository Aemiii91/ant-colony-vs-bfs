#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "coords.h"

using namespace std;

struct poi {
    string name;
    double lattitude_radian;
    double longitude_radian;
    int num_links;
    string links;
    int num_categories;
    string categories;
};

class PoiImport {
public:
    void ImportPoi(fstream *fileStream);
    vector<poi> importedPoi;
private:
    string header[7];
};
