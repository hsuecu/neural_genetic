#include "model.hpp"
#include <iostream>
using std::cout;
using std::endl;

////////////////////////////////////////// NODE

Model::Node::Node(int li, int ni) {
    layerId = li;
    nodeId = ni;
}
Model::Node::engage() {
    
}

////////////////////////////////////////// MODEL

Model::Model(int idim, vector<int> hdim, int odim) {
    cout << "Model made" << endl;
}