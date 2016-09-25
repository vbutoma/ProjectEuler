from collections import defaultdict

ds = lambda x: sum(int(c) for c in str(x))


def get_factors(m):
    f = []
    while m != 1:
        f.append(lp[m])
        m /= lp[m]
    return f


def make_factor(x):
    primes = []
    lp = [0 for _ in range(x + 1)]
    for i in range(2, x + 1):
        if not lp[i]:
            lp[i] = i
            primes.append(i)
        for prime in primes:
            if prime <= lp[i] and i * prime <= x:
                lp[i*prime] = prime
            else:
                break
    return lp


def generate_factors(cur_state, index, primes):
    divisors.add(cur_state)
    if index >= len(primes):
        return
    multiplier = 1
    for power in range(0, primes[index][1] + 1):
        generate_factors(cur_state * multiplier, index + 1, primes)
        multiplier *= primes[index][0]


def get_ans(factors):
    primes = defaultdict(int)
    for factor in factors:
        primes[factor] += 1
    primes = [p for p in primes.items()]
    global divisors
    divisors = set()
    generate_factors(1, 0, primes)
    ans = 1
    n = max(sorted(divisors))
    for divisor in sorted(divisors):
        p, q = divisor,  n // divisor
        if p > q:
            p, q = q, p
        if p == 1:
            ans = max(ans, digits_sum(q))
        else:
            ans = max(ans, d[p] + digits_sum(q))
            ans = max(ans, d[q] + digits_sum(p))
    return ans


def digits_sum(x):
    while True:
        s = ds(x)
        return s if s < 10 else digits_sum(s)

if __name__ == "__main__":
    print digits_sum(12345)

    n = 10**6
    lp = make_factor(n)
    d = [0 for _ in range(n)]
    file = open("results.txt", "w")
    res = 0
    for i in range(2, n):
        d[i] = get_ans(get_factors(i))
        res += d[i]
        file.write(str(i) + ' ' + str(d[i]) + '\n')
    print res