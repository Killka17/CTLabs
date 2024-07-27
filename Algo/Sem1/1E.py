def raspred(barrel, arr_count, count, mesto):
    counter = 0
    for i in range(arr_count):
        while count > 0 and barrel[i] >= mesto:
            counter += mesto
            barrel[i] -= mesto
            count -= 1
    if count == 0:
        return counter

    barrel = sorted(barrel, reverse=True)
    for i in range(arr_count):
        if count > 0:
            counter += barrel[i]
            count -= 1
    return counter


n, m, p = map(int, input().split())
a = list(map(int, input().split()))
print(raspred(a, n, m, p))



