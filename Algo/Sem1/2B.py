def binary_search(arr, x):
    first = -1
    l = 0
    r = len(arr) - 1
    mid = l + (r - l) // 2
    while l <= r:
        if arr[mid] == x:
            first = mid
            r = mid - 1
        elif arr[mid] < x:
            l = mid + 1
        else:
            r = mid - 1
        mid = l + (r - l) // 2
    return first + 1

def binary_search2(arr, x):
    second = -1
    l = 0
    r = len(arr) - 1
    mid = l + (r - l) // 2
    while l <= r:
        if arr[mid] == x:
            second = mid
            l = mid + 1
        elif arr[mid] < x:
            l = mid + 1
        else:
            r = mid - 1
        mid = l + (r - l) // 2
    return second + 1


n, k = map(int, input().split())
first_arr = [int(x) for x in input().split()]
second_arr = [int(x) for x in input().split()]
for numb in second_arr:
    if binary_search2(first_arr, numb) == 0:
        print(0)
    else:
        print(binary_search(first_arr, numb), binary_search2(first_arr, numb))