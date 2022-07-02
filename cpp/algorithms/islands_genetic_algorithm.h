//
// Created by marcin on 02.07.22.
//

#ifndef NONOGRAM_CPP_ALGORITHMS_ISLANDS_GENETIC_ALGORITHM_H
#define NONOGRAM_CPP_ALGORITHMS_ISLANDS_GENETIC_ALGORITHM_H

#include <functional>
#include "../nonogram.h"
#include "genetic_algorithm.h"

class IslandsGeneticAlgorithm {
public:
  IslandsGeneticAlgorithm(int island_count,
						  int migration_speed,
						  int migration_pause,
						  Nonogram target,
						  int initial_population_size,
						  int mutation_chance_percent,
						  int max_iterations,
						  std::function<std::tuple<Nonogram, Nonogram>(Nonogram,
																	   Nonogram)> crossover_function,
						  std::function<Nonogram(Nonogram)> mutation_function,
						  std::function<bool(GeneticAlgorithm)> termination_function);
  std::tuple<Nonogram, int> run(int iterations);
  void migrate();

private:
  std::vector<GeneticAlgorithm> islands;
  int island_count;
  int migration_speed;

  int migration_pause;
  Nonogram target;
  std::tuple<Nonogram, int> find_best_child();
};

#endif //NONOGRAM_CPP_ALGORITHMS_ISLANDS_GENETIC_ALGORITHM_H
