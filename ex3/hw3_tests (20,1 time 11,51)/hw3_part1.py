
def print_wrong_output(test, expected, test_num):
    print("Failed test " + str(test_num) + " :(")
    print("Your result: " + str(test))
    print("Expected Result: " + str(expected) + "\n")

def find_best_selling_product(filename):
    file = open(filename, 'r')
    sequence = [line.split() for line in file]
    file.close()
    if not sequence:
        return ('', 0)
    best = {}
    for idx, item in enumerate(sequence):
        if item[0] == 'add' and item[1] == 'product':
            if item[2] not in best:
                best[item[2]] = {'price': float(item[3]), 'amount': float(item[4]), 'total': 0}
        if item[0] == 'change' and item[1] == 'amount':
            if item[2] in best:
                best[item[2]]['amount'] += float(item[3])
        if item[0] == 'ship' and item[1] == 'order':
            orders = [[item[i+1][:-1], float(item[i+2])] for i, j in enumerate(item) if j == 'order' or j == '--']#not dict because can be duplication
            for order in orders:
                name = order[0]
                if name in best:
                    if (best[name]["amount"] - order[1]) >= 0:
                        best[name]["amount"] -= float(order[1])
                        best[name]["total"] += float(order[1]*best[name]["price"])# price times order amount
    current_selling_price = max([val["total"] for val in best.values()])
    products = sorted([key for key in best.keys() if best[key]["total"] == current_selling_price])
    if not products:
        return ('', 0)
    return (products[0], current_selling_price)


def main():
    test1 = find_best_selling_product("hw3_part1_tests_files/items1.txt")
    test1_expected_result = ('baloon', 5600)
    test3 = find_best_selling_product("hw3_part1_tests_files/items2.txt")
    test3_expected_result = ('pineapple', 23200)
    test5 = find_best_selling_product("hw3_part1_tests_files/items3.txt")
    test5_expected_result = ('apple', 9500)
    test7 = find_best_selling_product("hw3_part1_tests_files/items4.txt")
    test7_expected_result = ('pizza', 43350)
    test9 = find_best_selling_product("hw3_part1_tests_files/items5.txt")
    test9_expected_result = ('', 0)
    test11 = find_best_selling_product("hw3_part1_tests_files/items6.txt")
    test11_expected_result = ('bike', 52200)

    if (test1 == test1_expected_result):
        print("Passed test 1!\n")
    else:
        print_wrong_output(test1, test1_expected_result, 1)
    if (test3 == test3_expected_result):
        print("Passed test 3!\n")
    else:
        print_wrong_output(test3, test3_expected_result, 3)

    if (test5 == test5_expected_result):
        print("Passed test 5!\n")
    else:
        print_wrong_output(test5, test5_expected_result, 5)

    if (test7 == test7_expected_result):
        print("Passed test 7!\n")
    else:
        print_wrong_output(test7, test7_expected_result, 7)

    if (test9 == test9_expected_result):
        print("Passed test 9!\n")
    else:
        print_wrong_output(test9, test9_expected_result, 9)

    if (test11 == test11_expected_result):
        print("Passed test 11!\n")
    else:
        print_wrong_output(test11, test11_expected_result, 11)
    

if __name__ == '__main__':
    main()

