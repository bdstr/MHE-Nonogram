//
// Created by marcin on 01.07.22.
//

#ifndef NONOGRAM_CPP_ALGORITHMS_TABU_ALGORITHM_H
#define NONOGRAM_CPP_ALGORITHMS_TABU_ALGORITHM_H

#include "../nonogram.h"
class TabuAlgorithm {
public:
  TabuAlgorithm(Nonogram target);
  std::tuple<Nonogram, int> run(int iterations, int max_size);
private:
  Nonogram target;
  bool is_nonogram_in_list(Nonogram nonogram, std::vector<Nonogram> tabu_list);
};

#endif //NONOGRAM_CPP_ALGORITHMS_TABU_ALGORITHM_H
