#include <tuple>
#include "genetic_algorithm.h"
#include "../utils/random.h"

GeneticAlgorithm::GeneticAlgorithm(Nonogram target) : target(target) {}

std::tuple<Nonogram, int> GeneticAlgorithm::run(int population_size) {
  std::vector<Nonogram> population = generate_population(population_size);
  std::vector<std::tuple<Nonogram, int>> population_with_scores = score_population(population);

  int i = 0;
  while (i++ < 100) {
	std::vector<Nonogram> parents = select_population(population_with_scores);

//  	krzyzowanie (grupowanie parami, 1."grupowanie punktowe" dzielenie seeda randomowo na 2 czesci, tworzenie nowych seedow z polaczen tych 2 czesci
//  									2."grupowanie dwu-punktowe" dzielenie seeda randomowo na 3 czesci, tworzenie nowych seedow z zamiany na krzyż zewnętrznych czesci)
//  	mutacja
//		ocena + nowa populacja
  }
  return std::make_tuple(get<0>(population_with_scores[0]), get<1>(population_with_scores[0]));
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
