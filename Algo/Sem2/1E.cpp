#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
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
    explicit Tree(vector<int> &a) {
        t.resize(a.size() * 4);
        build(0, a.size(), 0, a);
    }

    void change(int num, int k) {
        num--;
        change(num, k, 0);
    }

    int get(int l, int x) {
        l--;
        int ans = get(l, 0, x);
        if (ans == INT32_MAX) {
            return -1;
        }
        return ans;
    }

private:
    struct node{
        int l, r, mx;

        node() = default;
    };

    vector<node> t;

    void build(int l, int r, int v, vector<int> &a) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            t[v].mx = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1, a);
        build(m, r, 2 * v + 2, a);
        update(v);
    }

    void update(int v) {
        t[v].mx = max(t[2 * v + 1].mx, t[2 * v + 2].mx);
    }

    int get(int l, int v, int x) {
        if (t[v].r <= l || t[v].mx < x) {
            return INT32_MAX;
        }
        if (t[v].l >= l) {
            if (t[v].r - t[v].l == 1) {
                return t[v].l + 1;
            }
            if (t[2 * v + 1].mx >= x) {
                return get(l, 2 * v + 1, x);
            } else {
                return get(l, 2 * v + 2, x);
            }
        }
        return min(get(l, 2 * v + 1, x), get(l, 2 * v + 2, x));
    }

    void change(int num, int k, int v) {
        if (t[v].l == num && t[v].l == t[v].r - 1) {
            t[v].mx = k;
            return;
        }
        if (t[v].l > num || t[v].r <= num) {
            return;
        }
        change(num, k, 2 * v + 1);
        change(num, k, 2 * v + 2);
        update(v);
    }
};

int solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    Tree b(a);
    while (m--) {
        int cur, i, x;
        cin >> cur >> i >> x;
        if (cur) {
            cout << b.get(i, x) << '\n';
        } else {
            b.change(i, x);
        }
    }
    return 0;
}
