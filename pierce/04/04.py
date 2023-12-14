import numpy as np


def part_one(file_name):
    # im done with the fancy stuff lol
    # just wanna process this with as little thinking as possible
    points = 0
    with open(file_name) as input:
        cards = [line.split(":")[1] for line in input.readlines()]
        for card in cards:
            winning_nums, my_nums = card.split("|")
            winning_nums = winning_nums.strip().split()
            my_nums = my_nums.strip().split()
            num_winners = sum(n in winning_nums for n in my_nums)
            if num_winners != 0:
                points += (2**(num_winners - 1))
    return points


def part_two(file_name):
    # not very efficient but seems to be good enough
    with open(file_name) as input:
        cards = [line.split(":")[1] for line in input.readlines()]

    num_cards = len(cards)
    num_copies = np.array([1] * num_cards)
    for i, card in enumerate(cards):
        winning_nums, my_nums = card.split("|")
        winning_nums = winning_nums.strip().split()
        my_nums = my_nums.strip().split()
        num_winners = sum(n in winning_nums for n in my_nums) + 1
        end_bound = min(i + num_winners, num_cards)
        for j in range(num_copies[i]):
            num_copies[i+1:end_bound] += 1
    return sum(num_copies)


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
