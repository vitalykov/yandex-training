#include <iostream>
#include <vector>

inline char Check(std::vector<int>& a, size_t l1, size_t l2, size_t k) {
    while (k--) {
        if (a[l1] != a[l2]) {
            return '-';
        }
        ++l1, ++l2;
    }
    return '+';
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (size_t i = 1; i < a.size(); ++i) {
        std::cin >> a[i];
    }

    int q;
    std::cin >> q;
    std::string result {};
    result.reserve(q);
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            size_t l, r;
            int val;
            std::cin >> l >> r >> val;
            while (l <= r) {
                a[l] = val;
                ++l;
            }
        } else {
            size_t l1, l2, k;
            std::cin >> l1 >> l2 >> k;
            result.push_back(Check(a, l1, l2, k));
        }
    }

    std::cout << result << '\n';

    return 0;
}