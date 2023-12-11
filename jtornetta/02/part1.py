def sum_possible_games(lines):
    available = {"red": 12, "green": 13, "blue": 14}
    possible_games = set()
    for line in lines:
        game, cubes = line.strip().split(":")
        game = int(game.split()[1])
        cubes = cubes.split(";")
        possible = True
        for subset in cubes:
            subset = subset.split(",")
            for color in subset:
                n, color = (int(part) if part.isdigit() else part for part in color.split())
                if available[color] < n:
                    possible = False
        if possible:
            possible_games.add(game)

    return(sum(possible_games))

def main():
    with open("input.txt", 'r') as f:
        lines = f.readlines()

    print("SUM:", sum_possible_games(lines))


if __name__ == "__main__":
    main()