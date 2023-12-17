import re
from math import lcm


def part_one(file_name):
    next_node = {}
    with open(file_name) as input:
        directions = [0 if c == "L" else 1 for c in input.readline().strip()]
        input.readline()
        for line in input.readlines():
            src, left, right = re.findall("\\w+", line)
            next_node[src] = (left, right)

    i = 0
    curr = "AAA"
    while curr != "ZZZ":
        d = directions[i % len(directions)]
        curr = next_node[curr][d]
        i += 1
    return i


def part_two(file_name):
    next_node = {}
    starts = []
    with open(file_name) as input:
        directions = [0 if c == "L" else 1 for c in input.readline().strip()]
        input.readline()
        for line in input.readlines():
            src, left, right = re.findall("\\w+", line)
            if src[2] == "A":
                starts.append(src)
            next_node[src] = (left, right)

    # answer is least common multiple of all starts
    num_steps = []
    for start in starts:
        i = 0
        curr = start
        while curr[2] != "Z":
            d = directions[i % len(directions)]
            curr = next_node[curr][d]
            i += 1
        num_steps.append(i)
    return lcm(*num_steps)


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
