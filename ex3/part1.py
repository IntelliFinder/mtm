def find_best_selling_product(filename):
    sequence = [line.split() for line in filename]
    best = {}
    for idx, item in enumerate(sequence):
        if item[0] == 'add' and item[1] == 'product':
            best[item[2]] = [float(item[3]), float(item[4]), 0]
        if item[0] == 'change' and item[1] == 'amount':
            best[item[2]][1] += float(item[3])
        if item[0] == 'ship' and item[1] == 'order':
            orders = [line.split('--') for line in filename if line.split()[0] == 'ship' and line.split()[1] == 'order']
    print(best)
    return None


def main():
    file = open("example.txt", 'r')
    find_best_selling_product(file)
    file.close()
    print("Hello World!")
    return 0


if __name__ == '__main__':
    main()

