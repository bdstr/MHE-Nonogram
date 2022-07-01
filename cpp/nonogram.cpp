#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include "nonogram.h"
#include "utils/random.h"

Nonogram::Nonogram(int Width, int Height) : width(Width), height(Height) {
  Random<unsigned long long> random;
  unsigned long long generated = random.generate(0, (unsigned long long)pow(2, width * height));
  this->seed = number_to_seed(generated);
  calculate_hints();
}
Nonogram::Nonogram(int Width, int Height, std::vector<bool> Seed)
	: width(Width), height(Height), seed(Seed) {
  calculate_hints();
}
Nonogram::Nonogram(int Width, int Height, unsigned long long Seed)
	: width(Width), height(Height), seed(number_to_seed(Seed)) {
  calculate_hints();
}

bool Nonogram::operator==(const Nonogram &Rhs) const {
  return width == Rhs.width &&
	  height == Rhs.height &&
	  hints_vertical == Rhs.hints_vertical &&
	  hints_horizontal == Rhs.hints_horizontal &&
	  seed == Rhs.seed;
}
bool Nonogram::operator!=(const Nonogram &Rhs) const {
  return !(Rhs == *this);
}
std::vector<Nonogram> Nonogram::get_neighbours() {
  std::vector<Nonogram> neighbours;
  for (int i = 0; i < this->seed.size(); i++) {
	std::vector<bool> new_seed = this->seed;
	new_seed[i] = !new_seed[i];
	neighbours.push_back(Nonogram(this->width, this->height, new_seed));
  }
  return neighbours;
}

int Nonogram::calculate_fitness_score(Nonogram candidate) {
  if (candidate.height != this->height || candidate.width != this->width) {
	return 0;
  }

  int fitness_score = 0;
  for (int y = 0; y < this->height; y++) {
	// matching lengths groups count
	fitness_score += std::max(0, (int)this->hints_vertical[y].size() - abs(
		(int)(this->hints_vertical[y].size() - candidate.hints_vertical[y].size())));
	// matching groups sums
	fitness_score +=
		std::max(0, std::accumulate(this->hints_vertical[y].begin(), this->hints_vertical[y].end(), 0) - abs(
			std::accumulate(this->hints_vertical[y].begin(), this->hints_vertical[y].end(), 0)
				- std::accumulate(candidate.hints_vertical[y].begin(), candidate.hints_vertical[y].end(), 0)));
	// matching groups content
	fitness_score += calculate_groups_content_score(this->hints_vertical[y], candidate.hints_vertical[y]);
  }

  for (int x = 0; x < this->width; x++) {
	// matching lengths groups count
	fitness_score += std::max(0, (int)this->hints_horizontal[x].size() - abs(
		(int)(this->hints_horizontal[x].size() - candidate.hints_horizontal[x].size())));
	// matching groups sums
	fitness_score +=
		std::max(0, std::accumulate(this->hints_horizontal[x].begin(), this->hints_horizontal[x].end(), 0) - abs(
			std::accumulate(this->hints_horizontal[x].begin(), this->hints_horizontal[x].end(), 0)
				- std::accumulate(candidate.hints_horizontal[x].begin(), candidate.hints_horizontal[x].end(), 0)));
	// matching groups content
	fitness_score += calculate_groups_content_score(this->hints_horizontal[x], candidate.hints_horizontal[x]);
  }

  return fitness_score;
}

int Nonogram::get_max_score() {
  if (this->max_score > 0) {
	return this->max_score;
  } else {
	this->max_score = calculate_fitness_score(*this);
	return this->max_score;
  }
}

void Nonogram::print() {
  int hint_column_number = 0;
  int hint_row_number = 0;
  for (int i = 0; i < this->hints_horizontal.size(); i++) {
	if (this->hints_horizontal[i].size() > hint_column_number)
	  hint_column_number = this->hints_horizontal[i].size();
  }
  for (int i = 0; i < this->hints_vertical.size(); i++) {
	if (this->hints_vertical[i].size() > hint_row_number)
	  hint_row_number = this->hints_vertical[i].size();
  }

  for (int hint_row = 0; hint_row < hint_row_number; hint_row++) {
	for (int i = 0; i < hint_column_number; i++) {
	  std::cout << ' ';
	}
	for (int hint_column = 0; hint_column < this->width; hint_column++) {
	  if (hint_row < this->hints_vertical[hint_column].size()) {
		std::cout << this->hints_vertical[hint_column][hint_row];
	  } else {
		std::cout << ' ';
	  }
	}
	std::cout << std::endl;
  }

  for (int y = 0; y < this->height; y++) {

	for (int hint_column = 0; hint_column < hint_column_number; hint_column++) {
	  if (hint_column < this->hints_horizontal[y].size()) {
		std::cout << this->hints_horizontal[y][hint_column];
	  } else {
		std::cout << ' ';
	  }
	}

	for (int x = 0; x < this->width; x++) {
	  if (this->seed[y * this->width + x]) {
		std::cout << "█";
	  } else {
		std::cout << ' ';
	  }
	}
	std::cout << std::endl;
  }
}

std::vector<bool> Nonogram::number_to_seed(unsigned long long hex) {
  std::vector<bool> new_seed;
  for (int i = 0; i < this->width * this->height; i++) {
	new_seed.push_back(hex & 1);
	hex >>= 1;
  }
  return new_seed;
}

void Nonogram::calculate_hints() {
  std::vector<std::vector<int>> hints_y;
  for (int x = 0; x < this->width; x++) {
	std::vector<int> vector;
	hints_y.push_back(vector);
	for (int y = 0; y < this->height; y++) {
	  if (this->seed[y * this->width + x] == true) {
		if (y == 0 || this->seed[(y - 1) * this->width + x] == false) {
		  hints_y[x].push_back(1);
		} else {
		  hints_y[x][hints_y.size() - 1] = hints_y[x][hints_y.size() - 1] + 1;
		}
	  }
	}
	if (hints_y[x].empty()) {
	  hints_y[x].push_back(0);
	}
  }

  std::vector<std::vector<int>> hints_x;
  for (int y = 0; y < this->height; y++) {
	std::vector<int> vector;
	hints_x.push_back(vector);
	for (int x = 0; x < this->width; x++) {
	  if (seed[y * this->width + x] == true) {
		if (x == 0 || seed[y * this->width + x - 1] == false) {
		  hints_x[y].push_back(1);
		} else {
		  hints_x[y][hints_x.size() - 1] = hints_x[y][hints_x.size() - 1] + 1;
		}
	  }
	}
	if (hints_x[y].empty()) {
	  hints_x[y].push_back(0);
	}
  }

  this->hints_vertical = hints_y;
  this->hints_horizontal = hints_x;
}

int Nonogram::calculate_groups_content_score(std::vector<int> self_line, std::vector<int> candidate_line) {
  int score = 0;
  for (int x = 0; x < std::min(self_line.size(), candidate_line.size()); x++) {
	if (self_line[x] == candidate_line[x]) {
	  score += 1;
	}
  }
  return score;
}

