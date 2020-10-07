# include "wGraph.h"

using namespace std;
    
wGraph::wGraph(vector<nodeData> &nodeList, vector<edgeData> &edgeLise){ 
  populateGraph(nodeList, edgeLise);
  printGraph();
}
void wGraph::printGraph(){ 

 auto vpair = vertices(g);
  for(auto iter=vpair.first; iter!=vpair.second; iter++) {
    std::cout << "vertex " << *iter << std::endl;
  }

  auto epair = edges(g);
  for(auto iter=epair.first; iter!=epair.second; iter++) {
    std::cout << "edge " << source(*iter, g) << " - " << target(*iter, g)  << std::endl;
  }  
};

void wGraph::populateGraph(vector<nodeData> &nodeList, vector<edgeData> &edgeLise){
    //vector<SE> evlist;
    //vector<SV> svlist;

    for (nodeData node : nodeList){ 
        SV v = add_vertex(node.id, g);
    }

    for (edgeData edge : edgeLise){
        SE e = boost::add_edge(edge.dist.first, edge.dist.second, {1.2}, g).first;
    }
    printGraph();
};

