def find_best_selling_product(filename):
    sequence = [line.split() for line in filename]
    best = []
    for item in sequence:
        if item[0] == 'add' and item[1] == 'product':
            best.append([item[2], float(item[3]), float(item[4]), 0])
        if item[0] == 'change' and item[1] == 'amount':
            best[[idx for idx, val in enumerate(best) if val[0] == item[2]][0]][2] += float(item[3])
    return None


def main():
    file = open("example.txt", 'r')
    find_best_selling_product(file)
    file.close()
    print("Hello World!")
    return 0


if __name__ == '__main__':
    main()

