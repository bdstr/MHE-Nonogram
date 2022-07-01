
#ifndef NONOGRAM_CPP_ALGORITHMS_GENETICALGORITHMSFUNCTIONS_H
#define NONOGRAM_CPP_ALGORITHMS_GENETICALGORITHMSFUNCTIONS_H

class GeneticAlgorithmsFunctions {
public:
  static
  static std::vector <std::tuple<Nonogram, int>> score_population(std::vector <Nonogram> population);
  static std::vector <Nonogram> select_population(std::vector <std::tuple<Nonogram, int>> scored_population);
};

#endif //NONOGRAM_CPP_ALGORITHMS_GENETICALGORITHMSFUNCTIONS_H
