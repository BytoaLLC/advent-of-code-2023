from pathlib import Path
import re


def get_steps(lines):
    # get directions
    rl = lines[0]
    rl = [0 if dir == "L" else 1 for dir in rl]

    # get and parse nodes
    nodes = lines[1].split("\n")
    nodes = [re.findall(r"([A-Z]+)", node) for node in nodes]
    nodes = {node[0]: (node[1], node[2]) for node in nodes}

    current = "AAA"
    count = 0

    while current != "ZZZ":
        dir = rl[count % len(rl)]
        current = nodes[current][dir]
        count += 1

    print(count)


def main():
    with open("input.txt", "r") as f:
        lines = f.read().split("\n\n")
    get_steps(lines)


if __name__ == "__main__":
    main()

