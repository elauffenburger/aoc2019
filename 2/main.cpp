#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "helpers.h"

const char *INPUT_FILE_NAME = "input";
const int TARGET_RESULT = 19690720;

enum OPCODE
{
    // add
    OP_ADD = 1,

    // mult
    OP_MUL = 2,

    // halt
    OP_HLT = 99
};

void set_noun_and_verb(std::vector<int> &program, int noun, int verb)
{
    program.at(1) = noun;
    program.at(2) = verb;
}

void run_program(std::vector<int>& program)
{
    auto pc = 0;

    auto opcode = program.at(pc);
    while (opcode != OP_HLT)
    {
        auto param1_addr = program.at(pc + 1);
        auto param2_addr = program.at(pc + 2);
        auto result_addr = program.at(pc + 3);

        auto param1 = program.at(param1_addr);
        auto param2 = program.at(param2_addr);

        auto result = -1;
        switch (opcode)
        {
        case OP_ADD:
            result = param1 + param2;
            break;

        case OP_MUL:
            result = param1 * param2;
            break;
        }

        program.at(result_addr) = result;

        pc += 4;
        opcode = program.at(pc);
    }
}

int main(int argc, char **argv)
{
    auto file_lines = read_file((char *)INPUT_FILE_NAME);
    std::cout << "read " << file_lines->size() << " lines" << std::endl;

    auto input = file_lines->at(0);

    auto program_strs = std::vector<std::string>();
    split_str(input, program_strs, ',');

    for (auto noun = 0; noun < 100; noun++)
    {
        for (auto verb = 0; verb < 100; verb++)
        {
            try
            {
                auto program = map<std::string, int>(program_strs, [](std::string ch) { return atoi(ch.c_str()); });
                set_noun_and_verb(*program, noun, verb);
                run_program(*program);

                auto result = program->at(0);
                if (result == TARGET_RESULT)
                {
                    std::cout << "(noun, verb) = (" << noun << ", " << verb << ") for result " << TARGET_RESULT << std::endl;
                    exit(0);
                }
            }
            catch (std::exception e)
            {
            }
        }
    }

    std::cout << "no match found :(" << std::endl;
}