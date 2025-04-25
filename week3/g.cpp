#include <iostream>
#include <vector>

inline long long SumPrefix(std::vector<long long>& arr, int r) {
    long long result = 0;
    while (r > 0) {
        result += arr[r];
        r -= r & -r;
    }
    return result;
}

inline long long Sum(std::vector<long long>& arr, int l, int r) {
    return SumPrefix(arr, r) - SumPrefix(arr, l - 1);
}

inline void Add(std::vector<long long>& arr, int i, long long value) {
    while (i <= arr.size()) {
        arr[i] += value;
        i += i & -i;
    }
}

inline long long Get(std::vector<long long>& arr, int i) {
    return Sum(arr, i, i);
}

inline void Assign(std::vector<long long>& arr, int i, int value) {
    long long old_value = Get(arr, i);
    Add(arr, i, value - old_value);
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> arr(n + 1, 0);

    while (k--) {
        char command;
        std::cin >> command;
        if (command == 'A') {
            int i, value;
            std::cin >> i >> value;
            Assign(arr, i, value);
        } else if (command == 'Q') {
            int l, r;
            std::cin >> l >> r;
            std::cout << Sum(arr, l, r) << '\n';
        }
    }

    return 0;
}