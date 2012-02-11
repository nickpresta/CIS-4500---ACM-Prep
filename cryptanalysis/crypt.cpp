#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::string filter_text(std::string text) {
  std::string out;
  for (auto t_iter = text.begin(); t_iter != text.end(); ++t_iter) {
    if (std::isalpha(*t_iter)) {
      out += std::toupper(*t_iter);
    }
  }
  return out;
}

std::map<char, int> build_map(std::string text) {
  std::map<char, int> map;
  for (auto t_iter = text.begin(); t_iter != text.end(); ++t_iter) {
    auto it = map.find(*t_iter);
    if (it == map.end()) {
      map[*t_iter] = 1;
    } else {
      map[*t_iter] = it->second + 1;
    }
  }
  return map;
}

bool sort_freq(std::pair<char, int> first, std::pair<char, int> second) {
  return first.second < second.second;
}

bool sort_alpha(std::pair<char, int> first, std::pair<char, int> second) {
  if (first.second == second.second) {
    return first.first < second.first;
  }
  return true;
}

void output(std::map<char, int> map) {
  std::vector<std::pair<char, int>> vec(map.begin(), map.end());
  std::sort(vec.begin(), vec.end(), &sort_freq);
  std::sort(vec.begin(), vec.end(), &sort_alpha);
  for (auto v_iter = vec.begin(); v_iter != vec.end(); ++v_iter) {
    std::cout << v_iter->first << " " << v_iter->second << "\n";
  }
}

int main() {
  std::string num_lines_input;
  std::getline(std::cin, num_lines_input);
  int num_lines;
  std::stringstream(num_lines_input) >> num_lines;

  // Concat lines into single string
  std::string input;
  for (int i = 0; i < num_lines; ++i) {
    std::string line;
    std::getline(std::cin, line);
    input += line;
  }

  std::string text = filter_text(input);
  std::map<char, int> map = build_map(text);
  output(map);
}
