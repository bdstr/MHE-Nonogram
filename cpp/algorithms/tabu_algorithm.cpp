#include <tuple>
#include "tabu_algorithm.h"

TabuAlgorithm::TabuAlgorithm(Nonogram target) : target(target) {}

std::tuple<Nonogram, int> TabuAlgorithm::run(int iterations, int max_size) {
  Nonogram initial = Nonogram(this->target.width, this->target.height);

  Nonogram best = initial;
  Nonogram best_candidate = initial;
  std::vector<Nonogram> tabu_list{initial};

  for (int i = 0; i < iterations; i++) {
	std::vector<Nonogram> neighbours = best_candidate.get_neighbours();
	best_candidate = neighbours[0];
	for (auto &candidate : neighbours) {
	  tabu_list.push_back(candidate);
	  if ((std::find(tabu_list.begin(), tabu_list.end(), candidate) != tabu_list.end()) &&
		  this->target.calculate_fitness_score(candidate) > this->target.calculate_fitness_score(best_candidate)) {
		best_candidate = candidate;
	  }
	}
	if (this->target.calculate_fitness_score(best_candidate) > this->target.calculate_fitness_score(best)) {
	  best = best_candidate;
	}

	if (tabu_list.size() > max_size) {
	  tabu_list.erase(tabu_list.begin());
	}
  }

  return std::make_tuple(best, this->target.calculate_fitness_score(best));
}
