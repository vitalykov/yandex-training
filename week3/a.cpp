#include <iostream>

int main() {
    unsigned long long x;
    std::cin >> x;
    // std::cout << std::popcount(x) << '\n';  // short solution using c++20 feature
    int ones_count = 0;

    while (x) {
        ones_count += static_cast<int>(x & 1);
        x >>= 1;
    }

    std::cout << ones_count << '\n';

    return 0;
}