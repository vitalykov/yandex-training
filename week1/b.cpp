#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        size_t n;
        cin >> n;

        vector<int> result;
        int min_value = numeric_limits<int>::max();
        int count = 0;

        for (size_t i = 0; i < n; ++i) {
            int a;
            cin >> a;
            min_value = min(a, min_value);
            
            if (count + 1 > min_value) {
                result.push_back(count);
                count = 0;
                min_value = a;
            }

            ++count;
        }

        result.push_back(count);

        cout << result.size() << '\n';
        for (const int& num : result) {
            cout << num << ' ';
        }
        cout << '\n';
    }
}