#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <algorithm>
#include <array>

using namespace std;
vector<int> a;
vector<int> a_srt;
int ans = 0;

void mrg(int left, int med, int right) {
    int i = left, j = med + 1;
    while (i <= med && j <= right) {
        if (a[i] > a[j]) {
            ans += med - i + 1;
            a_srt.push_back(a[j]);
            j++;
        } else {
            a_srt.push_back(a[i]);
            i++;
        }
    }
    while (j <= right) {
        a_srt.push_back(a[j]);
        j++;
    }
    while (i <= med) {
        a_srt.push_back(a[i]);
        i++;
    }
    for (int ji = left; ji <= right; ji++) {
        a[ji] = a_srt[ji - left];
    }
    a_srt.clear();
}

void cut(int left, int right) {
    if (right != left) {
        int med = (right + left) / 2;
        cut(left, med);
        cut(med + 1, right);
        mrg(left, med, right);
    }
}

int main() {
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cut(0, n - 1);
    cout << ans;
    return 0;
}