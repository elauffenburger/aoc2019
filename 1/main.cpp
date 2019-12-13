#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "helpers.h"

const char *INPUT_FILE_NAME = "input";

int calc_fuel(int mass, int acc)
{
    auto partial_fuel = std::floor(mass / 3) - 2;
    if (partial_fuel <= 0)
    {
        return acc;
    }

    return calc_fuel(partial_fuel, acc + partial_fuel);
}

int main(int argc, char **argv)
{
    auto file_lines = read_file((char *)INPUT_FILE_NAME);

    std::cout << "read " << file_lines->size() << " lines" << std::endl;

    auto masses = map<std::string, int>(file_lines, [](std::string line) { return atoi(line.c_str()); });
    auto required_fuel_entries = map<int, int>(masses, [](int mass) { return calc_fuel(mass, 0); });

    auto result = sum<int>(required_fuel_entries);

    std::cout << "Result: " << result << std::endl;
}