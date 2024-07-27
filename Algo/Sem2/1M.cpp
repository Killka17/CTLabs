#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class SegmentTree {
public:
    SegmentTree(int size) : size(size) {
        tree.resize(2 * size, 0);
    }

    void upd(int ind, int val) {
        ind += size;
        while (ind > 0) {
            tree[ind] += val;
            ind /= 2;
        }
    }

    int q(int l, int r) {
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

std::map<int, int> coord(const std::vector<int>& coords) {
    std::set<int> sorted_coords(coords.begin(), coords.end());
    std::map<int, int> coord_map;
    int idx = 0;
    for (int coord : sorted_coords) {
        coord_map[coord] = idx++;
    }
    return coord_map;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> stars(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> stars[i].first >> stars[i].second;
    }

    std::vector<int> x_coords(n);
    for (int i = 0; i < n; ++i) {
        x_coords[i] = stars[i].first;
    }

    auto x_map = coord(x_coords);
    SegmentTree seg_tree(x_map.size());
    std::vector<int> lvl(n, 0);

    for (const auto& star : stars) {
        int x = star.first;
        lvl[seg_tree.q(0, x_map[x] + 1)] += 1;
        seg_tree.upd(x_map[x], 1);
    }

    for (int ans : lvl) {
        std::cout << ans << std::endl;
    }

    return 0;
}
