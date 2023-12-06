def get_calibration_digits(line):
    digits = [ch for ch in line if ch.isdigit()]

    if not digits:
        return 0

    first, last = digits[0], digits[-1] if len(digits) > 1 else digits[0]

    print("Calibration Value:", first + last)
    return int(first + last)


def sum_calibration_values(lines):
    return sum(get_calibration_digits(line.strip()) for line in lines)


def main():
    with open("input.txt", 'r') as f:
        lines = f.readlines()

    print("TOTAL:", sum_calibration_values(lines))


if __name__ == "__main__":
    main()