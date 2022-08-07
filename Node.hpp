/*
model create nodes 
create connections

then use pointers to setup
*/

#include <iostream>
#include <vector>


#include "Connections.hpp"

using std::vector;

class Node
{
public:
    float inputSum = 0;
    float output = 0;
    int layerId;
    int nodeId;
    bool enabled = true;
    vector<Connections *> outconns;

    Node(int _layerId, int _nodeId);
    void engage();
    float sigmoid(float x);
};