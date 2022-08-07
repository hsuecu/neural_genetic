#include "Node.hpp"
#include <cmath>

Node::Node(int _layerId, int _nodeId)
{
    layerId = _layerId;
    nodeId = _nodeId;
    enabled = true;
}

void Node::engage()
{
    if(enabled == false) return;
    if (layerId != 0)
    {
        output = sigmoid(inputSum);
        //std::cout << output << ' ' << inputSum << '\n';
    }
    for(int i = 0; i < outconns.size(); i++)
    {
        outconns[i]->to->inputSum += output * outconns[i]->weight;
        //std::cout << output * outconns[i]->weight  << ' ' << outconns[i]->to->inputSum<< '\n';
    }
}

float Node::sigmoid(float x)
{
    return (1 / (1 + powf(M_E, -4.9*x)));
}