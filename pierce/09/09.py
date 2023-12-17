import re


def part_one_and_two(file_name, reverse=False):
    with open(file_name) as input:
        predictions = []
        for line in input.readlines():
            next_val = 0
            seq = [int(c) for c in re.findall("-?\\d+", line)]
            if reverse:
                seq.reverse()
            while not all([s == 0 for s in seq]):
                next_val += seq[-1]
                seq = [seq[i+1] - seq[i] for i in range(len(seq) - 1)]
            predictions.append(next_val)
    return sum(predictions)


if __name__ == "__main__":
    print(part_one_and_two("test_input.txt"))
    print(part_one_and_two("test_input.txt", reverse=True))
