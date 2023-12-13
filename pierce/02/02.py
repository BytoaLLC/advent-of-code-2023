import numpy as np


def part_one(file_name):
    # This is insanely overengineered but i had a vision and i had to make it reality lol
    # i cant tell if its beautiful or repulsive... either way i love it
    max_vals = {"red": 12, "green": 13, "blue": 14}

    def exceeds_max(game):
        for obs in game.split(","):
            num, color = obs.split()
            yield int(num) > max_vals[color]

    with open(file_name) as input:
        games = [",".join(line.split(":")[1].split(";")) for line in input.readlines()]
        not_possible = sum(i + 1 for i, game in enumerate(games) if any(exceeds_max(game)))
        return sum(i + 1 for i in range(len(games))) - not_possible


def part_two(file_name):
    # honestly this part felt easier but that's def cause i overdid it in the first part
    def find_powers(game):
        max_vals = {"red": 0, "green": 0, "blue": 0}
        for obs in game.split(","):
            num, color = obs.split()
            num = int(num)
            if max_vals[color] < num:
                max_vals[color] = num
        return np.prod(list(max_vals.values()))

    with open(file_name) as input:
        games = [",".join(line.split(":")[1].split(";")) for line in input.readlines()]
        return sum(find_powers(game) for game in games)


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
