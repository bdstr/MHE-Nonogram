#include <tuple>
#include "tabu_algorithm.h"

TabuAlgorithm::TabuAlgorithm(Nonogram target) : target(target) {}

std::tuple<Nonogram, int> TabuAlgorithm::run(int iterations, int max_size) {
  Nonogram initial = Nonogram(this->target.width, this->target.height);

  std::vector<Nonogram> tabu_list;
  std::vector<Nonogram> previous_steps;
  previous_steps.push_back(initial);
  Nonogram best = initial;
  Nonogram candidate = initial;
  int i = 0;
  while (i < iterations && target.calculate_fitness_score(best) != target.get_max_score()
	  && previous_steps.size() > 0) {
	i += 1;
	std::vector<Nonogram> neighbors = candidate.get_neighbours();
	std::vector<Nonogram> valid_neighbors;
	for (auto &neighbor : neighbors) {
	  if (!is_nonogram_in_list(neighbor, tabu_list)) {
		valid_neighbors.push_back(neighbor);
	  }
	}

	tabu_list.push_back(candidate);
	if (!valid_neighbors.empty()) {
	  Nonogram best_local_candidate = valid_neighbors[0];
	  for (int i = 1; i < valid_neighbors.size(); i++) {
		if (target.calculate_fitness_score(valid_neighbors[i]) > target.calculate_fitness_score(best_local_candidate)) {
		  best_local_candidate = valid_neighbors[i];
		}
	  }

	  if (target.calculate_fitness_score(best_local_candidate) > target.calculate_fitness_score(best)) {
		previous_steps.push_back(candidate);
		best = best_local_candidate;
	  }
	  candidate = best_local_candidate;
	} else {
	  candidate = previous_steps.back();
	  previous_steps.erase(tabu_list.begin());
	}
  }
  return std::make_tuple(best, this->target.calculate_fitness_score(best));
}

bool TabuAlgorithm::is_nonogram_in_list(Nonogram nonogram, std::vector<Nonogram> tabu_list) {
  for (int i = 0; i < tabu_list.size(); i++) {
	if (nonogram == tabu_list[i]) {
	  return true;
	}
  }
  return false;
}
