#pragma once

#include "helpers.h"
#include "types.h"

bool has_double_digits(int password) {
  auto password_str = to_str(password);
  auto password_len = password_str.length();
  auto char_streaks = std::map<char, std::vector<int>>();

  auto last_char = ' ';
  auto char_streak_len = 0;
  for (auto i = 0; i < password_len; i++) {
    auto ch = password_str.at(i);
    auto continues_stream = ch == last_char;

    if (last_char == ' ') {
      last_char = ch;
      char_streak_len++;

      continue;
    }

    // If the current char breaks the streak, record the stream and reset the
    // count.
    if (!continues_stream) {
      auto entry = char_streaks.find(last_char);
      if (entry != char_streaks.end()) {
        (*entry).second.push_back(char_streak_len);
      } else {
        auto new_entry = std::vector<int>();
        new_entry.push_back(char_streak_len);

        char_streaks.emplace(last_char, new_entry);
      }

      char_streak_len = 0;
    }

    // If this is the last char, record the streak.
    if (i + 1 == password_len) {
      char_streak_len++;

      auto entry = char_streaks.find(ch);

      if (entry != char_streaks.end()) {
        (*entry).second.push_back(char_streak_len);
      } else {
        auto new_entry = std::vector<int>();
        new_entry.push_back(char_streak_len);

        char_streaks.emplace(ch, new_entry);
      }

      continue;
    }

    last_char = ch;
    char_streak_len++;
  }

  for (auto it = char_streaks.begin(); it != char_streaks.end(); it++) {
    auto has_two_streak = find<int>(
        (*it).second, [](int streak) { return streak == 2; }, nullptr);

    if (has_two_streak != nullptr) {
      return true;
    }
  }

  return false;
}

bool is_increasing(int password) {
  auto password_str = to_str(password);

  auto last_char = ' ';
  for (auto i = 0; i < password_str.length(); i++) {
    char ch = password_str.at(i);

    if (last_char == ' ') {
      last_char = ch;
      continue;
    }

    if ((int)ch < (int)last_char) {
      return false;
    }

    last_char = ch;
  }

  return true;
}

bool is_valid_password(int password) {
  return has_double_digits(password) && is_increasing(password);
}

template <typename Container>
void compute_passwords(int from, int to, Container& results) {
  for (auto i = from; i <= to; i++) {
    if (is_valid_password(i)) {
      results.push_back(i);
    }
  }
}