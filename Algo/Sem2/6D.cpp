#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 2, -1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> L(n + 2, 0);
    vector<int> R(n + 2, 0);

    long long res = static_cast<long long>(n) * (n + 1) / 2;
    R[n] = n + 1;

    for (int i = 1; i <= n; ++i) {
        L[i] = i - 1;
        while ((a[i] | a[L[i]]) == a[i]) {
            L[i] = L[L[i]];
        }
    }

    for (int i = n; i >= 1; --i) {
        R[i] = i + 1;
        while ((a[i] | a[R[i]]) == a[i] && a[R[i]] < a[i]) {
            R[i] = R[R[i]];
        }
    }

    for (int i = 1; i <= n; ++i) {
        res -= static_cast<long long>(i - L[i]) * (R[i] - i);
    }

    cout << res << endl;
    return 0;
}
