/*
model create nodes
create connections

then use pointers to setup
*/

#include "Node.hpp"

#define CONNECTIONS_CLASS_RANDOM_INIT                        \
    do                                                       \
    {                                                        \
        std::random_device rd;                               \
        mt = std::mt19937(rd());                             \
        dist = std::uniform_real_distribution<float>(-1, 1); \
    } while (0);

class Model
{
public:
    int inputDim;
    int outputDim;
    vector<int> hiddenDim;
    int biasNodeId;

    vector<Node *> Nodes;
    vector<Connections *> Conns;

    Model(int _inputDim, vector<int> _hiddenDim, int _outputDim);
    void generateDeepNetwork(bool clonning);
    vector<float> feedForward(vector<float> in);
    Model * clone();
    ~Model();
};