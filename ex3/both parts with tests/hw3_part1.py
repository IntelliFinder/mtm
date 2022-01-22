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

