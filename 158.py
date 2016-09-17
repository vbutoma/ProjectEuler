from math import factorial as f

size = 26


def C(m, n):
    return f(m)//f(n)//f(m - n)


def p(n):
    return (2**n - n - 1) * C(size, n)

print max([p(i) for i in range((size + 1))])
