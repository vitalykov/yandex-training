#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<size_t> pigs(n + 1);
    for (size_t i = 0; i < pigs.size(); ++i) {
        pigs[i] = i;
    }
    for (size_t i = 1; i < pigs.size(); ++i) {
        size_t parent;
        std::cin >> parent;
        while (parent != pigs[parent]) {
            parent = pigs[parent];
        }
        pigs[i] = parent;
    }
    int sum = 0;
    for (size_t i = 1; i < pigs.size(); ++i) {
        if (i == pigs[i]) {
            ++sum;
        }
    }

    std::cout << sum << '\n';

    return 0;
}