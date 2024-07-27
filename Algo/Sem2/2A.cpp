#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using namespace std;

struct node{
    int l, r;
    int mx;
    int pl;

    node() = default;
};

struct Tree{
    vector<node> t;

    explicit Tree(vector<int> &a) {
        t.resize(a.size() * 4);
        build(0, a.size(), 0, a);
    }

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

    void push(int v) {
        t[v].mx += t[v].pl;
        if (t[v].r - t[v].l != 1) {
            t[2 * v + 1].pl += t[v].pl;
            t[2 * v + 2].pl += t[v].pl;
        }
        t[v].pl = 0;
    }

    int find_max(int l, int r) {
        l--;
        return find_max(l, r, 0);
    }

    int find_max(int l, int r, int v) {
        push(v);
        if (t[v].l >= l && t[v].r <= r) {
            return t[v].mx;
        }
        if (t[v].r <= l || t[v].l >= r) {
            return INT32_MIN;
        }
        return max(find_max(l, r, 2 * v + 1), find_max(l, r, 2 * v + 2));
    }

    void add(int l, int r, int k) {
        l--;
        add(l, r, 0, k);
    }

    void add(int l, int r, int v, int k) {
        push(v);
        if (t[v].l >= l && t[v].r <= r) {
            t[v].pl += k;
            push(v);
            return;
        }
        if (t[v].r <= l || t[v].l >= r) {
            return;
        }
        add(l, r, 2 * v + 1, k);
        add(l, r, 2 * v + 2, k);
        update(v);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
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
        char c;
        cin >> c;
        if (c == 'a') {
            int l, r, k;
            cin >> l >> r >> k;
            b.add(l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << b.find_max(l, r) << ' ';
        }
    }
    return 0;
}