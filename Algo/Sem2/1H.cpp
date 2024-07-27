#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <random>
#include <chrono>
using namespace std;

int solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();

    return 0;
}

struct Tree{
    explicit Tree(string &s) {
        t.resize(s.size() * 4);
        build(0, s.size(), 0, s);
    }

    int find(int l, int r) {
        l--;
        return find(l, r, 0).ans;
    }

private:
    struct node{
        int l, r, ans, sum0, sum1;

        node() = default;
    };

    vector<node> t;

    void build(int l, int r, int v, string &s) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            if (s[l] == '(') {
                t[v].sum0 = 1;
            } else {
                t[v].sum1 = 1;
            }
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1, s);
        build(m, r, 2 * v + 2, s);
        update(v);
    }

    void update(int v) {
        t[v] = unit(t[2 * v + 1], t[2 * v + 2]);
    }

    node find(int l, int r, int v) {
        if (t[v].l >= r || t[v].r <= l) {
            node cur{};
            return cur;
        }
        if (t[v].l >= l && t[v].r <= r) {
            return t[v];
        }
        return unit(find(l, r, 2 * v + 1),
                    find(l, r, 2 * v + 2));
    }

    node unit(node left, node right) {
        node cur{};
        cur.l = left.l;
        cur.r = right.r;
        cur.sum0 = left.sum0 + right.sum0;
        cur.sum1 = left.sum1 + right.sum1;
        cur.ans = left.ans + right.ans
                  + 2 * min(left.sum0 - left.ans / 2,
                            right.sum1 - right.ans / 2);
        return cur;
    }
};

int solve() {
    string s;
    cin >> s;
    Tree b(s);
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << b.find(l, r) << '\n';
    }
    return 0;
}
