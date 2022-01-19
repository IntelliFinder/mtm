def find_best_selling_product(filename):
    sequence = [line.split().extend([0]) for line in filename]
    return None


def main():
    file = open("example.txt", 'r')

    find_best_selling_product(file)
    file.close()
    return 0


if __name__ == '__main__':
    main()

