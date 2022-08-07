#include <unistd.h>


#include "Genetic.hpp"

#include "main.hpp"

#include <random>
#include <iostream>
#include <signal.h>

#define ONE_SEC 1000000
#define POPULATION_SIZE 120

using std::cout;

std::mt19937 mt;
std::uniform_real_distribution<float> dist;

std::vector<std::vector<float>> image_data;
std::vector<std::vector<float>> target_data;

float Genetic::fitnessFunction(Model *model, vector<vector<float>> &data, vector<vector<float>> &target)
{
    float ret = 0;

    for (int i = 0; i < data.size(); i++)
    {
        auto prediction = model->feedForward(data[i]);
        prediction[target[i].back()] = prediction[target[i].back()] - 1;
        for (int j = 0; j < prediction.size(); j++)
            ret += prediction[j] * prediction[j];
        prediction.clear();
    }

    return ret;
}

bool isInterrupted = false;

void while_keyboard_breaker(int signum)
{
    isInterrupted = true;
}

int main(int argc, const char **argv)
{
    std::cout << "Neural With Genetic Algorithm\n-----------------------------\n";
    usleep(ONE_SEC);

    load_csv_noheader("data.csv", image_data, ',');
    load_csv_noheader("target.csv", target_data, ',');

    std::cout << "Loaded data sets\n-----------------------------\n";
    usleep(ONE_SEC);

    CONNECTIONS_CLASS_RANDOM_INIT;

    Genetic genetic;

    int size = POPULATION_SIZE;

    for (int i = 0; i < size; i++)
    {
        genetic.Models.push_back({new Model(image_data[0].size(), {32, 32, 16}, 10), -1.0f});
        genetic.Models[i].first->generateDeepNetwork(false);
    }
    std::ofstream save;

    save.open("result.txt");
    long itr = 0;
    signal(SIGINT, while_keyboard_breaker);
    while (!isInterrupted)
    {
        save << ++itr << " " << genetic.Models.front().second << std::endl;
        genetic.fintessPopulate();
        for (int i = 0; i < size / 2; i++)
        {
            delete genetic.Models.back().first;
            genetic.Models.pop_back();
        }
        for (int i = 0; i < size / 2; i+=2)
        {
            auto ret = genetic.uniformCrossover(genetic.Models[i].first, genetic.Models[i+1].first);
            for (auto itr: ret)
            {
                genetic.Models.push_back({itr, -1.0f});
            }
        }
        for (int i = 0; i < size; i++)
        {
            genetic.mutation(genetic.Models[i].first);
        }
        if (genetic.Models.front().second < 10)
        {
            break;
        }
        cout << "\r working:" << itr << " score:" << genetic.Models.front().second;
        cout.flush();
    }
    cout << "\nExiting\n";
    save << "\nPredictions\n" << std::endl;

    float count=0;

    for (int i = 0; i < image_data.size(); i++)
    {
        auto itr = genetic.Models.front().first->feedForward(image_data[i]);
        vector<int> temp;
        for (int i = 0; i < itr.size(); i++)
        {
            if (itr[i] > 0.5)
            {
                temp.push_back(i);
                save << i << ',';
            }
        }
        save << "-> " << target_data[i].back() << '\n';
        if(temp.size() == 1)
        {
            if(temp.front() == target_data[i].back())
            {
                count += 1.0f;
            }
        }
    }
    save.close();
    cout << "Accuracy of:" << count / target_data.size() <<  '\n';

    save_model(genetic.Models.front().first, "final.bin");

    return EXIT_SUCCESS;
}
