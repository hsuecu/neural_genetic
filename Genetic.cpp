#include "Genetic.hpp"

bool sortByFitness(const pair<Model*, float> &a, const pair<Model*, float> &b)
{
    return (a.second < b.second);
}

vector<Model *> Genetic::singlePointCrossover(Model *parent1, Model *parent2)
{
    vector<Model *>  child;
    child.push_back(parent1->clone());
    child.push_back(parent2->clone());

    // 1st child half parent 1 half parent 2
    for(int i = 0;i < child[0]->Conns.size()/2; i++)
    {
        child[0]->Conns[i]->weight = parent2->Conns[i]->weight;
        child[1]->Conns[i]->weight = parent1->Conns[i]->weight;
    }

    return child;
}
vector<Model *> Genetic::multiPointCrossover(Model *parent1, Model *parent2)
{
    //
}
vector<Model *> Genetic::uniformCrossover(Model *parent1, Model *parent2)
{
    vector<Model *>  child;
    child.push_back(parent1->clone());
    child.push_back(parent2->clone());

    for(int i = 0; i < child[0]->Conns.size(); i++)
    {
        float t = Connections::random();
        if(t < 0)
        {
            child[0]->Conns[i]->weight = parent2->Conns[i]->weight;
        }
        else
        {
            child[1]->Conns[i]->weight = parent1->Conns[i]->weight;
        }
    }

    return child;
}
void Genetic::mutation(Model *model)
{
    for(auto itr: model->Conns)
    {
       itr->mutate();
    }
}
void Genetic::fintessPopulate()
{
    for (int i = 0; i < Models.size(); i++)
    {
        Models[i].second = Genetic::fitnessFunction(Models[i].first, image_data, target_data);
    }
    std::sort(Models.begin(), Models.end(), sortByFitness);
}