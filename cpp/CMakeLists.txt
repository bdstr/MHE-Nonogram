cmake_minimum_required(VERSION 3.22)
project(Nonogram)


set(CMAKE_CXX_FLAGS "-pthread")

set(CMAKE_CXX_STANDARD 23)
add_executable(Nonogram main.cpp nonogram.cpp nonogram.h nonogram.h algorithms/hill_climbing_algorithm.cpp algorithms/hill_climbing_algorithm.h utils/random.h utils/time_measure.h algorithms/tabu_algorithm.cpp algorithms/tabu_algorithm.h algorithms/simulated_annealing_algorithm.cpp algorithms/simulated_annealing_algorithm.h algorithms/genetic_algorithm.cpp algorithms/genetic_algorithm.h algorithms/genetic_algorithms_functions.h utils/time_measure.h)
