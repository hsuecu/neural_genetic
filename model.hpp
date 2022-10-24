#include <vector>
#ifndef MODEL_HPP
#define MODEL_HPP
using std::vector;
class Model{
    class Connections;
    class Node {
        public:
        int layerId;
        int nodeId;
        float inputSum = 0;
        float output = 0;
        bool enabled = true;
        vector<Connections *> outConns;

        Node(int li, int ni);
        void engage();
        float sigmoid(float x);
    };
    class Connections{
        public:
        int connId;
        Node * from;
        Node * to;
        float weight;
        
        Connections(Node * f, Node * t, float w);
        static float random();
        void mutate();
    };

    public:
    int inputDim;
    int outputDim;
    vector<int> hiddenDim;
    int biasNodeId;

    vector<Node*> nodes;
    vector<Connections*> conns;

    int nextNodeId;
    int nextConnId;

    Model(int idim, vector<int> hdim, int odim);
    ~Model();
};
#endif