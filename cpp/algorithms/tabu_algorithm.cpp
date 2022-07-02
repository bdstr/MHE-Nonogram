#include <tuple>
#include "tabu_algorithm.h"

TabuAlgorithm::TabuAlgorithm(Nonogram target) : target(target) {}

std::tuple<Nonogram, int> TabuAlgorithm::run(int iterations, int max_size) {
  Nonogram initial = Nonogram(this->target.width, this->target.height);

  Nonogram best = initial;
  Nonogram best_candidate = initial;
  std::vector<Nonogram> tabu_list{initial};
  std::vector<Nonogram> previous_steps{initial};

  for (int i = 0; i < iterations && !previous_steps.empty(); i++) {
	std::vector<Nonogram> neighbours = best_candidate.get_neighbours();
	bool was_changed = false;
	best_candidate = neighbours[0];
	for (auto &candidate : neighbours) {
	  if (!is_nonogram_in_list(candidate, tabu_list) &&
		  this->target.calculate_fitness_score(candidate) > this->target.calculate_fitness_score(best_candidate)) {
		best_candidate = candidate;
		was_changed = true;
	  }
	}

	if (!was_changed) {
	  best_candidate = previous_steps.back();
	  previous_steps.pop_back();
	} else if (this->target.calculate_fitness_score(best_candidate) > this->target.calculate_fitness_score(best)) {
	  best = best_candidate;
	  tabu_list.push_back(best_candidate);
	  previous_steps.push_back(best_candidate);
	} else {
	  previous_steps.push_back(best_candidate);
	}

	if (tabu_list.size() > max_size) {
	  tabu_list.erase(tabu_list.begin());
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
