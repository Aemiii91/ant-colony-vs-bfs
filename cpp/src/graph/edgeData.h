# include <string>
# include <vector>

using namespace std;
typedef pair<int, int> Pair;

class edgeData {
public: 

    edgeData();
    edgeData(double w) {weight = w;}
    edgeData(int from, int to, double w) {
        dist = Pair(from, to); 
        weight = w;
    } 
    Pair dist;
    double weight;
};
