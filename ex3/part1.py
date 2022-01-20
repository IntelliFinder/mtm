def find_best_selling_product(filename):
    sequence = [line.split() for line in filename]
    best = {}
    for idx, item in enumerate(sequence):
        if item[0] == 'add' and item[1] == 'product':
            best[item[2]] = [float(item[3]), float(item[4]), 0]
        if item[0] == 'change' and item[1] == 'amount':
            best[item[2]][1] += float(item[3])
        if item[0] == 'ship' and item[1] == 'order':
            orders = [[item[i+1][:-1], float(item[i+2])] for i, add in enumerate(item) if add == 'order' or add == '--']
            for order in orders:
                if order[0] in best:
                    if (best[order[0]][1] - order[1]) < 0:
                        print("Fail")
                    else:
                        print("success")
            #for order in orders:
            #    if order[0] in best:
            #        if (best[order[0]][1] - order[1]) >= 0:
            #            best[order[0]][1] -= order[1]
            #            best[order[0]][2] += order[1]*best[order[0]][0]
    print(best)
    return None


def main():
    file = open("example.txt", 'r')
    find_best_selling_product(file)
    file.close()
    print("Hello World!")


if __name__ == '__main__':
    main()

