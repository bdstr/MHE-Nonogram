//
// Created by marcin on 01.07.22.
//

#ifndef NONOGRAM_CPP_UTILS_TIME_MEASURE_H
#define NONOGRAM_CPP_UTILS_TIME_MEASURE_H

#include <chrono>

class TimeMeasure {
public:
  TimeMeasure() {}
  void start() {
	start_time = std::chrono::high_resolution_clock::now();
  }
  int stop() {
	auto stop_time = std::chrono::high_resolution_clock::now();
	return duration_cast<std::chrono::milliseconds>(stop_time - start_time).count();
  }
private:
  std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> start_time;
};

#endif //NONOGRAM_CPP_UTILS_TIME_MEASURE_H
