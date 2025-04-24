#include <iostream>
#include <bit>

inline unsigned ClosestGreaterPowerOfTwo(unsigned a) {
    return 1U << (8 * sizeof(a) - std::countl_zero(a));
}

unsigned FindLabel(unsigned x, unsigned y) {
    if (y > x) {
        unsigned temp = y;
        y = x;
        x = temp;
    }

    while (y != 0U) {
        unsigned len = ClosestGreaterPowerOfTwo(y);
        unsigned half_len = len >> 1;
        unsigned x0 = x - (x % len);
        x = (x0 + (x + half_len) % len);
        y = (y + half_len) % len;
    }

    return x;
}

unsigned FindY(unsigned x, unsigned c) {
    unsigned target = x;
    x = 0;
    unsigned y = c;

    while (x != target) {
        unsigned len = ClosestGreaterPowerOfTwo(target - x);
        unsigned half_len = len >> 1;
        unsigned x0 = x - (x % len);
        unsigned y0 = y - (y % len);
        x = x0 + (x + half_len) % len;
        y = y0 + (y + half_len) % len;
    }

    return y;
}

int main() {
    unsigned x, y, c;
    std::cin >> x >> y;
    std::cout << FindLabel(x, y) << '\n';
    std::cin >> x >> c;
    std::cout << FindY(x, c) << '\n';

    return 0;
}