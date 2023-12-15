from math import floor, ceil


def ways_to_win(time: int, dist: int):
    dn = time * time - 4 * dist
    return ceil((time + dn**0.5) / 2) - floor((time - dn**0.5) / 2) - 1


def main():
    with open("input.txt", "r") as f:
        lines = f.readlines()

    time, dist = [int("".join(filter(lambda x: x.isdigit(), s))) for s in lines]
    print(ways_to_win(time, dist))


if __name__ == "__main__":
    main()
