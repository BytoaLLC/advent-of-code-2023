import numpy as np


def min_loc_from_seeds(seeds, reader):
    # we only want to change seed values once per map
    updated = np.zeros(seeds.size, bool)
    for line in reader.readlines():
        if not line[0].isdigit():
            # moving on to next map, reset updated
            updated[:] = False
            continue
        dst, src, rng = line.split()
        dst, src, rng = int(dst), int(src), int(rng)
        update_cond = (src <= seeds) & (seeds <= (src+rng)) & ~updated
        seeds[update_cond] += (dst - src)
        updated[update_cond] = True
    return min(seeds)


def part_one(file_name):
    # idea is to update the seeds as we go
    with open(file_name) as input:
        seeds = input.readline().split(":")[1].split()
        seeds = np.array([int(s) for s in seeds])
        return min_loc_from_seeds(seeds, input)


if __name__ == "__main__":
    print(part_one("test_input.txt"))
    # print(part_two("test_input.txt"))
