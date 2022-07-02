#include <iostream>
#include <tuple>
#include "nonogram.h"
#include "algorithms/hill_climbing_algorithm.h"
#include "algorithms/tabu_algorithm.h"
#include "algorithms/simulated_annealing_algorithm.h"
#include "algorithms/genetic_algorithm.h"
#include "utils/random.h"
#include "algorithms/genetic_algorithms_functions.h"
#include "utils/time_measure.h"
#include "algorithms/islands_genetic_algorithm.h"
int main() {

  auto hex_seed = (unsigned long long)(0x1555555);
  Nonogram target(5, 5, hex_seed);
  target.print();

  TimeMeasure time_measure;

//  HillClimbingAlgorithm hill_climbing_algorithm(target);
//  TabuAlgorithm tabu_algorithm(target);
//  SimulatedAnnealingAlgorithm simulated_annealing_algorithm(target);
//
//  std::cout << "Hill Climbing Deterministic Algorithm" << std::endl;
//  time_measure.start();
//  std::tuple<Nonogram, int> hca_deterministic_result = hill_climbing_algorithm.run_deterministic(1000);
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(hca_deterministic_result).print();
//  std::cout << "Score: " << get<1>(hca_deterministic_result) << std::endl << std::endl;
//
//  std::cout << "Hill Climbing Stochastic Algorithm" << std::endl;
//  time_measure.start();
//  std::tuple<Nonogram, int> hca_stochastic_result = hill_climbing_algorithm.run_stochastic(1000);
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(hca_stochastic_result).print();
//  std::cout << "Score: " << get<1>(hca_stochastic_result) << std::endl << std::endl;
//
//  std::cout << "Tabu Algorithm" << std::endl;
//  time_measure.start();
//  std::tuple<Nonogram, int> tabu_result = tabu_algorithm.run(1000, 300);
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(tabu_result).print();
//  std::cout << "Score: " << get<1>(tabu_result) << std::endl << std::endl;
//
//  std::cout << "Simulated Annealing Algorithm" << std::endl;
//  time_measure.start();
//  std::tuple<Nonogram, int> saa_result = simulated_annealing_algorithm.run(100, 10, 1000);
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(saa_result).print();
//  std::cout << "Score: " << get<1>(saa_result) << std::endl << std::endl;

  std::cout << "Genetic Algorithm" << std::endl;
  GeneticAlgorithm genetic_algorithm(target,
									 200,
									 50,
									 200,
									 GeneticAlgorithmsFunctions::double_point_crossover,
									 GeneticAlgorithmsFunctions::mutate_single_bit,
									 GeneticAlgorithmsFunctions::terminate_condition_iterations);
  time_measure.start();
  std::tuple<Nonogram, int> ga_result = genetic_algorithm.run();
  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
  get<0>(ga_result).print();
  std::cout << "Score: " << get<1>(ga_result) << std::endl << std::endl;

  std::cout << "Islands Genetic Algorithm" << std::endl;
  IslandsGeneticAlgorithm islands_genetic_algorithm(5, 10, 5,
													target,
													200,
													0,
													200,
													GeneticAlgorithmsFunctions::double_point_crossover,
													GeneticAlgorithmsFunctions::mutate_single_bit,
													GeneticAlgorithmsFunctions::terminate_condition_iterations);
  time_measure.start();
  std::tuple<Nonogram, int> island_ga_result = islands_genetic_algorithm.run(100);
  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
  get<0>(island_ga_result).print();
  std::cout << "Score: " << get<1>(island_ga_result) << std::endl << std::endl;

  return 0;
}
