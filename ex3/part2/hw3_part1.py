def find_best_selling_product(file_name):
    file = open(file_name, 'r')
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

def is_name_in_dict(dict, name):
    """returns true if name is in list of values of dict"""
    for key in dict.keys():
        if name in dict[key]:
            return True
    return False


def find_k_most_expensive_products(file_name, k):
    file = open(file_name, 'r')
    sequence = [line.split() for line in file]
    file.close()
    price_to_names_dict = {}
    for item in sequence:
        if item[0] == 'add' and item[1] == 'product':
            name, price = item[2], float(item[3])
            if is_name_in_dict(price_to_names_dict, name):
                continue
            if price not in price_to_names_dict:
                price_to_names_dict[price] = [name]
            else:
                price_to_names_dict[price].append(name)
    sorted_price_list = sorted([price for price in price_to_names_dict.keys()])
    sorted_price_list.reverse()
    final = []
    for price in sorted_price_list:
        to_add = sorted([name for name in price_to_names_dict[price]])
        final.extend(to_add[0:max(0, k - len(final))])
    return final


def main():
    test1 = find_best_selling_product("hw3_part1_tests_files/items1.txt")
    test1_expected_result = ('baloon', 5600)
    test2 = find_k_most_expensive_products("hw3_part1_tests_files/items1.txt", 3)
    test2_expected_result = ['chair', 'lamp', 'pizza']
    test3 = find_best_selling_product("hw3_part1_tests_files/items2.txt")
    test3_expected_result = ('pineapple', 23200)
    test4 = find_k_most_expensive_products("hw3_part1_tests_files/items2.txt", 3)
    test4_expected_result = ['banana', 'pineapple', 'bike']
    test5 = find_best_selling_product("hw3_part1_tests_files/items3.txt")
    test5_expected_result = ('apple', 9500)
    test7 = find_best_selling_product("hw3_part1_tests_files/items4.txt")
    test7_expected_result = ('pizza', 43350)
    test9 = find_best_selling_product("hw3_part1_tests_files/items5.txt")
    test9_expected_result = ('', 0)
    test11 = find_best_selling_product("hw3_part1_tests_files/items6.txt")
    test11_expected_result = ('bike', 52200)
    test6 = find_k_most_expensive_products("hw3_part1_tests_files/items3.txt", 7)
    test6_expected_result = ['apple', 'banana', 'bike', 'chair', 'lamp', 'phone', 'pineapple']
    test8 = find_k_most_expensive_products("hw3_part1_tests_files/items4.txt", 7)
    test8_expected_result = ['apple', 'baloon', 'pizza', 'bike', 'pineapple', 'phone', 'chair']
    test10 = find_k_most_expensive_products("hw3_part1_tests_files/items5.txt", 3)
    test10_expected_result = []
    test12 = find_k_most_expensive_products("hw3_part1_tests_files/items6.txt", 7)
    test12_expected_result = ['apple', 'lamp', 'bike', 'banana', 'chair', 'pineapple', 'phone']

    if (test1 == test1_expected_result):
        print("Passed test 1!\n")
    else:
        print_wrong_output(test1, test1_expected_result, 1)

    if (test2 == test2_expected_result):
        print("Passed test 2!\n")
    else:
        print_wrong_output(test2, test2_expected_result, 2)

    if (test3 == test3_expected_result):
        print("Passed test 3!\n")
    else:
        print_wrong_output(test3, test3_expected_result, 3)

    if (test4 == test4_expected_result):
        print("Passed test 4!\n")
    else:
        print_wrong_output(test4, test4_expected_result, 4)

    if (test5 == test5_expected_result):
        print("Passed test 5!\n")
    else:
        print_wrong_output(test5, test5_expected_result, 5)

    if (test6 == test6_expected_result):
        print("Passed test 6!\n")
    else:
        print_wrong_output(test6, test6_expected_result, 6)

    if (test7 == test7_expected_result):
        print("Passed test 7!\n")
    else:
        print_wrong_output(test7, test7_expected_result, 7)

    if (test8 == test8_expected_result):
        print("Passed test 8!\n")
    else:
        print_wrong_output(test8, test8_expected_result, 8)

    if (test9 == test9_expected_result):
        print("Passed test 9!\n")
    else:
        print_wrong_output(test9, test9_expected_result, 9)

    if (test10 == test10_expected_result):
        print("Passed test 10!\n")
    else:
        print_wrong_output(test10, test10_expected_result, 10)

    if (test11 == test11_expected_result):
        print("Passed test 11!\n")
    else:
        print_wrong_output(test11, test11_expected_result, 11)

    if (test12 == test12_expected_result):
        print("Passed test 12!\n")
    else:
        print_wrong_output(test12, test12_expected_result, 12)


if __name__ == '__main__':
    main()

