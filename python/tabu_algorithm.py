from nonogram import Nonogram


class TabuAlgorithm:
    def __init__(self, target):
        self._target = target

    def run(self, iterations, max_size):
        initial = Nonogram(self._target.width, self._target.height)
        neighbours = initial.get_neighbours()

        best_score = 0
        best = neighbours[0]
        best_candidate = neighbours[0]

        tabu_list = [neighbours[0]]
        for i in range(iterations):
            neighbours = best_candidate.get_neighbours()
            best_candidate = neighbours[0]
            for candidate in neighbours:
                if (not tabu_list.count(candidate)) and (
                        self._target.calculate_fitness_score(candidate) > self._target.calculate_fitness_score(
                    best_candidate)):
                    best_candidate = candidate

            if self._target.calculate_fitness_score(best_candidate) > self._target.calculate_fitness_score(best):
                best = best_candidate
                best_score = self._target.calculate_fitness_score(best)

            tabu_list.append(best_candidate)
            if len(tabu_list) > max_size:
                tabu_list.pop(0)

        return best, best_score
