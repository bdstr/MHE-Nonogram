//
// Created by marcin on 02.07.22.
//

#include "islands_genetic_algorithm.h"
IslandsGeneticAlgorithm::IslandsGeneticAlgorithm(int island_count,
												 int migration_speed,
												 int migration_pause,
												 Nonogram target,
												 int initial_population_size,
												 int mutation_chance_percent,
												 int max_iterations,
												 std::function<std::tuple<Nonogram, Nonogram>(Nonogram,
																							  Nonogram)> crossover_function,
												 std::function<Nonogram(Nonogram)> mutation_function,
												 std::function<bool(GeneticAlgorithm)> termination_function) : target(
	target) {

  this->island_count = island_count;
  this->migration_speed = migration_speed;
  this->migration_pause = migration_pause;

  for (int i = 0; i < island_count; i++) {
	GeneticAlgorithm island = GeneticAlgorithm(target,
											   initial_population_size,
											   mutation_chance_percent,
											   max_iterations,
											   crossover_function,
											   mutation_function,
											   termination_function);
	this->islands.push_back(island);
  }

}

std::tuple<Nonogram, int> IslandsGeneticAlgorithm::run(int iterations) {
  for (int i = 0; i < iterations; i++) {
	if (i % this->migration_pause == 0) {
	  this->migrate();
	}
	for (int x = 0; x < this->island_count; x++) {
	  this->islands[x].next_generation();
	  auto best = this->islands[x].find_best_child();
	  if (get<1>(best) == this->target.get_max_score()) {
		return std::make_tuple(get<0>(best), get<1>(best));
	  }
	}
  }

  return find_best_child();
}

void IslandsGeneticAlgorithm::migrate() {
  std::tuple<Nonogram, int> emigrant = this->islands[0].population_with_scores.front();
  for (int x = 0; x < this->migration_speed; x++) {
	for (int i = 0; i < this->island_count; i++) {
	  emigrant = this->islands[i].population_with_scores.front();
	  this->islands[i].population_with_scores.erase(this->islands[i].population_with_scores.begin());
	  this->islands[(i + 1) % this->island_count].population_with_scores.push_back(emigrant);
	}
  }

}
std::tuple<Nonogram, int> IslandsGeneticAlgorithm::find_best_child() {
  std::tuple<Nonogram, int> best = this->islands[0].find_best_child();
  for (int x = 1; x < this->island_count; x++) {
	auto candidate = this->islands[x].find_best_child();
	if (get<1>(candidate) > get<1>(best)) {
	  best = candidate;
	}
  }
  return best;
}
