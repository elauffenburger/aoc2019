#ifndef types_h
#define types_h

#include <string>

struct Node {
 public:
  std::string name;
  Node* parent;
};

#endif