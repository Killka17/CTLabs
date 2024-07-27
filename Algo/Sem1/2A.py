def binary_search(arr, x):
    l = 0
    r = len(arr)
    mid = l + (r - l) // 2
    while r - l > 1:
        if arr[mid] <= x:
            l = mid
        else:
            r = mid
        mid = l + (r - l) // 2

    if arr[l] == x:
        return 1
    else:
        return 0


n, k = map(int, input().split())
first_arr = [int(x) for x in input().split()]
second_arr = [int(x) for x in input().split()]
for i in range(k):
    if binary_search(first_arr, second_arr[i]):
        print("YES")
    else:
        print("NO")