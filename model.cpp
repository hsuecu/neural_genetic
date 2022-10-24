#include "model.hpp"
#include <iostream>
using std::cout;
using std::endl;
Model::Node::Node(int li, int ni) {
    layerId = li;
    nodeId = ni;
}

Model::Model(int idim, vector<int> hdim, int odim) {
    cout << "Model made" << endl;
}