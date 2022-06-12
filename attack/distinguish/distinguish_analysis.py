from functools import reduce

ROUND = 10000
LEN = 10

def find_same_char_number(str1, str2, len):
    num = 0
    for i in range(len):
        if str1[2 * i] == str2[2 * i] and str1[2 * i + 1] == str2[2 * i + 1]:
            num += 1
    return num

def factorial(x):
    if x == 0:
        return 1
    return reduce(lambda a, b: a * b, range(1, x + 1))

def calculate_theoretical_distribution(total_num, hit_num, len):
    tmp = 1 / 2 ** 8
    return total_num * factorial(len) / factorial(hit_num) / factorial(len-hit_num) * (tmp ** hit_num) * ((1 - tmp) ** (len-hit_num))

def collision_analysis(f_in = "distinguish.output"):
    file = open(f_in)
    num_map = { i:0 for i in range(11) }
    theorical_map = {i: calculate_theoretical_distribution(ROUND, i, LEN) for i in range(11)}
    for i in range(ROUND):
        line1 = file.readline()
        line2 = file.readline()
        num = find_same_char_number(line1, line2, LEN)
        num_map[num] += 1
    print("The theorical distirbution is:")
    print(theorical_map)
    print("The distribution of our function is:")
    print(num_map)

if __name__ == "__main__":
    collision_analysis()