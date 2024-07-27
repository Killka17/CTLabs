#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <queue>
#include <deque>
#include <unordered_map>
#include <random>
#include <chrono>
#include <cassert>
#include <type_traits>
#include <unordered_set>

#define debug(x) cerr << (#x) << ":\t" << (x) << endl;

#define fi first
#define se second

using namespace std;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

typedef long long ll;
typedef unsigned long long ull;

int solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();

    return 0;
}

struct Tree{
    explicit Tree(vector<int> &a) {
        t.resize(a.size() * 4);
        build(0, a.size(), 0, a);
    }

    pair<int, int> find_max(int l, int r) {
        l--;
        return find_max(l, r, 0);
    }

    void change(int num, int k) {
        num--;
        change(num, k, 0);
    }

    int query(int l, int r) {
        l--;
        return query(l, r, 0).mk;
    }

    int k_zero(int l, int r, int k) {
        l--;
        return k_zero(0, l, r, k);
    }

private:
    struct node{
        int l, r;
        int mx, ind;
        int k0;
        int mk, ml, mr;

        node() = default;
    };

    vector<node> t;

    void build(int l, int r, int v, vector<int> &a) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            if (a[l] == 0) {
                t[v].k0 = 1;
                t[v].mk = 1;
                t[v].ml = 1;
                t[v].mr = 1;
            } else {
                t[v].k0 = 0;
                t[v].mk = 0;
                t[v].ml = 0;
                t[v].mr = 0;
            }
            t[v].mx = a[l];
            t[v].ind = l;
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1, a);
        build(m, r, 2 * v + 2, a);
        update(v);
    }

    void update(int v) {
        t[v].mx = max(t[2 * v + 1].mx, t[2 * v + 2].mx);
        t[v].k0 = t[2 * v + 1].k0 + t[2 * v + 2].k0;
        if (t[2 * v + 1].mx > t[2 * v + 2].mx) {
            t[v].ind = t[2 * v + 1].ind;
        } else {
            t[v].ind = t[2 * v + 2].ind;
        }
        t[v] = unite(t[2 * v + 1], t[2 * v + 2], t[v]);
    }

    pair<int, int> find_max(int l, int r, int v) {
        if (t[v].l >= l && t[v].r <= r) {
            return {t[v].mx, t[v].ind + 1};
        }
        if (t[v].r <= l || t[v].l >= r) {
            return {INT32_MIN, -1};
        }
        return max(find_max(l, r, 2 * v + 1), find_max(l, r, 2 * v + 2));
    }

    void change(int num, int k, int v) {
        if (t[v].l == num && t[v].l == t[v].r - 1) {
            t[v].mx = k;
            if (k == 0) {
                t[v].k0 = 1;
                t[v].ml = 1;
                t[v].mk = 1;
                t[v].mr = 1;
            } else {
                t[v].k0 = 0;
                t[v].ml = 0;
                t[v].mk = 0;
                t[v].mr = 0;
            }
            return;
        }
        if (t[v].l > num || t[v].r <= num) {
            return;
        }
        change(num, k, 2 * v + 1);
        change(num, k, 2 * v + 2);
        update(v);
    }

    node query(int l, int r, int v) {
        if (t[v].l >= l && t[v].r <= r) {
            return t[v];
        }
        node cur{};
        if (t[v].r <= l || t[v].l >= r) {
            cur.l = t[v].l;
            cur.r = t[v].r;
            return cur;
        }
        return unite(query(l, r, 2 * v + 1),
                     query(l, r, 2 * v + 2), cur);
    }


    node unite(node left, node right, node cur) {
        node v{};
        v = cur;
        if (left.mk == left.r - left.l) {
            v.ml = left.ml + right.ml;
            v.mk = max(v.ml, right.mk);
            if (right.mk == right.r - right.l) {
                v.mr = left.ml + right.ml;
                return v;
            }
            v.mr = right.mr;
            return v;
        }
        if (right.mk == right.r - right.l) {
            v.mr = left.mr + right.mr;
            v.mk = max(v.mr, left.mk);
            v.ml = left.ml;
            return v;
        }
        v.ml = left.ml;
        v.mr = right.mr;
        v.mk = max(right.ml + left.mr, max(right.mk, left.mk));
        return v;
    }

    int k_zero(int v, int l, int r, int &count) {
        if (count == 0) {
            return -1;
        }
        if (t[v].l >= l && t[v].r <= r) {
            if (t[v].k0 < count) {
                count -= t[v].k0;
                return -1;
            }
            if (t[v].k0 == count && t[v].r - t[v].l == 1) {
                count = 0;
                return t[v].l + 1;
            }
            int ans1 = k_zero(2 * v + 1, l, r, count);
            int ans2 = k_zero(2 * v + 2, l, r, count);
            return max(ans1, ans2);
        }
        if (t[v].r <= l || t[v].l >= r) {
            return -1;
        }
        int ans1 = k_zero(2 * v + 1, l, r, count);
        int ans2 = k_zero(2 * v + 2, l, r, count);
        return max(ans1, ans2);
    }
};

int solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    Tree b(a);
    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        if (s == "u") {
            int i, x;
            cin >> i >> x;
            b.change(i, x);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            cout << b.k_zero(l, r, k) << ' ';
        }
    }
    return 0;
}
