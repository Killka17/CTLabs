#include <iostream>
#include <vector>

using namespace std;
#define int long long

int hash_f(int n, size_t h_size) {
    return ((n + 239420239420) * 9929 / 7193) % h_size;
}

void insert(vector<vector<int>> &hashtable, int element) {
    bool flag = false;
    int index = hash_f(element, hashtable.size());
    if (hashtable[index].empty()) {
        hashtable[index].push_back(element);
    }
    for (long long j: hashtable[index]) {
        if (j != element) {
            flag = true;
        }
        if (j == element) {
            return;
        }
    }
    if (flag)
        hashtable[index].push_back(element);
}

void delete_(vector<vector<int>> &hashtable, int element) {
    int index = hash_f(element, hashtable.size());
    if (hashtable[index].empty()) {
        return;
    }
    for (long long j = 0; hashtable[index].size() > j; j++) {
        if (hashtable[index][j] == element) {
            swap(hashtable[index][j], hashtable[index][hashtable[index].size() - 1]);
            hashtable[index].pop_back();
            return;
        }
    }
}

bool exists(vector<vector<int>> &hashtable, int element) {
    bool flag = false;
    int index = hash_f(element, hashtable.size());
    if (hashtable[index].empty()) {
        return flag;
    }
    for (long long j: hashtable[index]) {
        if (j != element) {
            flag = false;
        }
        if (j == element) {
            return true;
        }
    }
    return flag;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    vector<vector<int>> hashtable(10000000);
    while (cin) {
        string command;
        int temp_n;
        cin >> command >> temp_n;
        if (command == "insert")
            insert(hashtable, temp_n);

        if (command == "delete")
            delete_(hashtable, temp_n);
        if (command == "exists") {
            if (exists(hashtable, temp_n))
                cout << "true" << '\n';
            else {
                cout << "false" << '\n';
            }
        }
    }
    return 0;
}