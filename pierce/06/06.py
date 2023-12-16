import math


def find_roots(a, b, c):
    # we can use the quadratic formula, this describes the quadratic a x**2 + b x + c
    return (
        (-b + math.sqrt(b**2 - (4 * a * c))) / (2 * a),
        (-b - math.sqrt(b**2 - (4 * a * c))) / (2 * a),
    )


def count_ints_between(x1, x2):
    return math.floor(x2) - math.floor(x1) - (x1.is_integer() and x2.is_integer())


def part_one(file_name):
    # x ms holding down gives x mm/ms speed for n-x ms. So distance traveled is x(n-x) mm
    # which explains why the example shows a parabola. So if the record distance is D,
    # we want to solve which values satisfy x(n-x) = D, which is the same as finding the
    # roots of the quadratic -x**2 + nx - D = 0. And the integers between these
    # 2 roots are the number of times that would result in a record.
    with open(file_name) as input:
        times = input.readline().split(":")[1].split()
        times = [int(t) for t in times]
        distances = input.readline().split(":")[1].split()
        distances = [int(d) for d in distances]

    return math.prod(count_ints_between(*find_roots(-1, t, -d)) for t, d in zip(times, distances))


def part_two(file_name):
    with open(file_name) as input:
        time = int(input.readline().split(":")[1].replace(' ', ''))
        distance = int(input.readline().split(":")[1].replace(' ', ''))
        return count_ints_between(*find_roots(-1, time, -distance))


if __name__ == "__main__":
    # print(part_one("test_input.txt"))
    print(part_two("test_input.txt"))
