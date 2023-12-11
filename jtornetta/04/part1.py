import re


def sum_card_points(cards):
    total = 0
    for card in range(len(cards)):
        v = re.findall("[0-9]+|\|", cards[card])
        pipe = v.index("|")
        wins = sum(i in v[pipe + 1:] for i in v[1:pipe])
        total += int(2 ** (wins - 1))
    return total


def main():
    with open("input.txt") as f:
        cards = f.read().splitlines()
    print(sum_card_points(cards))


if __name__ == "__main__":
    main()
