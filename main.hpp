#include <bits/stdc++.h>

#ifndef main_hpp
#define main_hpp

#define NO_ERROR_CSV 0
#define NO_SAVE_ERROR 0


long get_line_count(std::ifstream &file)
{
    long ret = 0;
    std::string temp;
    while(std::getline(file, temp))
    {
        if(temp.size() > 0)++ret;
    }
    return ret;
}

int load_csv_noheader(std::string filename, std::vector<std::vector<float>>&data, char delimiter)
{
    int line_count = 0, col_count=0;
    std::string line, t;
    std::ifstream file;

    file.open(filename);

    line_count = get_line_count(file);
    file.clear();
    file.seekg(0, std::ios::beg);

    std::getline(file, line);

    col_count = std::count(line.begin(), line.end(), delimiter) + 1;

    data = std::vector<std::vector<float>>(line_count, std::vector<float>());

    int i=0;
    std::stringstream ss;
    do{
        ss.clear();
        ss.str(line);
        while(std::getline(ss, t, ','))
        {
            data[i].push_back(std::stof(t));
        }
        i++;
        std::getline(file, line);
    }while(i<line_count);

    file.close();

    return NO_ERROR_CSV;
}

int save_model(Model * m, std::string filename)
{
    std::ofstream save;
    save.open(filename, std::ios::out | std::ios::binary);

    save << "# model save file !! don't edit\n";
    save << "input_dim:" << m->inputDim << '\n';
    save << "hidden_dim_size:" << m->hiddenDim.size() << '\n';
    for(auto itr: m->hiddenDim) save << itr << '\n';
    save << "output_dim:" << m->outputDim << '\n';
    save << "conn_weight:\n";
    for(auto itr: m->Conns) save << itr->connId << ':' << itr->weight << '\n';

    return NO_SAVE_ERROR;
}

#endif /*main_hpp*/