
#ifndef NONOGRAM_CPP_RANDOM_H
#define NONOGRAM_CPP_RANDOM_H

#include <random>

template<typename T>
class Random {
public:
  Random();
  T generate(T from, T to);
  T generate_floating(T from, T to);
private:
  std::random_device r;
  std::mt19937 generator;
};

template<typename T>
Random<T>::Random() {
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  generator.seed(seed);
}

template<typename T>
T Random<T>::generate(T from, T to) {
  std::uniform_int_distribution<T> distribution(from, to);
  return distribution(generator);
}

template<typename T>
T Random<T>::generate_floating(T from, T to) {
  std::uniform_real_distribution<T> distribution(from, to);
  return distribution(generator);
}

#endif //NONOGRAM_CPP_RANDOM_H
