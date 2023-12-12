from random import randint
import math

lazy_leng = 1000
base_len = 3
base = 10 ** base_len


def norm_vec(a):
    for i in range(len(a) - 1):
        if a[i] < 0:
            a[i] = base + a[i]
            a[i + 1] -= 1
        a[i + 1] += a[i] // base
        a[i] %= base
    while a[-1] >= base:
        a.append(a[-1] // base)
        a[-2] %= base


def print_number(a):
    stri = ""
    for i in range(len(a)):
        if i != 0:
            num = a[-1 - i]
            if num == 0:
                num += 1
            len_num = int(math.log10(num)) + 1
            for j in range(base_len - len_num):
                stri += '0'
        stri += str(a[-1 - i])
    return stri


def print_part_res(a, b, dig):
    print_number(a)
    print(" " + dig + " ", end='')
    print_number(b)
    print()


def print_part_res_with_ans(a, b, c, dig):
    print_number(a)
    print(" " + dig + " ", end='')
    print_number(b)
    print(" = ", end='')
    print_number(c)
    print()


def min_nulls(a):
    k = 0
    for i in range(len(a)):
        if a[i] != 0:
            k = i + 1
    if k == 0:
        return [0]
    if k == len(a):
        return a
    b = []
    for i in range(k):
        b.append(a[i])
    return b


def add_nulls(a, b):
    while len(a) < len(b):
        a.append(0)
    while len(b) < len(a):
        b.append(0)


def sum_vec(a, b):
    add_nulls(a, b)
    c = [0] * len(a)
    for i in range(len(b)):
        c[i] = a[i] + b[i]
    norm_vec(c)
    return c


def sub_vec(a, b):
    add_nulls(a, b)
    c = [0] * len(a)
    for i in range(len(b)):
        c[i] = a[i] - b[i]
    norm_vec(c)
    return c


def mul_vec(a, b):
    add_nulls(a, b)
    c = [0] * (2 * len(a))
    if len(b) < lazy_leng:
        for i in range(len(a)):
            for j in range(len(b)):
                c[i + j] += a[i] * b[j]
    else:
        k = len(a) // 2
        a1, a2, b1, b2 = [], [], [], []
        for i in range(k):
            a1.append(a[i])
            b1.append(b[i])
        for i in range(k, len(a)):
            a2.append(a[i])
            b2.append(b[i])
        a1b1 = mul_vec(a1, b1)
        a2b2 = mul_vec(a2, b2)
        a1_a2 = sum_vec(a1, a2)
        b1_b2 = sum_vec(b1, b2)
        a1_a2b1_b2 = mul_vec(a1_a2, b1_b2)
        part_sub = sub_vec(a1_a2b1_b2, a1b1)
        a1b2_a2b1 = sub_vec(part_sub, a2b2)
        a1b1 = min_nulls(a1b1)
        a2b2 = min_nulls(a2b2)
        a1b2_a2b1 = min_nulls(a1b2_a2b1)
        for i in range(len(a1b1)):
            c[i] += a1b1[i]
        for i in range(2 * k, 2 * k + len(a2b2)):
            c[i] += a2b2[i - 2 * k]
        for i in range(k, k + len(a1b2_a2b1)):
            c[i] += a1b2_a2b1[i - k]
    return c


# v1 = input()
# v2 = input()
cnst = 10 ** 10
epoch = 10 ** 6
for i in range(epoch):
    aa = randint(-cnst, cnst)
    v1 = str(aa)
    bb = randint(-cnst, cnst)
    v2 = str(bb)
    less_zero = False
    if ((v1[0] == '-' and v2[0] != '-') or (v1[0] != '-' and v2[0] == '-')):
        less_zero = True
    leng = max(len(v1) - (1 if v1[0] == '-' else 0), len(v2) - (1 if v2[0] == '-' else 0))
    vec_len = ((leng + base_len) // base_len)
    val1 = [0] * vec_len
    val2 = [0] * vec_len
    k = 0
    for i in range(len(v1) - 1, -1, -base_len):
        a = 0
        for j in range(base_len - 1, -1, -1):
            if (i - j >= 0) and (v1[i - j] != '-'):
                a *= 10
                a += ord(v1[i - j]) - ord('0')
        val1[k] = a
        k += 1
    k = 0
    for i in range(len(v2) - 1, -1, -base_len):
        a = 0
        for j in range(base_len - 1, -1, -1):
            if (i - j >= 0) and (v2[i - j] != '-'):
                a *= 10
                a += ord(v2[i - j]) - ord('0')
        val2[k] = a
        k += 1
    # if less_zero:
    #     print('-')
    if(aa == 0 or bb == 0):
        print(0)
    ans = mul_vec(val1, val2)
    norm_vec(ans)
    ans = min_nulls(ans)
    l = print_number(ans)
    if len(l) == 1 and l == "0":
        less_zero = False
    if less_zero:
        l = '-' + l
    if str(aa * bb) != l:
        print(aa, bb, aa * bb, l)
        print()
