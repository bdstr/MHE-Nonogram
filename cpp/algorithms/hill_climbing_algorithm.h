
#ifndef NONOGRAM_CPP_HILL_CLIMBING_ALGORITHM_H
#define NONOGRAM_CPP_HILL_CLIMBING_ALGORITHM_H

static const double WEIGHTED_EXPONENT = 1.2;
#include "../nonogram.h"

class HillClimbingAlgorithm {
public:
  HillClimbingAlgorithm(Nonogram target);

  std::tuple<Nonogram, int> run_deterministic(int iterations);
  std::tuple<Nonogram, int> run_stochastic(int iterations);
private:
  Nonogram target;

  std::tuple<Nonogram, int> find_best_neighbour(std::vector<Nonogram> neighbours);
  std::tuple<Nonogram, int> find_weighted_random_best_neighbour(std::vector<Nonogram> neighbours);

};

#endif //NONOGRAM_CPP_HILL_CLIMBING_ALGORITHM_H
