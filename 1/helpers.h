#pragma once

#include <string>
#include <vector>
#include <functional>

std::vector<std::string> *read_file(char *file_name);

template <typename TInput, typename TResult>
std::vector<TResult> *map(std::vector<TInput> *iterable, std::function<TResult(TInput)> fn)
{
    auto results = new std::vector<TResult>();

    for (auto it = iterable->begin(); it != iterable->end(); it++)
    {
        results->push_back(fn(*it));
    }

    return results;
}

template <typename T>
T sum(std::vector<T> *iterable)
{
    T result = 0;
    for (auto it = iterable->begin(); it != iterable->end(); it++)
    {
        result += *it;
    }

    return result;
}