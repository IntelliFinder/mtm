def find_best_selling_product(filename):
    sequence = [line.split() for line in filename]
    if sequence == ['']: #not sure about this, test it !
        value = ('', 0)
        return value
    best = {}
    #debug_orders = []
    for idx, item in enumerate(sequence):
        if item[0] == 'add' and item[1] == 'product':
            best[item[2]] = [float(item[3]), float(item[4]), 0]
        if item[0] == 'change' and item[1] == 'amount':
            best[item[2]][1] += float(item[3])
        if item[0] == 'ship' and item[1] == 'order':
            orders = [[item[i+1][:-1], float(item[i+2])] for i, add in enumerate(item) if add == 'order' or add == '--']
            for order in orders:
                if order[0] in best:
                    if (best[order[0]][1] - order[1]) >= 0:
                        ###debug_orders.append([order[0], order[1], order[1]*best[order[0]][0]])
                        best[order[0]][1] -= order[1]
                        best[order[0]][2] += order[1]*best[order[0]][0]
    #get maximum sold product and total money made while shipping it
    current_selling_price = max([val[2] for val in best.values()])
    products = sorted([key for key in best.keys() if best[key][2] == current_selling_price])
    if not products:
        value = ('', 0)
        return value
    value = (products[0], current_selling_price)
    return value


def main():
    file = open("example.txt", 'r')
    find_best_selling_product(file)
    file.close()


if __name__ == '__main__':
    main()

