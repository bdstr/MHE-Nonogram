import random

from nonogram import Nonogram


class HillClimbingAlgorithm:
    def __init__(self, target):
        self._target = target

    def _find_best_neighbour(self, neighbours):
        best_score = 0
        best_neighbour = neighbours[0]
        for neighbour in neighbours:
            fitness_score = self._target.calculate_fitness_score(neighbour)
            if fitness_score > best_score:
                best_score = fitness_score
                best_neighbour = neighbour
        return best_neighbour, self._target.calculate_fitness_score(best_neighbour)

    def _find_weighted_random_best_neighbour(self, neighbours):
        weighted_indexes = []
        for i in range(len(neighbours)):
            fitness_score = self._target.calculate_fitness_score(neighbours[i])
            if fitness_score == 100:
                return neighbours[i], fitness_score
            for x in range(int(fitness_score ** 1.1)):
                weighted_indexes.append(i)
        chosen_neighbour = neighbours[random.choice(weighted_indexes)]
        return chosen_neighbour, self._target.calculate_fitness_score(chosen_neighbour)

    def run_deterministic(self, iterations):
        iterations -= 1
        initial = Nonogram(self._target.width, self._target.height)
        neighbours = initial.get_neighbours()
        best, best_score = self._find_best_neighbour(neighbours)
        for i in range(iterations):
            neighbours = best.get_neighbours()
            candidate, candidate_score = self._find_best_neighbour(neighbours)
            if best_score > candidate_score:
                return best, best_score
            else:
                best = candidate
                best_score = candidate_score
        return best, best_score

    def run_stochastic(self, iterations):
        iterations -= 1
        initial = Nonogram(self._target.width, self._target.height)
        neighbours = initial.get_neighbours()
        best, best_score = self._find_weighted_random_best_neighbour(neighbours)
        for i in range(iterations):
            neighbours = best.get_neighbours()
            candidate, candidate_score = self._find_weighted_random_best_neighbour(neighbours)
            if candidate_score > best_score:
                best = candidate
                best_score = candidate_score
        return best, best_score
