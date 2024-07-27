#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;

struct node{
    int l, r;
    int sum;
    bool xr;

    node() = default;
};

struct Tree{
    vector<node> t;
    int num;

    explicit Tree(vector<int> &a, int num) {
        this->num = num;
        t.resize(a.size() * 4);
        build(0, a.size(), 0, a);
    }

    void build(int l, int r, int v, vector<int> &a) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            t[v].sum = ((a[l] & (1 << num)) > 0);
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1, a);
        build(m, r, 2 * v + 2, a);
        update(v);
    }

    void update(int v) {
        t[v].sum = t[2 * v + 1].sum + t[2 * v + 2].sum;
    }

    void push(int v) {
        if (t[v].xr) {
            t[v].sum = t[v].r - t[v].l - t[v].sum;
        }
        if (t[v].r - t[v].l != 1 && t[v].xr) {
            t[2 * v + 1].xr ^= 1;
            t[2 * v + 2].xr ^= 1;
        }
        t[v].xr = false;
    }

    int get_sum(int l, int r) {
        l--;
        return get_sum(l, r, 0);
    }

    int get_sum(int l, int r, int v) {
        push(v);
        if (t[v].l >= l && t[v].r <= r) {
            return t[v].sum;
        }
        if (t[v].r <= l || t[v].l >= r) {
            return 0;
        }
        return get_sum(l, r, 2 * v + 1) + get_sum(l, r, 2 * v + 2);
    }

    void add(int l, int r, int k) {
        l--;
        k &= (1 << num);
        if (k) {
            add1(l, r, 0);
        }
    }

    void add1(int l, int r, int v) {
        push(v);
        if (t[v].l >= l && t[v].r <= r) {
            t[v].xr ^= 1;
            push(v);
            return;
        }
        if (t[v].r <= l || t[v].l >= r) {
            return;
        }
        add1(l, r, 2 * v + 1);
        add1(l, r, 2 * v + 2);
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
    vector<Tree> b;
    for (int i = 0; i <= 20; i++) {
        Tree c(a, i);
        b.push_back(c);
    }
    int m;
    cin >> m;
    while (m--) {
        int c;
        cin >> c;
        if (c == 1) {
            int l, r;
            cin >> l >> r;
            long long ans = 0;
            for (int i = 0; i <= 20; i++) {
                ans += 1ll * (1 << i) * b[i].get_sum(l, r);
            }
            cout << ans << '\n';
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            for (int i = 0; i <= 20; i++) {
                b[i].add(l, r, k);
            }
        }
    }
    return 0;
}
