# palindrome
def is_palindrom(str):
    """returns True iff str is a palindrome"""
    # Shai: ran a few tests, seem fine
    for i in range(len(str) // 2):
        if str[i] != str[-i - 1]:
            return False
    return True


def get_palindrom_dict(str):
    """returns dictionary:
    keys are palindrome_size,
    values are the matching subwords"""
    # Shai ran one test
    dict = {}
    for palindrome_size in range(1, len(str) + 1): #why +1 ??
        dict[palindrome_size] = []
        for subword_start_index in range(0, len(str) - palindrome_size + 1):
            subword = str[subword_start_index:subword_start_index + palindrome_size]
            if is_palindrom(subword):
                dict[palindrome_size].append(subword)
        if len(dict[palindrome_size]) == 0:
            dict.pop(palindrome_size)
    return dict


# check_match
def split_by_mod2(str):
    """returns tuple , first is str in odd indexes, second is str in even indexes"""
    left_str = str[::2]
    right_str = str[1::2]
    return left_str, right_str


def check_match(str):
    """returns True iff word made from odd indexes can "swap"
     with the one from even indexes"""
    if len(str) % 2 != 0: #makes sure both str's have same length
        return False
    left_str, right_str = split_by_mod2(str)
    swap_function = {}  # keys are swap char(key) by char(value)
    for i in range(len(left_str)):
        letter_in_left = left_str[i]
        letter_in_right = right_str[i]
        if letter_in_left in swap_function:
            if swap_function[letter_in_left] != letter_in_right:
                #it cant be a function
                return False
        else:
            swap_function[letter_in_left] = letter_in_right
    # there is a valid swap funcntion
    return True

'''
if __name__ == '__main__':
    print(is_palindrom("hello"), "F")
    print(is_palindrom("ab"), "F")

    print(is_palindrom("a"), "T")
    print(is_palindrom("ava"), "T")
    print(is_palindrom("ayttya"), "T")
    print(get_palindrom_dict("AbbAcaBBa"))
    print(get_palindrom_dict("abcdcba"))
    print(get_palindrom_dict("abcddcba"))

    print(split_by_mod2("dkoeoerp"))
    print(check_match("dkoeoerp"),"T")#door, keep
    print(split_by_mod2("xtaptmapld"))
    print(check_match("xtaptmapld"),"T")#xatal,tpmpd
    print(split_by_mod2("dsaadd"))
    print(check_match("dsaadd"),"F")#dad,sad
    print(split_by_mod2("sdaadd"))
    print(check_match("sdaadd"), "T")  # sad,dad, swapped order
    print(split_by_mod2("chheelcpk"))
    print(check_match("chheelcpk"), "F")  #check,help
    print(split_by_mod2("aabbccddeeffgf"))
    print(check_match("aabbccddeeffgf"), "T")

'''

