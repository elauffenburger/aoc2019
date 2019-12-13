#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <functional>

std::vector<std::string> *read_file(char *file_name);

template <typename TInput, typename TResult>
std::vector<TResult>* map(const std::vector<TInput>& iterable, std::function<TResult(TInput)> fn)
{
    auto results = new std::vector<TResult>();

    for (auto it = iterable.begin(); it != iterable.end(); it++)
    {
        results->push_back(fn(*it));
    }

    return results;
}

template <typename T>
T sum(const std::vector<T>& iterable)
{
    T result = 0;
    for (auto it = iterable.begin(); it != iterable.end(); it++)
    {
        result += *it;
    }

    return result;
}

template <class Container>
void split_str(const std::string &str, Container &result, char delimiter = ' ')
{
    std::stringstream stream(str);
    std::string token;
    while (std::getline(stream, token, ','))
    {
        result.push_back(token);
    }
}