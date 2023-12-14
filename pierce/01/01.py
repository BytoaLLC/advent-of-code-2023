def part_one(file_name):
    s = 0
    with open(file_name) as input:
        for line in input.readlines():
            low, hi = 0, len(line) - 1
            while not line[low].isdigit():
                low += 1
            while not line[hi].isdigit():
                hi -= 1
            s += int(line[hi]) + int(line[low]) * 10
    return s


def part_two(file_name):
    digits = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "eight": 8,
        "nine": 9,
    }
    starting_chars = ["o", "t", "f", "s", "e", "n"]
    ending_chars = ["e", "o", "r", "x", "n", "t"]

    def find_digit(line, reverse=False):
        line = line[::-1] if reverse else line
        cand_endpoints = ending_chars if reverse else starting_chars
        # candidate indices to check (i.e. characters that could start/end a spelled out digit)
        # this is slightly better than naively checking all slices
        cand_idx = []
        for i, c in enumerate(line):
            if c in cand_endpoints:
                cand_idx.append(i)
            for j in cand_idx:
                if j != i:
                    # we have to reverse our slice so "eno" becomes "one" and can be recognized by our dict
                    candidate = line[j:i][::-1] if reverse else line[j:i]
                    if candidate in digits:
                        return digits[candidate]
            if c.isdigit():
                return int(c)
        return -1

    s = 0
    with open(file_name) as input:
        for line in input.readlines():
            s += find_digit(line, reverse=True) + find_digit(line) * 10
    return s


if __name__ == "__main__":
    # print(part_one("part1_test_input.txt"))
    print(part_two("part2_test_input.txt"))
