#include <tuple>
#include "hill_climbing_algorithm.h"
#include "../utils/random.h"

HillClimbingAlgorithm::HillClimbingAlgorithm(Nonogram Target) : target(Target) {}

std::tuple<Nonogram, int> HillClimbingAlgorithm::run_deterministic(int iterations) {
  iterations -= 1;
  Nonogram initial = Nonogram(this->target.width, this->target.height);
  std::vector<Nonogram> neighbours = initial.get_neighbours();
  std::tuple<Nonogram, int> best = this->find_best_neighbour(neighbours);
  for (int i = 0; i < iterations; i++) {
	std::vector<Nonogram> neighbours = get<0>(best).get_neighbours();
	std::tuple<Nonogram, int> candidate = this->find_best_neighbour(neighbours);
	if (get<1>(best) > get<1>(candidate)) {
	  return best;
	} else {
	  best = candidate;
	}
  }
  return best;
}

std::tuple<Nonogram, int> HillClimbingAlgorithm::run_stochastic(int iterations) {
  iterations -= 1;
  Nonogram initial = Nonogram(this->target.width, this->target.height);
  std::vector<Nonogram> neighbours = initial.get_neighbours();

  std::tuple<Nonogram, int> best = this->find_weighted_random_best_neighbour(neighbours);
  for (int i = 0; i < iterations; i++) {
	neighbours = get<0>(best).get_neighbours();
	std::tuple<Nonogram, int> candidate = this->find_weighted_random_best_neighbour(neighbours);
	if (get<1>(candidate) > get<1>(best)) {
	  best = candidate;
	}
  }
  return best;
}

std::tuple<Nonogram, int> HillClimbingAlgorithm::find_best_neighbour(std::vector<Nonogram> neighbours) {
  int best_score = 0;
  Nonogram best_neighbour = neighbours[0];
  for (int i = 1; i < neighbours.size(); i++) {
	int fitness_score = this->target.calculate_fitness_score(neighbours[i]);
	if (fitness_score > best_score) {
	  best_score = fitness_score;
	  best_neighbour = neighbours[i];
	}
  }

  return std::make_tuple(best_neighbour, best_score);
}

std::tuple<Nonogram, int> HillClimbingAlgorithm::find_weighted_random_best_neighbour(std::vector<Nonogram> neighbours) {
  Random<int> random;
  std::vector<int> weighted_indexes;
  for (int i = 0; i < neighbours.size(); i++) {
	int fitness_score = this->target.calculate_fitness_score(neighbours[i]);
	if (fitness_score == this->target.get_max_score()) {
	  return std::make_tuple(neighbours[i], fitness_score);
	}
	int number_of_duplicates = lround((double)pow((double)fitness_score, WEIGHTED_EXPONENT));
	for (int x = 0; x < number_of_duplicates; x++) {
	  weighted_indexes.push_back(i);
	}
  }

  int generated = random.generate(0, (int)weighted_indexes.size() - 1);
  Nonogram chosen_neighbour = neighbours[weighted_indexes[generated]];
  int chosen_score = this->target.calculate_fitness_score(chosen_neighbour);

  return std::make_tuple(chosen_neighbour, chosen_score);
}
