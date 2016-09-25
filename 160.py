from math import log


def power(n, prime):
    res = 0
    while n:
        n /= prime
        res += n
    return res


def f(n):
    #n = base * p + q
    return (product[base] ** (n / base) * product[n % base]) % base


N = 10**12
base = 10**5

product = [0 for _ in range(base + 1)]
p = product[0] = 1

for i in range(1, base + 1):
    if i % 2 and i % 5:
        p = (p * i) % base
    product[i] = p

result = 1

for p2 in range(0, int(log(N) / log(2)) + 1):
    for p5 in range(0, int(log(N) / log(5)) + 1):
        number = (2**p2) * (5**p5)
        if number > N:
            break
        result = (result * f(N / number)) % base


print (result * pow(2, power(N, 2) - power(N, 5), base)) % base
