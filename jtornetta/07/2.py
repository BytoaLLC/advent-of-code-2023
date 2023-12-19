from collections import Counter


def category(hand):
    jokers = hand.count("J")
    hand = filter(lambda x: x != "J", hand)
    c = Counter(hand)
    freq = [x[1] for x in c.most_common()]
    freq = [0] if len(freq) == 0 else freq
    freq[0] += jokers
    if freq == [5]:
        return 1  # five of a kind
    elif freq == [4,1]:
        return 2  # four of a kind
    elif freq == [3,2]:
        return 3  # full house
    elif freq == [3,1,1]:
        return 4  # three of a kind
    elif freq == [2,2,1]:
        return 5  # two pair
    elif freq == [2,1,1,1]:
        return 6  # one pair
    else:
        return 7  # high card


def translate(hand):
    translation = dict(zip(
        'AKQT987654321J',
        'ABCDEFGHIJKLMN'))
    return ''.join([translation[card] for card in hand])


def sort(bid):
    hand = bid[0]
    return str(category(hand)) + "." + translate(hand)


def main():
    bids = []
    with open("input.txt", "r") as f:
        for line in f:
            bid = line.split()
            hand = bid[0].strip()
            bet = int(bid[1].strip())
            bids.append((hand, bet))
        sorted_bids = sorted(bids, key=sort, reverse=True)
        total = 0
        for i, (hand, bid) in enumerate(sorted_bids):
            total += (i+1) * bid
    print(total)


if __name__ == "__main__":
    main()