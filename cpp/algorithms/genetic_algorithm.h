
#ifndef NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H
#define NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H

#include "../nonogram.h"
class GeneticAlgorithm {
public:
  GeneticAlgorithm(Nonogram target);
  std::tuple<Nonogram, int> run(int population_size);
private:
  Nonogram target;

  std::vector<Nonogram> generate_population(int size);
  std::vector<std::tuple<Nonogram, int>> score_population(std::vector<Nonogram> population);
  std::vector<Nonogram> select_population(std::vector<std::tuple<Nonogram, int>> scored_population);
};

#endif //NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H
