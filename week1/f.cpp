#include <iostream>
#include <vector>
#include <algorithm>

struct Weight {
    int total_cost;
    int last_bar;
};

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> masses(n + 1);
    std::vector<int> costs(n + 1);
    
    for (size_t i = 1; i < masses.size(); ++i) {
        std::cin >> masses[i];
    }
    for (size_t i = 1; i < costs.size(); ++i) {
        std::cin >> costs[i];
    }

    std::vector<std::vector<Weight>> weights(n + 1, std::vector<Weight>(m + 1, {-1, -1}));
    weights[0][0] = {0, 0};

    for (size_t j = 1; j < n + 1; ++j) {
        auto& mass = masses[j];
        auto& cost = costs[j];
        
        weights[j] = weights[j - 1];

        if (mass > m) {
            continue;
        }

        for (int i = m - mass; i >= 0; --i) {
            int& old_cost = weights[j][i].total_cost;
            int& new_cost = weights[j][i + mass].total_cost;

            if (old_cost > -1) {
                if (old_cost + cost > new_cost) {
                    new_cost = old_cost + cost;
                    weights[j][i + mass].last_bar = j;
                }
            }
        }
    }

    auto& row = weights[weights.size() - 1];

    size_t max_weight = 0;
    int max_cost = 0;
    
    for (size_t i = 1; i < row.size(); ++i) {
        if (row[i].total_cost > max_cost) {
            max_weight = i;
            max_cost = row[i].total_cost;
        }
    }

    for (size_t i = weights.size() - 1; i > 0;) {
        auto& row = weights[i];
        int& bar_index = row[max_weight].last_bar;
        if (bar_index == 0) {
            break;
        }
        
        std::cout << bar_index << '\n';
        i = bar_index - 1;
        // --i;
        max_weight -= masses[bar_index];
    }

    return 0;
}