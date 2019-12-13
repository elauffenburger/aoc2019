#ifndef problem_helpers_h
#define problem_helpers_h

#include <map>
#include <string>
#include <vector>

#include "types.h"

std::map<std::string, Node*>& build_graph(const std::vector<std::string>& lines);

int count_distances(const std::map<std::string, Node*>& graph);
int count_orbital_transfers_to(const std::map<std::string, Node*>& graph, std::string from, std::string to);

#endif