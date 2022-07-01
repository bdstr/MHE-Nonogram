
#ifndef NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHMS_FUNCTIONS_H
#define NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHMS_FUNCTIONS_H

#include <tuple>
#include "../nonogram.h"
#include "../utils/random.h"
#include "genetic_algorithm.h"

class GeneticAlgorithmsFunctions {
public:

  static constexpr auto splice = [](std::vector<bool> a, int start, int end) {
	std::vector<bool> result;
	for (int i = start; i < end; i++) {
	  result.push_back(a[i]);
	}
	return result;
  };

  static constexpr auto concat = [](std::vector<bool> a, std::vector<bool> b) {
	std::vector<bool> result;
	for (int i = 0; i < a.size(); i++) {
	  result.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++) {
	  result.push_back(b[i]);
	}
	return result;
  };

  static constexpr auto single_point_crossover = [](Nonogram a, Nonogram b) {
	Random<int> random;
	int point = random.generate(0, a.seed.size() - 1);
	auto seed_a_first = splice(a.seed, 0, point);
	auto seed_a_second = splice(a.seed, point, a.seed.size());
	auto seed_b_first = splice(b.seed, 0, point);
	auto seed_b_second = splice(b.seed, point, b.seed.size());

	auto child_a_seed = concat(seed_a_first, seed_b_second);
	auto child_b_seed = concat(seed_b_first, seed_a_second);
	Nonogram child_a(a.width, a.height, child_a_seed);
	Nonogram child_b(a.width, a.height, child_b_seed);
	return std::make_tuple(child_a, child_b);
  };

  static constexpr auto double_point_crossover = [](Nonogram a, Nonogram b) {
	Random<int> random;
	int first_point = random.generate(0, a.seed.size() - 2);
	int second_point = random.generate(first_point + 1, a.seed.size() - 1);

	auto seed_a_first = splice(a.seed, 0, first_point);
	auto seed_a_second = splice(a.seed, first_point, second_point);
	auto seed_a_third = splice(a.seed, second_point, a.seed.size());
	auto seed_b_first = splice(b.seed, 0, first_point);
	auto seed_b_second = splice(b.seed, first_point, second_point);
	auto seed_b_third = splice(b.seed, second_point, b.seed.size());

	auto child_a_seed = concat(concat(seed_a_first, seed_b_second), seed_a_third);
	auto child_b_seed = concat(concat(seed_b_first, seed_a_second), seed_b_third);
	Nonogram child_a(a.width, a.height, child_a_seed);
	Nonogram child_b(a.width, a.height, child_b_seed);
	return std::make_tuple(child_a, child_b);
  };

  static constexpr auto mutate_single_bit = [](Nonogram nonogram) {
	Random<int> random;
	int index = random.generate(0, nonogram.seed.size() - 1);
	auto mutated_seed = nonogram.seed;
	mutated_seed[index] = !mutated_seed[index];
	return Nonogram(nonogram.width, nonogram.height, mutated_seed);
  };

  static constexpr auto mutate_scramble = [](Nonogram nonogram) {
	Random<int> random;
	int start_index = random.generate(0, nonogram.seed.size() - 2);
	int end_index = random.generate(start_index, nonogram.seed.size() - 1);
	auto mutated_seed = nonogram.seed;
	for (int i = start_index; i < end_index; i++) {
	  if (random.generate(0, 1) == 0) {
		mutated_seed[i] = false;
	  } else {
		mutated_seed[i] = true;
	  }
	}

	return Nonogram(nonogram.width, nonogram.height, mutated_seed);
  };

  static constexpr auto terminate_condition_iterations = [](GeneticAlgorithm ga) {
	return ga.current_iteration >= ga.max_iterations;
  };

  static constexpr auto
	  terminate_condition_score_has_not_changed = [](GeneticAlgorithm ga) {
	int score = ga.average_scores[ga.average_scores.size() - 1];
	for (int i = 1; i < ga.max_iterations; i++) {
	  if (ga.average_scores[ga.average_scores.size() - 1 - i] != score) {
		return false;
	  }
	}
	return true;
  };
};

#endif //NONOGRAM_CPP_ALGORITHMS_GENETIC_ALGORITHMS_FUNCTIONS_H
