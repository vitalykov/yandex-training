#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> bars(n);
    for (int& bar : bars) {
        std::cin >> bar;
    }

    std::vector<bool> weights(m + 1, false);
    weights[0] = true;

    for (const auto& bar : bars) {
        if (bar > m) {
            continue;
        }

        for (int i = m - bar; i >= 0; --i) {
            if (weights[i] == true) {
                weights[i + bar] = true;
            }
        }
    }

    for (int i = m; i >= 0; --i) {
        if (weights[i] == true) {
            std::cout << i << '\n';
            break;
        }
    }

    return 0;
}