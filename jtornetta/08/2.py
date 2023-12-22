import re
from math import lcm
from functools import reduce

def get_steps(lines):
    rl = lines[0]
    rl = [0 if dir == "L" else 1 for dir in rl]

    nodes = lines[1].split("\n")
    nodes = [re.findall(r"([A-Z]+)", node) for node in nodes]
    nodes = {node[0]: (node[1], node[2]) for node in nodes}

    locs = [loc for loc in nodes.keys() if loc[-1] == "A"]
    results = []

    for loc in locs:
        count = 0
        while loc[-1] != "Z":
            dir = rl[count % len(rl)]
            loc = nodes[loc][dir]
            count += 1
        results.append(count)

    print(reduce(lcm, results))

def main():
    with open("input.txt", "r") as f:
        lines = f.read().split("\n\n")
    get_steps(lines)


if __name__ == "__main__":
    main()