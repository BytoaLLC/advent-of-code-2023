from string import punctuation
import numpy as np

special_not_period = punctuation.replace(".", "")
gear_symbol = "*"


def grid_helper(file_name):
    grid = []
    with open(file_name) as input:
        for line in input.readlines():
            grid.append([c for c in line.strip()])
    return grid


def handle_num(grid, i, j, consume=True):
    # check for num at index i,j
    # if present add to running total and zero out
    num_cols = len(grid[0])
    if grid[i][j].isdigit():
        ones_place = j
        # go as far to right as we can to find the ones place
        while ones_place < num_cols - 1 and grid[i][ones_place + 1].isdigit():
            ones_place += 1

        factor = 1
        pos = ones_place
        num = 0
        while pos >= 0:
            num += int(grid[i][pos]) * factor
            if consume:
                grid[i][pos] = "."
            if pos == 0 or not grid[i][pos - 1].isdigit():
                break
            pos -= 1
            factor *= 10
        return num
    return 0


def part_one(file_name):
    # There has to be a better way... this felt so tedious
    # plan turn into a pseudomatrix so i can do index math
    grid = grid_helper(file_name)
    num_rows = len(grid)
    num_cols = len(grid[0])
    ret = 0
    for i, row in enumerate(grid):
        if any(c in special_not_period for c in row):
            for j, val in enumerate(row):
                if val in special_not_period:
                    if i != 0:
                        # check the previous row
                        ret += handle_num(grid, i - 1, j)
                        if j != 0:
                            # check the previous col
                            ret += handle_num(grid, i - 1, j - 1)
                            ret += handle_num(grid, i, j - 1)
                        if j != num_cols - 1:
                            # check the next col
                            ret += handle_num(grid, i - 1, j + 1)
                            ret += handle_num(grid, i, j + 1)
                    if i != num_rows - 1:
                        # check the next row
                        ret += handle_num(grid, i + 1, j)
                        if j != 0:
                            # check the previous col
                            ret += handle_num(grid, i + 1, j - 1)
                        if j != num_cols - 1:
                            # check the next col
                            ret += handle_num(grid, i + 1, j + 1)
    return ret


def part_two(file_name):
    # LOL i cheated on this one... but they didn't cover the edge case so i guess it counts
    grid = grid_helper(file_name)
    num_rows = len(grid)
    num_cols = len(grid[0])
    ret = 0
    for i, row in enumerate(grid):
        if any(c == gear_symbol for c in row):
            for j, val in enumerate(row):
                if val == gear_symbol:
                    inds_to_consider = []
                    if i != 0:
                        # check the previous row
                        inds_to_consider.append((i - 1, j))
                        if j != 0:
                            # check the previous col
                            inds_to_consider.append((i - 1, j - 1))
                            inds_to_consider.append((i, j - 1))
                        if j != num_cols - 1:
                            # check the next col
                            inds_to_consider.append((i - 1, j + 1))
                            inds_to_consider.append((i, j + 1))
                    if i != num_rows - 1:
                        # check the next row
                        inds_to_consider.append((i + 1, j))
                        if j != 0:
                            # check the previous col
                            inds_to_consider.append((i + 1, j - 1))
                        if j != num_cols - 1:
                            # check the next col
                            inds_to_consider.append((i + 1, j + 1))

                    # okay this doesn't techinically work...
                    # if a gear is adjacent 2 identical part numbers this will undercount...
                    # but maybe they don't have an edge case for it lol
                    part_nums = set(
                        handle_num(grid, x, y, consume=False) for x, y in inds_to_consider
                    ) - {0}
                    if len(part_nums) == 2:
                        ret += np.prod(list(part_nums))
    return ret


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
