class SegmentTree:
    def __init__(self, array):
        self.array = array
        self.tree = [None] * (4 * len(array))
        self.build(0, 0, len(array) - 1)

    def build(self, v, left, right):
        if left == right:
            self.tree[v] = (self.array[left], 1)
        else:
            mid = (left + right) // 2
            self.build(2 * v + 1, left, mid)
            self.build(2 * v + 2, mid + 1, right)
            left_max, left_count = self.tree[2 * v + 1]
            right_max, right_count = self.tree[2 * v + 2]
            if left_max > right_max:
                self.tree[v] = (left_max, left_count)
            elif left_max < right_max:
                self.tree[v] = (right_max, right_count)
            else:
                self.tree[v] = (left_max, left_count + right_count)

    def query(self, ql, qr, v=0, left=0, right=None):
        if right is None:
            right = len(self.array) - 1
        if ql > right or qr < left:
            return (-float('inf'), 0)
        if ql <= left and qr >= right:
            return self.tree[v]
        mid = (left + right) // 2
        left_max, left_count = self.query(ql, qr, 2 * v + 1, left, mid)
        right_max, right_count = self.query(ql, qr, 2 * v + 2, mid + 1, right)
        if left_max > right_max:
            return (left_max, left_count)
        elif left_max < right_max:
            return (right_max, right_count)
        else:
            return (left_max, left_count + right_count)


def main():
    N = int(input())
    array = list(map(int, input().split()))

    seg_tree = SegmentTree(array)

    K = int(input())
    for _ in range(K):
        l, r = map(int, input().split())
        max_val, max_count = seg_tree.query(l - 1, r - 1)
        print(max_val, max_count)


if __name__ == "__main__":
    main()
