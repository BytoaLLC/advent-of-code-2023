import re

def next_seq_l(seq):
    n_seq = []
    for i in range(len(seq) - 1):
        n_seq.append(seq[i+1] - seq[i])
        
    return n_seq


def main():
    total = 0

    with open("input.txt") as file:
        for line in file.readlines():
            next_seqs = []
            
            seq = list(map(lambda x: int(x), line.split()))
            
            next_seqs.append(seq)
            next_seq = seq
            
            while any(next_seq := next_seq_l(next_seq)):
                next_seqs.append(next_seq)
            next_seqs.append(next_seq)
            
            r = 0
            for s in next_seqs[::-1]:
                r = s[0] - r
            
            total += r
            
    print(total)


if __name__ == "__main__":
    main()