#include "Model.hpp"
#include <algorithm>
/*
    1. make population
    2. make cross over
    3. make mutation
    4. make fitness
*/

/*
random_issue    Reference: https://docs.microsoft.com/en-us/events/goingnative-2013/rand-considered-harmful
crossover       Reference: https://www.sciencedirect.com/topics/computer-science/point-crossover
crossover       Reference: https://ictactjournals.in/paper/IJSC_V6_I1_paper_4_pp_1083_1092.pdf
*/

/*
Model has two chromosome: under mutation
    1. Node gene
        node can be enabled or disabled
    2. Connection gene
        connection weight can be changed
        totaly or slightly
*/

using std::vector;
using std::pair;

extern std::vector<std::vector<float>> image_data;
extern std::vector<std::vector<float>> target_data;

class Genetic
{
public:
    vector<pair<Model *, float>> Models;

    vector<Model*> singlePointCrossover(Model * parent1, Model * parent2);
    vector<Model*> multiPointCrossover(Model * parent1, Model * parent2);
    vector<Model*> uniformCrossover(Model * parent1, Model * parent2);
    void mutation(Model * model);
    static float fitnessFunction(Model * model, vector<vector<float>>&data, vector<vector<float>>&target); // override
    void fintessPopulate();
};