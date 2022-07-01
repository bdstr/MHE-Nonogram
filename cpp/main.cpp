#include <iostream>
#include <tuple>
#include "nonogram.h"
#include "algorithms/hill_climbing_algorithm.h"
#include "algorithms/tabu_algorithm.h"
#include "algorithms/simulated_annealing_algorithm.h"
#include "algorithms/genetic_algorithm.h"
int main() {

  auto hex_seed = (unsigned long long)(0x1555555);
  Nonogram target(5, 5, hex_seed);
  target.print();

  HillClimbingAlgorithm hill_climbing_algorithm(target);
  TabuAlgorithm tabu_algorithm(target);
  SimulatedAnnealingAlgorithm simulated_annealing_algorithm(target);
  GeneticAlgorithm genetic_algorithm(target);

  auto singlePointCrossoverFunction = [](Nonogram a, Nonogram b) {
	Random<int> random;
	int point = random.generate(0, a.width - 1);
	Nonogram child(a.width, a.height);
	for (int i = 0; i < a.width; i++) {
	  for (int j = 0; j < a.height; j++) {
		if (i < point) {
		  child.set_cell(i, j, a.get_cell(i, j));
		} else {
		  child.set_cell(i, j, b.get_cell(i, j));
		}
	  }
	}
	return child;
  };

//  std::cout << "Hill Climbing Deterministic Algorithm" << std::endl;
//  std::tuple<Nonogram, int> hca_deterministic_result = hill_climbing_algorithm.run_deterministic(1000);
//  get<0>(hca_deterministic_result).print();
//  std::cout << "Score: " << get<1>(hca_deterministic_result) << std::endl << std::endl;
//
//  std::cout << "Hill Climbing Stochastic Algorithm" << std::endl;
//  std::tuple<Nonogram, int> hca_stochastic_result = hill_climbing_algorithm.run_stochastic(1000);
//  get<0>(hca_stochastic_result).print();
//  std::cout << "Score: " << get<1>(hca_stochastic_result) << std::endl << std::endl;
//
//  std::cout << "Tabu Algorithm" << std::endl;
//  std::tuple<Nonogram, int> tabu_result = tabu_algorithm.run(1000, 300);
//  get<0>(tabu_result).print();
//  std::cout << "Score: " << get<1>(tabu_result) << std::endl << std::endl;
//
//  std::cout << "Simulated Annealing Algorithm" << std::endl;
//  std::tuple<Nonogram, int> saa_result = simulated_annealing_algorithm.run(100, 10, 1000);
//  get<0>(saa_result).print();
//  std::cout << "Score: " << get<1>(saa_result) << std::endl << std::endl;

  std::cout << "Genetic Algorithm" << std::endl;
  genetic_algorithm.run(100);
//  get<0>(ga_result).print();
//  std::cout << "Score: " << get<1>(ga_result) << std::endl << std::endl;

  return 0;
}
