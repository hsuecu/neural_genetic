/*
model create nodes 
create connections

then use pointers to setup
*/

#include <iostream>
#include <random>

class Node;

extern std::mt19937 mt;
extern std::uniform_real_distribution<float> dist;

class Connections
{
public:
    int connId;
    Node * from;
    Node * to;
    float weight;
    Connections(Node * _from, Node * to, float _weight);
    static float random(); 
    void mutate();
};