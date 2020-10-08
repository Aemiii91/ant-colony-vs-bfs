# include "wGraph.h"

using namespace std;
    
wGraph::wGraph(vector<nodeData> &nodeList, vector<edgeData> &edgeLise){ 
  populateGraph();
  printGraph();
}
void wGraph::printGraph(){ 

 auto vpair = vertices(g);

boost::property_map<adjGraph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight_t(), g);

 for(auto iter=vpair.first; iter!=vpair.second; iter++) {
    std::cout << "vertex " << *iter << std::endl;
  }

  auto epair = edges(g);
  for(auto iter=epair.first; iter!=epair.second; iter++) {
    std::cout << "edge " << source(*iter, g) << " - " << target(*iter, g)<< " " << EdgeWeightMap[*iter]  << std::endl;
  } 
};

void wGraph::populateGraph(){
    for (nodeData node : nodeList){ 
        SV v = add_vertex(node.id, g);
    }

    for (edgeData edge : edgeList){
        SE e = boost::add_edge(edge.dist.first, edge.dist.second, {edge.weight}, g).first;
    }
    printGraph();
};

