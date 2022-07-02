#include <iostream>
#include <tuple>
#include <any>
#include "nonogram.h"
#include "algorithms/hill_climbing_algorithm.h"
#include "algorithms/tabu_algorithm.h"
#include "algorithms/simulated_annealing_algorithm.h"
#include "algorithms/genetic_algorithm.h"
#include "utils/random.h"
#include "algorithms/genetic_algorithms_functions.h"
#include "utils/time_measure.h"
#include "algorithms/islands_genetic_algorithm.h"
//int main() {
//
//  auto hex_seed = (unsigned long long)(0x1555555);
//  Nonogram target(5, 5, hex_seed);
//  target.print();
//
//  TimeMeasure time_measure;

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

//  std::cout << "Genetic Algorithm" << std::endl;
//  GeneticAlgorithm genetic_algorithm(target,
//									 200,
//									 50,
//									 200,
//									 GeneticAlgorithmsFunctions::double_point_crossover,
//									 GeneticAlgorithmsFunctions::mutate_single_bit,
//									 GeneticAlgorithmsFunctions::terminate_condition_iterations);
//  time_measure.start();
//  std::tuple<Nonogram, int> ga_result = genetic_algorithm.run();
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(ga_result).print();
//  std::cout << "Score: " << get<1>(ga_result) << std::endl << std::endl;
//
//  std::cout << "Islands Genetic Algorithm" << std::endl;
//  IslandsGeneticAlgorithm islands_genetic_algorithm(5, 10, 5,
//													target,
//													200,
//													0,
//													200,
//													GeneticAlgorithmsFunctions::double_point_crossover,
//													GeneticAlgorithmsFunctions::mutate_single_bit,
//													GeneticAlgorithmsFunctions::terminate_condition_iterations);
//  time_measure.start();
//  std::tuple<Nonogram, int> island_ga_result = islands_genetic_algorithm.run(100);
//  std::cout << "Time: " << time_measure.stop() << "ms" << std::endl;
//  get<0>(island_ga_result).print();
//  std::cout << "Score: " << get<1>(island_ga_result) << std::endl << std::endl;
//
//  return 0;
//}


auto arg = [](int argc, char **argv, std::string name, auto default_value) -> decltype(default_value) {
  using namespace std;
  string paramname = "";
  any ret = default_value;
  for (auto argument : vector<string>(argv, argv + argc)) {
	if ((argument.size() > 0) && (argument[0] == '-')) {
	  if (paramname != "") {
		if (name == argument.substr(1))
		  ret = true;
	  }
	  paramname = argument.substr(1);
	} else if (name == paramname) {
	  if (std::is_same_v<decltype(default_value), int>)
		ret = stoi(argument);
	  else if (std::is_same_v<decltype(default_value), double>)
		ret = stod(argument);
	  else if (std::is_same_v<decltype(default_value), char>)
		ret = argument.at(0);
	  else if (std::is_same_v<decltype(default_value), bool>)
		ret = (argument == "true") || (argument == "1") || (argument == "yes");
	  else
		ret = argument;
	  paramname = "";
	}
  }
  return std::any_cast<decltype(default_value)>(ret);
};

int main(int argc, char **argv) {
  using namespace std;

//  auto hex_seed = arg(argc, argv, "target", (unsigned long long)(0x1555555));
  auto hex_seed = arg(argc, argv, "target", (unsigned long long)(0x87A988));
  auto width = arg(argc, argv, "width", 5);
  auto height = arg(argc, argv, "height", 5);

  auto iterations = arg(argc, argv, "iterations", 500);
  auto method = arg(argc, argv, "method", std::string("hillclimb_deterministic"));
  auto print_result = arg(argc, argv, "print_result", std::string("true"));

  auto tabu_size = arg(argc, argv, "tabu_size", 200);
  auto initial_temp = arg(argc, argv, "initial_temp", 20);
  auto tries_in_epoque = arg(argc, argv, "tries_in_epoque", 15);

  auto pop_size = arg(argc, argv, "pop_size", 500);
  auto crossover_p = arg(argc, argv, "crossover_p", 0.9);
  auto mutation_p = arg(argc, argv, "mutation_p", 10);

  auto islands_count = arg(argc, argv, "islands_count", 5);
  auto migration_speed = arg(argc, argv, "migration_speed", 10);
  auto migration_pause = arg(argc, argv, "migration_pause", 5);

  auto crossover_func_arg = arg(argc, argv, "crossover_func", std::string("single_point_crossover"));
  std::function< std::tuple<Nonogram, Nonogram>(Nonogram a, Nonogram b)> crossover_func;
  if (crossover_func_arg == "single_point_crossover") {
	crossover_func = GeneticAlgorithmsFunctions::single_point_crossover;
  } else if (crossover_func_arg == "double_point_crossover") {
	crossover_func = GeneticAlgorithmsFunctions::double_point_crossover;
  }

  auto mutation_func_arg = arg(argc, argv, "mutation_func", std::string("mutate_single_bit"));
  std::function<Nonogram(Nonogram)> mutation_func;
  if (mutation_func_arg == "mutate_single_bit") {
	mutation_func = GeneticAlgorithmsFunctions::mutate_single_bit;
  } else if (mutation_func_arg == "mutate_scramble") {
	mutation_func = GeneticAlgorithmsFunctions::mutate_scramble;
  }

  auto terminate_condition_arg = arg(argc, argv, "terminate_condition_func", std::string("terminate_iterations"));
  std::function<bool(GeneticAlgorithm ga)> terminate_condition_func;
  if (terminate_condition_arg == "terminate_iterations") {
	terminate_condition_func = GeneticAlgorithmsFunctions::terminate_condition_iterations;
  } else if (terminate_condition_arg == "terminate_score_not_changing") {
	terminate_condition_func = GeneticAlgorithmsFunctions::terminate_condition_score_has_not_changed;
  }

  cout << "Target:" << std::endl;
  Nonogram target(width, height, hex_seed);
  target.print();
  cout << std::endl;

  TimeMeasure time_measure;
  int best_score = 0;
  int time = 0;

  if (method == "hillclimb_deterministic") {
	HillClimbingAlgorithm hill_climbing_algorithm(target);
	std::cout << "Hill Climbing Deterministic Algorithm" << std::endl;
	time_measure.start();
	std::tuple<Nonogram, int> hca_deterministic_result = hill_climbing_algorithm.run_deterministic(iterations);
	time = time_measure.stop();
	best_score = get<1>(hca_deterministic_result);
	get<0>(hca_deterministic_result).print();
  } else if (method == "hillclimb_stochastic") {
	HillClimbingAlgorithm hill_climbing_algorithm(target);
	std::cout << "Hill Climbing Stochastic Algorithm" << std::endl;
	time_measure.start();
	std::tuple<Nonogram, int> hca_stochastic_result = hill_climbing_algorithm.run_stochastic(iterations);
	time = time_measure.stop();
	best_score = get<1>(hca_stochastic_result);
	get<0>(hca_stochastic_result).print();
  } else if (method == "tabu") {
	TabuAlgorithm tabu_algorithm(target);
	std::cout << "Tabu Algorithm" << std::endl;
	time_measure.start();
	std::tuple<Nonogram, int> tabu_result = tabu_algorithm.run(iterations, tabu_size);
	time = time_measure.stop();
	best_score = get<1>(tabu_result);
	get<0>(tabu_result).print();
  } else if (method == "simulated_annealing") {
	SimulatedAnnealingAlgorithm simulated_annealing_algorithm(target);
	std::cout << "Simulated Annealing Algorithm" << std::endl;
	time_measure.start();
	std::tuple<Nonogram, int> saa_result = simulated_annealing_algorithm.run(initial_temp, tries_in_epoque, iterations);
	time = time_measure.stop();
	best_score = get<1>(saa_result);
	get<0>(saa_result).print();
  } else if (method == "genetic_algorithm") {
	std::cout << "Genetic Algorithm" << std::endl;
	GeneticAlgorithm genetic_algorithm(target,
									   pop_size,
									   mutation_p,
									   iterations,
									   crossover_func,
									   mutation_func,
									   terminate_condition_func);
	time_measure.start();
	std::tuple<Nonogram, int> ga_result = genetic_algorithm.run();
	time = time_measure.stop();
	best_score = get<1>(ga_result);
	get<0>(ga_result).print();
  } else if (method == "island_genetic_algorithm") {
	std::cout << "Islands Genetic Algorithm" << std::endl;
	IslandsGeneticAlgorithm islands_genetic_algorithm(islands_count, migration_speed, migration_pause,
													  target,
													  pop_size,
													  mutation_p,
													  iterations,
													  crossover_func,
													  mutation_func,
													  terminate_condition_func);
	time_measure.start();
	std::tuple<Nonogram, int> islands_ga_result = islands_genetic_algorithm.run(iterations);
	time = time_measure.stop();
	best_score = get<1>(islands_ga_result);
	get<0>(islands_ga_result).print();
  } else {
	std::cerr << "unknown method" << std::endl;
  }

  if (print_result == "true") {
	std::cout << "Time: " << time << "ms" << std::endl;
	std::cout << "Score: " << best_score << std::endl << std::endl;
  }

  return best_score;
}
