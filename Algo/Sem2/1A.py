class SegmentTree:
    def __init__(self, array):
        self.array = array
        self.tree = [None] * (4 * len(array))
        self.build(0, 0, len(array) - 1)

    def build(self, v, left, right):
        if left == right:
            self.tree[v] = (self.array[left], left)
        else:
            mid = (left + right) // 2
            self.build(2 * v + 1, left, mid)
            self.build(2 * v + 2, mid + 1, right)
            self.tree[v] = max(self.tree[2 * v + 1], self.tree[2 * v + 2])

    def query(self, ql, qr):
        left = 0
        right = len(self.array) - 1
        v = 0
        result = (-float('inf'), -1)
        stack = [(v, left, right)]
        while stack:
            v, left, right = stack.pop()
            if ql > right or qr < left:
                continue
            if ql <= left and qr >= right:
                result = max(result, self.tree[v])
            else:
                mid = (left + right) // 2
                stack.append((2 * v + 1, left, mid))
                stack.append((2 * v + 2, mid + 1, right))
        return result

def main():
    N = int(input())
    array = list(map(int, input().split()))

    seg_tree = SegmentTree(array)

    K = int(input())
    for _ in range(K):
        l, r = map(int, input().split())
        max_val, max_index = seg_tree.query(l - 1, r - 1)
        print(max_val, max_index + 1)

if __name__ == "__main__":
    main()
