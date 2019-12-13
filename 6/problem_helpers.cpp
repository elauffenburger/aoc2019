#include <exception>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "helpers.h"
#include "types.h"

std::map<std::string, Node*>& build_graph(
    const std::vector<std::string>& lines) {
  auto graph = new std::map<std::string, Node*>();

  for (auto it = lines.begin(); it != lines.end(); it++) {
    auto entry = *it;
    auto entry_parts = std::vector<std::string>();
    split_str(entry, entry_parts, ')');

    Node* parent = nullptr;

    auto node_name = entry_parts[1];
    auto parent_name = entry_parts[0];

    auto existing_parent = graph->find(parent_name);
    if (existing_parent != graph->end()) {
      parent = (*existing_parent).second;
    } else {
      parent = new Node{.name = parent_name, .parent = nullptr};
      graph->emplace(parent_name, parent);
    }

    auto existing_node = graph->find(node_name);
    if (existing_node != graph->end()) {
      auto node = existing_node->second;
      node->parent = parent;
    } else {
      auto node = new Node{.name = node_name, .parent = parent};
      graph->emplace(node_name, node);
    }
  }

  return *graph;
}

int count_distance(Node* from, Node* to) {
  auto distance = 0;

  auto node = from;
  while (node != to) {
    distance++;
    node = node->parent;
  }

  return distance;
}

int count_distances(const std::map<std::string, Node*>& graph) {
  auto num_orbits = 0;

  for (auto it = graph.begin(); it != graph.end(); it++) {
    auto entry = *it;

    auto node = entry.second->parent;
    num_orbits += count_distance(node, nullptr);
  }

  return num_orbits;
}

Node* find_common_ancestor(const std::map<std::string, Node*>& graph,
                           Node* node1, Node* node2) {
  auto ancestors = std::set<std::string>();

  Node* visited_node = node1->parent;
  while (visited_node != nullptr) {
    ancestors.insert(visited_node->name);

    visited_node = visited_node->parent;
  }

  visited_node = node2->parent;
  while (visited_node != nullptr) {
    auto entry = ancestors.find(visited_node->name);
    if (entry != ancestors.end()) {
      return graph.find(*entry)->second;
    }

    visited_node = visited_node->parent;
  }

  return nullptr;
}

int count_orbital_transfers_to(const std::map<std::string, Node*>& graph,
                               std::string from, std::string to) {
  auto from_node = graph.find(from)->second;
  auto to_node = graph.find(to)->second;

  auto common_ancestor_node = find_common_ancestor(graph, from_node, to_node);

  return count_distance(from_node->parent, common_ancestor_node) +
         count_distance(to_node->parent, common_ancestor_node);
}