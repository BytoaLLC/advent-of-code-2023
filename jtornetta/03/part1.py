import re
from collections import defaultdict


def sum_part_numbers(lines):
    symbols = dict()
    for y, line in enumerate(lines):
        for x, c in enumerate(line):
            if c not in "1234567890.":
                symbols[(x, y)] = c

    gears = defaultdict(list)
    part_numbers_sum = 0
    for y, line in enumerate(lines):
        for match in re.finditer(r"\d+", line):
            for (s_x, s_y), c in symbols.items():
                if (match.start() - 1 <= s_x <= match.end()) and (y - 1 <= s_y <= y + 1):
                    num = int(match.group())
                    part_numbers_sum += num
                    if c == "*":
                        gears[(s_x, s_y)].append(num)
                    break
    return part_numbers_sum


def main():
    with open("input.txt") as f:
        lines = f.read().split("\n")
        
        print(sum_part_numbers(lines))


if __name__ == "__main__":
    main()


