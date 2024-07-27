#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<long> sec_vec;
struct tree_seg {
    long l_border, r_border, fir_sum, sec_sum;
};

struct tree {
    vector<tree_seg> tree_sum;

    tree() {
        tree_sum.resize(sec_vec.size() * 4 + 1);
        bld(1, 0, sec_vec.size() - 1);
    }

    void bld(long v, long l_border, long r_border) {
        tree_sum[v].l_border = l_border;
        tree_sum[v].r_border = r_border;
        if (l_border == r_border) {
            if (l_border % 2 == 1) {
                tree_sum[v].sec_sum = -1 * sec_vec[l_border];
                tree_sum[v].fir_sum = sec_vec[l_border];
            } else {
                tree_sum[v].fir_sum = -1 * sec_vec[l_border];
                tree_sum[v].sec_sum = sec_vec[l_border];
            }
        } else {
            long m = (r_border + l_border) / 2;
            bld(2 * v + 1, m + 1, r_border);
            bld(2 * v, l_border, m);
            upd(v);
        }
    }

    void upd(long v) {
        tree_sum[v].fir_sum = tree_sum[2 * v].fir_sum + tree_sum[2 * v + 1].fir_sum;
        tree_sum[v].sec_sum = tree_sum[2 * v].sec_sum + tree_sum[2 * v + 1].sec_sum;
    }

    int sum2(long l_border, long r_border, long v) {
        if (l_border <= tree_sum[v].l_border && r_border >= tree_sum[v].r_border) {
            return tree_sum[v].sec_sum;
        } else if (l_border > tree_sum[v].r_border || r_border < tree_sum[v].l_border) {
            return 0;
        } else {
            return sum2(l_border, r_border, 2 * v) + sum2(l_border, r_border, 2 * v + 1);
        }
    }

    int sum1(long l_border, long r_border, long v) {
        if (l_border <= tree_sum[v].l_border && r_border >= tree_sum[v].r_border) {
            return tree_sum[v].fir_sum;
        } else if (l_border > tree_sum[v].r_border || r_border < tree_sum[v].l_border) {
            return 0;
        } else {
            return sum1(l_border, r_border, 2 * v) + sum1(l_border, r_border, 2 * v + 1);
        }
    }

    long sum(long l_border, long r_border) {
        l_border--;
        r_border--;
        if (l_border == r_border) {
            return abs(sum1(l_border, r_border, 1));
        } else if (l_border % 2 == 1) {
            return sum1(l_border, r_border, 1);
        } else {
            return sum2(l_border, r_border, 1);
        }
    }

    void change(long number, long k) {
        number--;
        change(1, number, k);
    }

    void change(long v, long number, long k) {
        if (number == tree_sum[v].l_border && number == tree_sum[v].r_border) {
            if (number % 2 == 1) {
                tree_sum[v].fir_sum = k;
                tree_sum[v].sec_sum = k * -1;
            } else {
                tree_sum[v].fir_sum = k * -1;
                tree_sum[v].sec_sum = k;
            }
        } else if (number >= tree_sum[v].l_border && number <= tree_sum[v].r_border) {
            change(2 * v, number, k);
            change(2 * v + 1, number, k);
            upd(v);
        }
    }
};

signed main() {
    int n;
    cin >> n;
    sec_vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> sec_vec[i];
    }
    tree a;
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        char s;
        long var, var1;
        cin >> s >> var >> var1;
        if (s == '1') {
            cout << a.sum(var, var1) << '\n';
        } else {
            a.change(var, var1);
        }
    }
    return 0;
}