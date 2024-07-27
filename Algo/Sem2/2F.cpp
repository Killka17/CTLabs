#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long mm(int l, int r, vector<long long>& s, long long t) {
    if (l >= r) return 0;

    int mid = (l + r) / 2;
    long long a1 = mm(l, mid, s, t);
    long long a2 = mm(mid + 1, r, s, t);

    long long e = 0;
    int i = l;
    int j = mid + 1;

    while (i <= mid) {
        while (j <= r && s[j] - s[i] < t) {
            j++;
        }
        e += j - (mid + 1);
        i++;
    }

    vector<long long> temp(r - l + 1);
    merge(s.begin() + l, s.begin() + mid + 1, s.begin() + mid + 1, s.begin() + r + 1, temp.begin());
    copy(temp.begin(), temp.end(), s.begin() + l);

    return a1 + a2 + e;
}

int main() {
    int n;
    long long t;
    cin >> n >> t;
    vector<long long> s(n + 1, 0);

    vector<int> val(n);
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }

    for (int i = 1; i <= n; ++i) {
        s[i] = s[i - 1] + val[i - 1];
    }

    cout << mm(0, n, s, t) << endl;
    return 0;
}
