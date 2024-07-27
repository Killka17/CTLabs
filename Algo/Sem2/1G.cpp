#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class SegmentTree {
public:
    SegmentTree(int size) : size(size) {
        tree.resize(2 * size, 0);
    }

    void update(int pos, int value) {
        pos += size;
        tree[pos] += value;
        while (pos > 1) {
            pos /= 2;
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }

    int query(int l, int r) {
        int res = 0;
        l += size;
        r += size;
        while (l < r) {
            if (l % 2 == 1) {
                res += tree[l];
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res += tree[r];
            }
            l /= 2;
            r /= 2;
        }
        return res;
    }

private:
    int size;
    std::vector<int> tree;
};

std::pair<std::vector<int>, int> coord_c(const std::vector<int>& arr) {
    std::vector<int> s_uni(arr);
    std::sort(s_uni.begin(), s_uni.end());
    s_uni.erase(std::unique(s_uni.begin(), s_uni.end()), s_uni.end());

    std::map<int, int> c_m;
    for (int idx = 0; idx < s_uni.size(); ++idx) {
        c_m[s_uni[idx]] = idx;
    }

    std::vector<int> compressed(arr.size());
    for (int i = 0; i < arr.size(); ++i) {
        compressed[i] = c_m[arr[i]];
    }

    return {compressed, static_cast<int>(s_uni.size())};
}

long long cnt_w(int n, const std::vector<int>& a) {
    auto [ca, size] = coord_c(a);

    std::vector<int> l_cnt(n, 0);
    std::vector<int> r_cnt(n, 0);

    SegmentTree l_tree(size);
    for (int j = 0; j < n; ++j) {
        if (ca[j] + 1 < size) {
            l_cnt[j] = l_tree.query(ca[j] + 1, size);
        }
        l_tree.update(ca[j], 1);
    }

    SegmentTree r_tree(size);
    for (int j = n - 1; j >= 0; --j) {
        if (ca[j] > 0) {
            r_cnt[j] = r_tree.query(0, ca[j]);
        }
        r_tree.update(ca[j], 1);
    }

    long long wd = 0;
    for (int j = 0; j < n; ++j) {
        wd += static_cast<long long>(l_cnt[j]) * r_cnt[j];
    }
    return wd;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::cout << cnt_w(n, a) << std::endl;
    return 0;
}
