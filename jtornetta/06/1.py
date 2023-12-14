from math import floor, ceil, prod


def ways_to_win(time: int, dist: int):
    dn = time * time - 4 * dist
    return ceil((time + dn**0.5) / 2) - floor((time - dn**0.5) / 2) - 1


def main():
    with open("input.txt", "r") as f:
        lines = f.readlines()

    win_val = list(zip(lines[0].split()[1:], lines[1].split()[1:]))
    win_val = [(int(x[0]), int(x[1])) for x in win_val]

    print(prod(map(lambda x: ways_to_win(x[0], x[1]), win_val)))


if __name__ == "__main__":
    main()
