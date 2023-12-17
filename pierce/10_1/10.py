def grid_helper(file_name):
    grid = []
    with open(file_name) as input:
        for line in input.readlines():
            grid.append([c for c in line.strip()])
    return grid


def steps_in_path(grid, i, j, came_from):
    num_steps = 1
    # symbols mean different things depending on direction we're coming from
    while True:
        # print()
        # print(grid)
        # print(grid[i][j], i, j)
        # print(came_from)
        curr = grid[i][j]
        if grid[i][j] != "S":
            grid[i][j] = "."
        match came_from:
            case "L":
                match curr:
                    case "-":
                        j += 1
                        came_from = "L"
                    case "7":
                        i += 1
                        came_from = "U"
                    case "J":
                        i -= 1
                        came_from= "D"
            case "R":
                match curr:
                    case "-":
                        j -= 1
                        came_from = "R"
                    case "F":
                        i += 1
                        came_from = "U"
                    case "L":
                        i -= 1
                        came_from = "D"
            case "U":
                match curr:
                    case "|":
                        i += 1
                        came_from = "U"
                    case "L":
                        j += 1
                        came_from = "L"
                    case "J":
                        j -= 1
                        came_from = "R"
            case "D":
                match curr:
                    case "|":
                        i -= 1
                        came_from = "D"
                    case "F":
                        j += 1
                        came_from = "L"
                    case "7":
                        j -= 1
                        came_from = "R"
        num_steps += 1
        if grid[i][j] == "S":
            return num_steps


def part_one(file_name):
    grid = grid_helper(file_name)
    for i, row in enumerate(grid):
        if "S" in row:
            j = row.index("S")
            break
    num_rows, num_cols = len(grid), len(grid[0])
    came_from = ""
    if (j+1) < num_cols:
        curr = grid[i][j+1]
        if curr in ["-",  "7", "J"]:
            j += 1
            came_from = "L"
    if not came_from and (j-1)>0:
        curr = grid[i][j-1]
        if curr in ["-",  "F", "L"]:
            j -= 1
            came_from = "R"
    if not came_from and (i+1) < num_rows:
        curr = grid[i+1][j]
        if curr in ["|", "L", "J"]:
            i += 1
            came_from = "U"
    if not came_from and (j-1)>0:
        curr = grid[i - 1][j]
        if curr in ["|", "F", "7"]:
            i -= 1
            came_from = "D"

    return int(steps_in_path(grid, i, j, came_from=came_from) / 2)


if __name__ == "__main__":
    print(part_one("test_input.txt"))
    # print(part_two("test_input.txt"))
