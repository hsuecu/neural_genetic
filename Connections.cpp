#include "Connections.hpp"


Connections::Connections(Node * _from, Node * _to, float _weight)
{
    from = _from;
    to = _to;
    weight = _weight;
}

void Connections::mutate()
{
    float t = dist(mt);
    if(-0.005 < t and t < 0.005)
    {
        // 1% of time mutate connection weight

        // (0.0025, 0.005) of (-1, 1) change of changing to new weight
        if(t > 0.0025)
        {
            weight = Connections::random();
        }
        else //(-0.005, 0.0025] of (-1, 1) change of slightly changing the weight
        {
            weight += Connections::random()/50;
        }
    }
}

float Connections::random()
{
    return dist(mt);
} 