#pragma once

#include <map>
#include <vector>

enum Direction {
  UP = 'U',
  RIGHT = 'R',
  DOWN = 'D',
  LEFT = 'L',
};

class Point {
 public:
  int x;
  int y;

  bool operator<(const Point& point) const {
    return this->x == point.x ? this->y < point.y : this->x < point.x;
  }
};

struct WireInstr {
  Direction direction;
  int value;
};

struct WireContext {
  int number;
  std::vector<WireInstr> instrs;
};

struct GridMark {
  int wire_num;
  int num_steps;
};

struct Intersection {
  Point point;
  int num_steps;
  GridMark marks[2];
};

typedef std::map<Point, std::vector<GridMark>> Grid;
typedef std::vector<Intersection> Tracklist;