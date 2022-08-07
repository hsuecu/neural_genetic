#include "Model.hpp"

Model::Model(int _inputDim, vector<int> _hiddenDim, int _outputDim)
{
    inputDim = _inputDim;
    for (auto itr : _hiddenDim)
        hiddenDim.push_back(itr);
    outputDim = _outputDim;
    biasNodeId = inputDim;

    int _node_counter = 0;
    //------------------------- Input Node --------------------------
    for (int i = 0; i < inputDim; i++)
    {
        Nodes.push_back(new Node(0, _node_counter++));
    }

    //--------------------------Bias Node----------------------------
    Nodes.push_back(new Node(0, _node_counter++));

    //-------------------------hidden Node---------------------------
    for (int l = 0; l < hiddenDim.size(); l++)
    {
        for (int i = 0; i < hiddenDim[l]; i++)
        {
            Nodes.push_back(new Node(l + 1, _node_counter++));
        }
    }

    //------------------------output Node-----------------------------
    for (int i = 0; i < outputDim; i++)
    {
        Nodes.push_back(new Node(hiddenDim.size() + 1, _node_counter++));
    }
}

void Model::generateDeepNetwork(bool clonning)
{
    int l=0;
    int total_layer = hiddenDim.size()+2; // n hidden 1 input 1 output
    int conn_counter =0  ;
    for(l = 0; l <= total_layer - 2; l++)
    {
        vector<Node *> fnode;
        vector<Node *> tnode;
        for(auto itr: Nodes)
        {
            if(itr->layerId == l) fnode.push_back(itr);
            if(itr->layerId == l+1) tnode.push_back(itr);
        }
        for(int i = 0; i < fnode.size(); i++)
        {
            for(int j = 0; j < tnode.size(); j++)
            {
                if(clonning) Conns.push_back(new Connections(fnode[i], tnode[j], 0.0f));
                else Conns.push_back(new Connections(fnode[i], tnode[j], Connections::random()));
                Conns.back()->connId = conn_counter++;
                fnode[i]->outconns.push_back(Conns.back());
            }
        }
    }
}

vector<float> Model::feedForward(vector<float> in)
{
    vector<float> out;

    for(int i = 0; i < in.size(); i++)
    {
        Nodes[i]->output = in[i];
        Nodes[i]->inputSum = in[i];
    }

    Nodes[biasNodeId]->output = 1;
    Nodes[biasNodeId]->inputSum = 1;

    for(auto itr: Nodes)
    {
        itr->engage();
    }
    int output_layer = hiddenDim.size() + 1; 
    for(int i = 0; i < Nodes.size(); i++)
    {
        if(Nodes[i]->layerId == output_layer) out.push_back(Nodes[i]->output);
    }
    for(auto itr: Nodes)
    {
        itr->inputSum = 0;
        itr->output = 0;
    }
    return out;
}

Model::~Model()
{
    for(int i = 0; i < Nodes.size(); i++)
        delete Nodes[i];
    for(int i = 0; i < Conns.size(); i++)
        delete Conns[i];
}

Model* Model::clone()
{
    Model * ret = new Model(inputDim, hiddenDim, outputDim);
    ret->generateDeepNetwork(true);
    for(int i = 0; i < Nodes.size(); i++)
    {
        ret->Nodes[i]->enabled = Nodes[i]->enabled;
    }
    for(int i = 0; i < Conns.size(); i++)
    {
        ret->Conns[i]->weight = Conns[i]->weight;
    }

    return ret;
}