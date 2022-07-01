#include <tuple>
#include "genetic_algorithm.h"
#include "../utils/random.h"

GeneticAlgorithm::GeneticAlgorithm(Nonogram target,
								   int initial_population_size,
								   int mutation_chance_percent,
								   int max_iterations,
								   std::function<std::tuple<Nonogram, Nonogram>(Nonogram a,
																				Nonogram b)> crossover_function,
								   std::function<Nonogram(Nonogram nonogram)> mutation_function,
								   std::function<bool(GeneticAlgorithm ga)> termination_function)
	: target(target), initial_population_size(initial_population_size),
	  mutation_chance_percent(mutation_chance_percent), max_iterations(max_iterations),
	  crossover_function(crossover_function), mutation_function(mutation_function),
	  termination_function(termination_function) {}

std::tuple<Nonogram, int> GeneticAlgorithm::run() {
  std::vector<Nonogram> population = generate_population(initial_population_size);
  std::vector<std::tuple<Nonogram, int>> population_with_scores = score_population(population);
  this->average_scores.push_back(calculate_average_population_score(population_with_scores));

  this->current_iteration = 0;
  while (!termination_function(*this)) {
	std::vector<Nonogram> parents = this->select_population(population_with_scores);
	std::vector<Nonogram> children = this->crossover_population(parents);
	children = this->mutate_population(children);
	population_with_scores = score_population(children);

	this->average_scores.push_back(calculate_average_population_score(population_with_scores));

//	int population_score = calculate_average_population_score(population_with_scores);
//	int best_score = get<1>(find_best_child(population_with_scores));
//	std::cout << "Population score: " << population_score << "  best: " << best_score << std::endl;

	this->current_iteration++;
  }
  return find_best_child(population_with_scores);
}

std::vector<Nonogram> GeneticAlgorithm::generate_population(int size) {
  std::vector<Nonogram> population;
  for (int i = 0; i < size; i++) {
	population.push_back(Nonogram(this->target.width, this->target.height));
  }
  return population;
}

std::vector<std::tuple<Nonogram, int>> GeneticAlgorithm::score_population(std::vector<Nonogram> population) {
  std::vector<std::tuple<Nonogram, int>> population_with_scores;
  for (int i = 0; i < population.size(); i++) {
	population_with_scores.push_back(std::make_tuple(population[i],
													 this->target.calculate_fitness_score(population[i])));
  }
  return population_with_scores;
}

std::vector<Nonogram> GeneticAlgorithm::select_population(std::vector<std::tuple<Nonogram, int>> scored_population) {
  Random<int> random;
  std::vector<Nonogram> selected_population;

  for (int i = 0; i < scored_population.size(); i++) {
	int idx1 = random.generate(0, scored_population.size() - 1);
	int idx2 = random.generate(0, scored_population.size() - 1);
	if (get<1>(scored_population[idx1]) > get<1>(scored_population[idx2]))
	  selected_population.push_back(get<0>(scored_population[idx1]));
	else {
	  selected_population.push_back(get<0>(scored_population[idx2]));
	}
  }

  return selected_population;
}

std::vector<Nonogram> GeneticAlgorithm::crossover_population(std::vector<Nonogram> population) {
  std::vector<Nonogram> children;
  for (int i = 0; i < population.size(); i += 2) {
	auto children_tuple = crossover_function(population[i], population[i + 1]);
	children.push_back(get<0>(children_tuple));
	children.push_back(get<1>(children_tuple));
  }
  return children;
}

std::vector<Nonogram> GeneticAlgorithm::mutate_population(std::vector<Nonogram> population) {
  Random<int> random;
  std::vector<Nonogram> mutated_population;
  for (int i = 0; i < population.size(); i++) {
	if (random.generate(0, 100) < this->mutation_chance_percent) {
	  mutated_population.push_back(this->mutation_function(population[i]));
	} else {
	  mutated_population.push_back(population[i]);
	}
  }
  return mutated_population;
}

int GeneticAlgorithm::calculate_average_population_score(std::vector<std::tuple<Nonogram, int>> scored_population) {
  int sum = 0;
  for (int i = 0; i < scored_population.size(); i++) {
	sum += get<1>(scored_population[i]);
  }
  return sum / scored_population.size();
}

std::tuple<Nonogram, int> GeneticAlgorithm::find_best_child(std::vector<std::tuple<Nonogram, int>> scored_population) {
  Nonogram best = get<0>(scored_population[0]);
  int best_score = get<1>(scored_population[0]);
  for (int i = 1; i < scored_population.size(); i++) {
	if (get<1>(scored_population[i]) > best_score) {
	  best = get<0>(scored_population[i]);
	  best_score = get<1>(scored_population[i]);
	}
  }
  return std::make_tuple(best, best_score);
}
