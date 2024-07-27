def count_inversions(arr):
    if len(arr) <= 1:
        return 0, arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    inv_count_left, sorted_left = count_inversions(left_half)
    inv_count_right, sorted_right = count_inversions(right_half)

    inv_count_merge, merged_array = merge_and_count_inversions(sorted_left, sorted_right)

    return inv_count_left + inv_count_right + inv_count_merge, merged_array


def merge_and_count_inversions(left, right):
    inv_count = 0
    merged_array = []
    i, j = 0, 0

    while i < len(left) and j < len(right):
        if left[i] > right[j]:
            inv_count += len(left) - i
            merged_array.append(right[j])
            j += 1
        else:
            merged_array.append(left[i])
            i += 1

    merged_array.extend(left[i:])
    merged_array.extend(right[j:])

    return inv_count, merged_array


n = int(input())
arr = list(map(int, input().split()))

result, _ = count_inversions(arr)
print(result)
