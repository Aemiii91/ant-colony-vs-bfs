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
class wGraph {
    public:
        
        typedef boost::adjacency_list<boost::vecS, boost::vecS, 
                                        boost::undirectedS,
                                        nodeData,
                                        boost::property<boost::edge_weight_t, double>
                                     > adjGraph;
       
    typedef boost::graph_traits<adjGraph>::vertex_descriptor SV;
    typedef boost::graph_traits<adjGraph>::edge_descriptor SE;

        
        wGraph(){}; 
        wGraph(vector<nodeData>& nodeList, vector<edgeData>& edgeLise); 
        adjGraph g;
        void printGraph();          
        void populateGraph(vector<nodeData> &nodeList, vector<edgeData> &edgeLise); 
        void dijkstra(); 
    private: 
        vector<edgeData> edgeS;
        vector<nodeData> nodeS;
        
};


