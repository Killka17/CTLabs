#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void processQuery(vector<int> charPositions[], int left, int right, int direction) {
    int startChar = direction ? 0 : 25;
    int step = direction ? 1 : -1;

    int newIndex = --left;

    for (int c = startChar; (direction && c < 26) || (!direction && c >= 0); c += step) {
        auto lower = lower_bound(charPositions[c].begin(), charPositions[c].end(), left);
        auto upper = lower_bound(charPositions[c].begin(), charPositions[c].end(), right);

        for (auto it = lower; it != upper; ++it) {
            *it = newIndex++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int stringLength, queryCount;
    string inputString;
    cin >> stringLength >> queryCount >> inputString;

    vector<int> charPositions[26];
    for (int i = 0; i < stringLength; i++) {
        charPositions[inputString[i] - 'a'].push_back(i);
    }

    while (queryCount--) {
        int left, right, direction;
        cin >> left >> right >> direction;
        processQuery(charPositions, left, right, direction);
    }

    for (int c = 0; c < 26; c++) {
        for (int index : charPositions[c]) {
            inputString[index] = 'a' + c;
        }
    }

    cout << inputString;

    return 0;
}
