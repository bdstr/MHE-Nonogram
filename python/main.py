import time

from hill_climbing_algorithm import HillClimbingAlgorithm
from nonogram import Nonogram
from simulated_annealing_algorithm import SimulatedAnnealingAlgorithm
from tabu_algorithm import TabuAlgorithm


def benchmark_mhe_algorithm_function(func, *args):
    start = time.time()
    match, score = func(*args)
    match.print()
    end = time.time()
    print(f'Score: {score}')
    print(f"Execution time: {end - start:.2f} seconds")
    return match, score


# nonogram = Nonogram(10, 10, seed=int(hex(0xC0781E0781E0781E1FE7F8CC), 16))
# nonogram = Nonogram(5, 5, seed=int(hex(0x73BFB), 16))
nonogram = Nonogram(5, 5, seed=int(hex(0x1555555), 16))
nonogram.print()

hill_climbing_algorithm = HillClimbingAlgorithm(nonogram)
tabu_algorithm = TabuAlgorithm(nonogram)
simulated_annealing_algorithm = SimulatedAnnealingAlgorithm(nonogram)

print("\nHill Climbing Deterministic")
benchmark_mhe_algorithm_function(hill_climbing_algorithm.run_deterministic, 1_000)

print("\nHill Climbing Stochastic")
benchmark_mhe_algorithm_function(hill_climbing_algorithm.run_stochastic, 1_000)

print("\nTabu")
benchmark_mhe_algorithm_function(tabu_algorithm.run, 1_000, 100)

print("\nSimulated Annealing")
benchmark_mhe_algorithm_function(simulated_annealing_algorithm.run, 100,
                                 SimulatedAnnealingAlgorithm.temp_annealing_func, 10, 1_000)
