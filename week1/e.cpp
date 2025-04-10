#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> masses(n);
    std::vector<int> costs(n);
    
    for (auto& mass : masses) {
        std::cin >> mass;
    }
    for (auto& cost : costs) {
        std::cin >> cost;
    }

    std::vector<int> weights(m + 1, -1);
    weights[0] = 0;

    for (size_t j = 0; j < n; ++j) {
        auto& mass = masses[j];
        auto& cost = costs[j];

        if (mass > m) {
            continue;
        }

        for (int i = m - mass; i >= 0; --i) {
            if (weights[i] > -1) {
                weights[i + mass] = std::max(cost + weights[i], weights[i + mass]);
            }
        }
    }

    std::cout << *std::max_element(weights.begin(), weights.end()) << '\n';

    return 0;
}