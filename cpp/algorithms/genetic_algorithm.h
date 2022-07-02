
#ifndef NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H
#define NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H

#include <functional>
#include "../nonogram.h"
class GeneticAlgorithm {
public:
  GeneticAlgorithm(Nonogram target,
				   int initial_population_size,
				   int mutation_chance_percent,
				   int max_iterations,
				   std::function<std::tuple<Nonogram, Nonogram>(Nonogram a, Nonogram b)> crossover_function,
				   std::function<Nonogram(Nonogram nonogram)> mutation_function,
				   std::function<bool(GeneticAlgorithm ga)> termination_function);
  std::tuple<Nonogram, int> run();

  void next_generation();
  std::tuple<Nonogram, int> find_best_child();

  int current_iteration;
  int max_iterations;
  std::vector<int> average_scores;
  std::vector<std::tuple<Nonogram, int>> population_with_scores;
private:
  Nonogram target;
  int initial_population_size;
  int mutation_chance_percent;

  std::function<std::tuple<Nonogram, Nonogram>(Nonogram a, Nonogram b)> crossover_function;
  std::function<Nonogram(Nonogram nonogram)> mutation_function;
  std::function<bool(GeneticAlgorithm ga)> termination_function;

  std::vector<Nonogram> generate_population(int size);
  std::vector<std::tuple<Nonogram, int>> score_population(std::vector<Nonogram> population);
  std::vector<Nonogram> select_population(std::vector<std::tuple<Nonogram, int>> scored_population);
  std::vector<Nonogram> crossover_population(std::vector<Nonogram> population);
  std::vector<Nonogram> mutate_population(std::vector<Nonogram> population);
  int calculate_average_population_score(std::vector<std::tuple<Nonogram,
																int>> scored_population);

};

#endif //NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHM_H
