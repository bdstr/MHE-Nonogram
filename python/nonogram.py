import enum
import random


class Pixel(enum.Enum):
    white = 0
    black = 1


class Nonogram:
    def __init__(self, width=5, height=5, seed=None):
        self.width = width
        self.height = height
        if seed is not None:
            self.seed = seed
        else:
            self.seed = random.randint(0, 2 ** (width * height))
        self.pixels = self._generate_from_seed(self.seed)
        self.hints_vertical, self.hints_horizontal = self._calculate_hints()

    def _generate_from_seed(self, seed):
        pixels = []
        for y in range(self.height):
            pixels.append([])
            for x in range(self.width):
                if (bin(seed)[2:].zfill(self.height * self.width))[y * self.width + x] == str(1):
                    pixels[y].append(Pixel.black)
                else:
                    pixels[y].append(Pixel.white)
        return pixels

    def _calculate_hints(self):
        hints_y = []
        for x in range(self.width):
            hints_y.append([])
            for y in range(self.height):
                if self.pixels[y][x] == Pixel.black:
                    if y == 0 or self.pixels[y - 1][x] == Pixel.white:
                        hints_y[x].append(1)
                    else:
                        hints_y[x][-1] = hints_y[x][-1] + 1
            if len(hints_y[x]) == 0:
                hints_y[x].append(0)

        hints_x = []
        for y in range(self.height):
            hints_x.append([])
            for x in range(self.width):
                if self.pixels[y][x] == Pixel.black:
                    if x == 0 or self.pixels[y][x - 1] == Pixel.white:
                        hints_x[y].append(1)
                    else:
                        hints_x[y][-1] = hints_x[y][-1] + 1
            if len(hints_x[y]) == 0:
                hints_x[y].append(0)

        return hints_y, hints_x

    def print(self):
        hint_column_number = max(len(hints) for hints in self.hints_horizontal)
        hint_row_number = max(len(hints) for hints in self.hints_vertical)

        for hint_row in range(hint_row_number):
            print(' ' * hint_column_number, end='')
            for hint_column in range(self.width):
                if hint_row < len(self.hints_vertical[hint_column]):
                    print(self.hints_vertical[hint_column][hint_row], end='')
                else:
                    print(' ', end='')
            print('\n', end='')

        for y in range(self.height):

            for hint_column in range(hint_column_number):
                if hint_column < len(self.hints_horizontal[y]):
                    print(self.hints_horizontal[y][hint_column], end='')
                else:
                    print(' ', end='')

            for hint_column in range(self.width):
                if self.pixels[y][hint_column] == Pixel.black:
                    print('█', end='')
                else:
                    print(' ', end='')
            print('\n', end='')

    def _calculate_groups_content_score(self, self_line, neighbour_line):
        score = 0
        for x in range(min(len(self_line), len(neighbour_line))):
            if self_line[x] == neighbour_line[x]:
                score += 1

        return score

    def calculate_fitness_score(self, candidate):
        if candidate.height != self.height or candidate.width != self.width:
            return 0

        fitness_score = 0
        for y in range(self.height):
            # matching lengths groups count
            fitness_score += max(0, len(self.hints_vertical[y]) - abs(
                len(self.hints_vertical[y]) - len(candidate.hints_vertical[y])))
            # matching groups sums
            fitness_score += max(0, sum(self.hints_vertical[y]) - abs(
                sum(self.hints_vertical[y]) - sum(candidate.hints_vertical[y])))
            # matching groups content
            fitness_score += self._calculate_groups_content_score(self.hints_vertical[y], candidate.hints_vertical[y])

        for x in range(self.width):
            # matching lengths groups count
            fitness_score += max(0, len(self.hints_horizontal[x]) - abs(
                len(self.hints_horizontal[x]) - len(candidate.hints_horizontal[x])))
            # matching groups sums
            fitness_score += max(0, sum(self.hints_horizontal[x]) - abs(
                sum(self.hints_horizontal[x]) - sum(candidate.hints_horizontal[x])))
            # matching groups content
            fitness_score += self._calculate_groups_content_score(self.hints_horizontal[x],
                                                                  candidate.hints_horizontal[x])

        return fitness_score

    def get_neighbours(self):
        seeds = [self.seed ^ (1 << bit) for bit in range(self.width * self.height)]
        neighbours = [Nonogram(self.width, self.height, seed=seed) for seed in seeds]
        return neighbours
