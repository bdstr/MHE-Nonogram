//
// Created by marcin on 01.07.22.
//

#include <tuple>
#include "simulated_annealing_algorithm.h"
#include "../utils/random.h"

SimulatedAnnealingAlgorithm::SimulatedAnnealingAlgorithm(Nonogram target) : target(target) {}

std::tuple<Nonogram, int> SimulatedAnnealingAlgorithm::run(double initial_temp,
														   int number_of_tries_during_one_epoque,
														   int iterations) {
  Random<int> random_int;
  Random<double> random_double;

  double temp = initial_temp;
  Nonogram initial = Nonogram(this->target.width, this->target.height);

  int best_score = 0;
  Nonogram best = initial;

  for (int i = 0; i < iterations; i++) {
	std::vector<Nonogram> neighbours = best.get_neighbours();
	for (int n = 0; n < number_of_tries_during_one_epoque; n++) {
	  Nonogram candidate = neighbours[random_int.generate(0, neighbours.size() - 1)];
	  int fitness_score = this->target.calculate_fitness_score(candidate);
	  if (fitness_score > best_score) {
		best = candidate;
		best_score = fitness_score;
	  } else {
		double worse_candidate_overwrite_probability =
			exp(-(abs(this->target.calculate_fitness_score(best) - this->target.calculate_fitness_score(candidate))
				/ temp));
		double random_number = random_double.generate_floating(0, 1);
		if (random_number < worse_candidate_overwrite_probability) {
		  best = candidate;
		  best_score = fitness_score;
		}
	  }

	  if (best_score == this->target.get_max_score()) {
		return std::make_tuple(best, best_score);
	  }
	}
	temp = temp_annealing_func(temp);
  }

  return std::make_tuple(best, best_score);
}

double SimulatedAnnealingAlgorithm::temp_annealing_func(double current) {
  return current * 0.99;
}
