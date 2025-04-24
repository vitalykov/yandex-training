#include <iostream>
#include <bit>

int main() {
    unsigned a;
    std::cin >> a;
    int digits_count = 8 * sizeof(a) - std::countl_zero(a);
    unsigned max_a = a;

    for (int i = 0; i < digits_count; ++i) {
        unsigned last = (a & 1) << (digits_count - 1);
        a = (a >> 1) + last;
        if (a > max_a) {
            max_a = a;
        }
    }

    std::cout << max_a << '\n';

    return 0;
}