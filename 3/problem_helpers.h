#pragma once

#include <map>
#include <vector>

#include "helpers.h"
#include "types.h"

Grid *init_grid() { return new Grid(); }

std::vector<WireInstr> parse_wire_instrs(std::string wire_line) {
  auto results = std::vector<WireInstr>();

  auto parts = std::vector<std::string>();
  split_str(wire_line, parts, ',');

  for (auto it = parts.begin(); it != parts.end(); it++) {
    auto direction = (Direction)(*it)[0];
    auto value = atoi((*it).substr(1).c_str());

    results.push_back(WireInstr{.direction = direction, .value = value});
  }

  return results;
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

template <typename Action>
void exec_instr(Grid &grid, Tracklist &track_list, Point &cursor,
                const WireInstr &instr, bool track_intersections, int wire_num,
                int &num_steps, Action action) {
  // Iterate over the grid n-many times (according the to the instr value).
  for (auto i = 0; i < instr.value; i++) {
    num_steps++;

#ifdef DEBUG_CURSOR
    auto old_cursor = cursor;
#endif

    // Perform the action.
    action(cursor);

#ifdef DEBUG_CURSOR
    fprintf(stdout, "(%d, %d) -> (%d,%d)\n", old_cursor.x, old_cursor.y,
            cursor.x, cursor.y);
#endif

    auto entries = grid.find(cursor);
    auto has_entries = entries != grid.end();

    if (has_entries) {
#ifdef DEBUG
      fprintf(stdout, "found intersection at (%d, %d)\n", cursor.x, cursor.y);
#endif
      // Check if this space has been visited by a DIFFERENT wire.
      GridMark *existing_mark =
          find<GridMark>((*entries).second,
                         [&](const GridMark &grid_entry) {
                           return grid_entry.wire_num != wire_num;
                         },
                         nullptr);

      // If the grid was marked, we found an intersection!
      auto has_mark_from_diff_wire = existing_mark != nullptr;
      if (has_mark_from_diff_wire) {
        auto cloned_existing_mark = *existing_mark;
        auto new_mark = GridMark{.wire_num = wire_num, .num_steps = num_steps};

        // Mark the grid.
        grid.at(cursor).push_back(new_mark);

        // Track the intersection.
        if (track_intersections) {
          track_list.push_back(Intersection{
              .point = cursor,
              .marks = {cloned_existing_mark, new_mark},
          });
        }
      }

      continue;
    }

    // Mark the grid.
    auto new_entry = std::vector<GridMark>();
    new_entry.push_back(GridMark{.wire_num = wire_num, .num_steps = num_steps});

    grid.emplace(cursor, new_entry);
  }
}

void draw_wire(Grid &grid, Tracklist &track_list, Point &start,
               const WireContext &wire_context, bool track_intersections) {
  Point cursor = start;
  auto num_steps = 0;

  for (auto it = wire_context.instrs.begin(); it != wire_context.instrs.end();
       it++) {
    auto instr = *it;

    switch (instr.direction) {
      case UP:
        exec_instr(grid, track_list, cursor, instr, track_intersections,
                   wire_context.number, num_steps,
                   [](Point &cursor) { cursor.y++; });
        break;
      case RIGHT:
        exec_instr(grid, track_list, cursor, instr, track_intersections,
                   wire_context.number, num_steps,
                   [](Point &cursor) { cursor.x++; });
        break;
      case DOWN:
        exec_instr(grid, track_list, cursor, instr, track_intersections,
                   wire_context.number, num_steps,
                   [](Point &cursor) { cursor.y--; });
        break;
      case LEFT:
        exec_instr(grid, track_list, cursor, instr, track_intersections,
                   wire_context.number, num_steps,
                   [](Point &cursor) { cursor.x--; });
        break;
    }
  }

#ifdef DEBUG
  std::cout << std::endl;
#endif
}