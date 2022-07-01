import math
import random

from nonogram import Nonogram


class SimulatedAnnealingAlgorithm:
    def __init__(self, target):
        self._target = target

    @staticmethod
    def temp_annealing_func(current):
        return current * 0.99

    def run(self, initial_temp, temp_annealing_func, number_of_tries_during_one_epoque, iterations):
        temp = initial_temp
        initial = Nonogram(self._target.width, self._target.height)

        best_score = 0
        best = initial

        for i in range(iterations):
            neighbours = best.get_neighbours()
            for n in range(number_of_tries_during_one_epoque):
                candidate = random.choice(neighbours)
                fitness_score = self._target.calculate_fitness_score(candidate)
                if fitness_score > best_score:
                    best = candidate
                    best_score = fitness_score
                else:
                    worse_candidate_overwrite_probability = math.exp(
                        self._target.calculate_fitness_score(best) - self._target.calculate_fitness_score(
                            candidate) / temp)
                    random_number = random.random()
                    # print(f"{random_number >= worse_candidate_overwrite_probability} {random_number} {worse_candidate_overwrite_probability}")
                    if random_number >= worse_candidate_overwrite_probability:
                        best = candidate
                        best_score = fitness_score

                # print(f"Best score: {str(best_score)}")
                if best_score == 100.00:
                    return best, best_score
            temp = temp_annealing_func(temp)
            # print(f"Iteration: {str(i)}\tTemp: {str(temp)}\tBest score: {str(best_score)}")

        return best, best_score
