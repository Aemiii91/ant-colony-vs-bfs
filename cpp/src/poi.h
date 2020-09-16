#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

struct poi {
    std::string name;
    double lattitude_radian;
    double longitude_radian;
    int num_links;
    std::string links;
    int num_categories;
    std::string categories;
};

class PoiImport {
public:
    void ImportPoi(fstream *fileStream);
    vector<poi> importedPoi;
private:
    string header[7];
};