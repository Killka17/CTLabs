#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#define fi first
#define se second

using namespace std;


map<int, int> num;
map<int, int> y;

struct node{
    int l, r;
    int mn, mncnt;
    int pl;

    node() = default;
};

struct Tree{
    vector<node> t;
    int sum = 0;

    explicit Tree() {
        t.resize((num.size() - 1) * 4);
        build(0, (num.size() - 1), 0);
    }

    void build(int l, int r, int v) {
        t[v].l = l;
        t[v].r = r;
        if (l == r - 1) {
            t[v].mn = 0;
            t[v].mncnt = y[l + 1] - y[l];
            sum += t[v].mncnt;
            return;
        }
        int m = (l + r) / 2;
        build(l, m, 2 * v + 1);
        build(m, r, 2 * v + 2);
        update(v);
    }

    void update(int v) {
        int l = 2 * v + 1, r = 2 * v + 2;
        if (t[l].mn == t[r].mn) {
            t[v].mn = t[l].mn;
            t[v].mncnt = t[l].mncnt + t[r].mncnt;
            return;
        }
        if (t[l].mn < t[r].mn) {
            t[v].mn = t[l].mn;
            t[v].mncnt = t[l].mncnt;
            return;
        }
        t[v].mn = t[r].mn;
        t[v].mncnt = t[r].mncnt;
    }

    void push(int v) {
        t[v].mn += t[v].pl;
        if (t[v].r - t[v].l != 1) {
            t[2 * v + 1].pl += t[v].pl;
            t[2 * v + 2].pl += t[v].pl;
        }
        t[v].pl = 0;
    }

    int cnt() {
        push(0);
        if (t[0].mn == 0) {
            return sum - t[0].mncnt;
        } else {
            return sum;
        }
    }

    void add(int l, int r, int k) {
        int l1 = num[l], r1 = num[r];
        add(l1, r1, 0, k);
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
    if (n == 0) {
        cout << 0;
        return 0;
    }
    vector<int> y3;
    vector<pair<pair<int, int>, pair<int, int>>> a;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        y3.push_back(y1);
        y3.push_back(y2);
        a.push_back({{x1, 0}, {y1, y2}});
        a.push_back({{x2, 1}, {y1, y2}});
    }
    sort(y3.begin(), y3.end());
    sort(a.begin(), a.end());
    int k = 0;
    for (int i : y3) {
        if (num.find(i) == num.end()) {
            num[i] = k;
            y[k] = i;
            k++;
        }
    }
    Tree b;
    b.add(a[0].se.fi, a[0].se.se, 1);
    long long ans = 0;
    for (int i = 1; i < a.size(); i++) {
        int d = a[i].fi.fi - a[i - 1].fi.fi;
        ans += 1ll * d * b.cnt();
        if (a[i].fi.se) {
            b.add(a[i].se.fi, a[i].se.se, -1);
        } else {
            b.add(a[i].se.fi, a[i].se.se, 1);
        }
    }
    cout << ans;
    return 0;
}
