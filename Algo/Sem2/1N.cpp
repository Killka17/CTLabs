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

struct node{
    int l, r;
    int sum;

    node() = default;
};

struct Tree{
    vector<node> t;

    explicit Tree(int n) {
        t.resize(n * 4);
        build(0, n, 0);
    }

    void build(int l, int r, int v) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            t[v].sum = 0;
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1);
        build(m, r, 2 * v + 2);
        update(v);
    }

    void update(int v) {
        int l = 2 * v + 1, r = 2 * v + 2;
        t[v].sum = t[l].sum + t[r].sum;
    }

    void change(int c, int k) {
        change(c, 0, k);
    }

    void change(int c, int v, int k) {
        if (t[v].l == c && t[v].r == t[v].l + 1) {
            t[v].sum = k;
            return;
        }
        if (t[v].r <= c || t[v].l > c) {
            return;
        }
        change(c, 2 * v + 1, k);
        change(c, 2 * v + 2, k);
        update(v);
    }

    int sum(int l, int r) {
        r++;
        return sum(l, r, 0);
    }

    int sum(int l, int r, int v) {
        if (t[v].l >= l && t[v].r <= r) {
            return t[v].sum;
        }
        if (t[v].r <= l || t[v].l >= r) {
            return 0;
        }
        return sum(l, r, 2 * v + 1) + sum(l, r, 2 * v + 2);
    }
};

int solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    int q;
    cin >> q;
    vector<pair<pair<int, int>, int>> b(q);
    int k = 0;
    for (auto &i : b) {
        cin >> i.fi.se >> i.fi.fi;
        i.fi.se--;
        i.fi.fi--;
        i.se = k;
        k++;
    }
    sort(b.begin(), b.end());
    int cur = 0;
    Tree cnt(n);
    vector<int> ans(q);
    map<int, int> last;
    k = 0;
    for (int i : a) {
        if (last.find(i) != last.end()) {
            cnt.change(last[i], 0);
        }
        last[i] = k;
        cnt.change(k, 1);
        while (cur < q && b[cur].fi.fi == k) {
            int l = b[cur].fi.se, r = b[cur].fi.fi, num = b[cur].se;
            ans[num] = cnt.sum(l, r);
            cur++;
        }
        if (cur == q) {
            break;
        }
        k++;
    }
    for (int i : ans) {
        cout << i << '\n';
    }
    return 0;
}