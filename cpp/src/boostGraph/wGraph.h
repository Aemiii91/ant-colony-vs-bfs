# include <vector> 
# include <algorithm>
# include <string>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include "./nodeData.h"
#include "./edgeData.h"
using namespace std;

using adjGraph = boost::adjacency_list<boost::vecS, boost::vecS, 
                                boost::directedS,
                                nodeData,
                                boost::property<boost::edge_weight_t, double>
                                >;
using SV = boost::graph_traits<adjGraph>::vertex_descriptor;
using SE = boost::graph_traits<adjGraph>::edge_descriptor;
class wGraph {
    public:  
        wGraph(){}; 
        wGraph(vector<nodeData>& nodeList, vector<edgeData>& edgeLise); 
        adjGraph g;
        
        vector<nodeData> nodeList;
        vector<edgeData> edgeList; 
        void printGraph();          
        void populateGraph(); 
        void dijkstra(); 
    private: 
        vector<edgeData> edgeS;
        vector<nodeData> nodeS;
        
};


