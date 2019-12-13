#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "helpers.h"

std::vector<std::string> *read_file(char *file_name)
{
    auto results = new std::vector<std::string>();
    auto file = std::ifstream(file_name);

    std::string line;
    while (std::getline(file, line))
    {
        results->push_back(line);
    }

    return results;
}