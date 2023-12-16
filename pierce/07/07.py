from collections import Counter
from functools import cmp_to_key

val_dict = {str(i): i for i in range(1, 10)}
val_dict.update({"T": 10, "J": 11, "Q": 12, "K": 13, "A": 14})


def comparator_hands(h1, h2):
    # At first we only care about how many times each elem appeared
    # So we can count and sort to compare
    h1_counts = sorted(Counter(h1).values(), reverse=True)
    h2_counts = sorted(Counter(h2).values(), reverse=True)
    if h1_counts == h2_counts:
        # counts are equal, now we have to consider the values of the hands
        h1_val, h2_val = [val_dict[c] for c in h1], [val_dict[c] for c in h2]
    else:
        h1_val, h2_val = h1_counts, h2_counts
    if h1_val < h2_val:
        return -1
    elif h1_val > h2_val:
        return 1
    else:
        return 0


def part_one(file_name):
    hands_and_bets = []
    for line in open(file_name).readlines():
        hand, bet = line.split()
        hands_and_bets.append((hand, int(bet)))

    def comparator_hand_and_bets(hb1, hb2):
        return comparator_hands(hb1[0], hb2[0])

    sorted_hands_and_bets = sorted(hands_and_bets, key=cmp_to_key(comparator_hand_and_bets))
    return sum(b*i for (_, b), i in zip(sorted_hands_and_bets, list(range(1, len(hands_and_bets)+1))))


def convert_jokes(hand):
    # best choice is the highest frequency card besides joker
    counts = sorted(Counter(hand).items(), key=lambda x: x[1], reverse=True)
    if len(counts) == 1:
        # all jokers
        best = counts[0][0] if counts[0][0] != "J" else "A"
    else:
        best = counts[0][0] if counts[0][0] != "J" else counts[1][0]
    return hand.replace("J", best)


def jokers_comparator_hands(h1, h2):
    h1_counts = sorted(Counter(convert_jokes(h1)).values(), reverse=True)
    h2_counts = sorted(Counter(convert_jokes(h2)).values(), reverse=True)
    if h1_counts == h2_counts:
        # counts are equal, now we have to consider the values of the hands
        h1_val, h2_val = [val_dict[c] for c in h1], [val_dict[c] for c in h2]
    else:
        h1_val, h2_val = h1_counts, h2_counts
    if h1_val < h2_val:
        return -1
    elif h1_val > h2_val:
        return 1
    else:
        return 0


def part_two(file_name):
    # jacks became jokers
    val_dict["J"] = 0

    hands_and_bets = []
    for line in open(file_name).readlines():
        hand, bet = line.split()
        hands_and_bets.append((hand, int(bet)))

    def comparator_hand_and_bets(hb1, hb2):
        return jokers_comparator_hands(hb1[0], hb2[0])

    sorted_hands_and_bets = sorted(hands_and_bets, key=cmp_to_key(comparator_hand_and_bets))
    return sum(b*i for (_, b), i in zip(sorted_hands_and_bets, list(range(1, len(hands_and_bets)+1))))


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
