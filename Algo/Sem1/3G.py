first = [int(x) for x in input().split()]
second = [int(x) for x in input().split()]
len_a = len(first)
len_b = len(second)
i = 0
counter = 0
while len(second) != 0 and len(first) != 0:
    # for _ in range(10):
    if first[i] == 0 and second[i] == 9:
        res1 = first[i]
        res2 = second[i]
        first.pop(i)
        second.pop(i)
        first.append(res1)
        first.append(res2)
        len_a += 1
        len_b -= 1

    elif second[i] == 0 and first[i] == 9:
        res1 = first[i]
        res2 = second[i]
        first.pop(i)
        second.pop(i)
        second.append(res1)
        second.append(res2)
        len_a -= 1
        len_b += 1

    elif first[i] > second[i]:
        res1 = first[i]
        res2 = second[i]
        first.pop(i)
        second.pop(i)
        first.append(res1)
        first.append(res2)
        len_a += 1
        len_b -= 1

    elif (second[i] == 0 and first[i] == 9) or second[i] > first[i]:
        res1 = first[i]
        res2 = second[i]
        first.pop(i)
        second.pop(i)
        second.append(res1)
        second.append(res2)
        len_a -= 1
        len_b += 1
    counter += 1

    if counter == 10**6:
        print("botva")
        break
if len_a == 0:
    print("second", counter)
elif len_b == 0:
    print("first", counter)