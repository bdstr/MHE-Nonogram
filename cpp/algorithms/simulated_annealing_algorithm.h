
#ifndef NONOGRAM_CPP_ALGORITHMS_SIMULATED_ANNEALING_ALGORITHM_H
#define NONOGRAM_CPP_ALGORITHMS_SIMULATED_ANNEALING_ALGORITHM_H

#include "../nonogram.h"

class SimulatedAnnealingAlgorithm {
public:
  SimulatedAnnealingAlgorithm(Nonogram target);
  std::tuple<Nonogram, int> run(double initial_temp, int number_of_tries_during_one_epoque, int iterations);
private:
  Nonogram target;
  double temp_annealing_func(double current);
};

#endif //NONOGRAM_CPP_ALGORITHMS_SIMULATED_ANNEALING_ALGORITHM_H
