
#ifndef NONOGRAM_CPP_NONOGRAM_H
#define NONOGRAM_CPP_NONOGRAM_H

#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include <cmath>
#include <numeric>

class Nonogram {
public:
  int width;
  int height;
  std::vector<std::vector<int>> hints_vertical;
  std::vector<std::vector<int>> hints_horizontal;
  std::vector<bool> seed;

  Nonogram(int Width, int Height);
  Nonogram(int Width, int Height, std::vector<bool> Seed);
  Nonogram(int Width, int Height, unsigned long long int Seed);

  std::vector<Nonogram> get_neighbours();
  int calculate_fitness_score(Nonogram candidate);
  int get_max_score();
  void print();
  bool operator==(const Nonogram &Rhs) const;
  bool operator!=(const Nonogram &Rhs) const;

private:
  int max_score = 0;

  std::vector<bool> number_to_seed(unsigned long long hex);
  void calculate_hints();
  int calculate_groups_content_score(std::vector<int> self_line, std::vector<int> candidate_line);
};

#endif //NONOGRAM_CPP_NONOGRAM_H