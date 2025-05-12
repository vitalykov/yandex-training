#include <iostream>
#include <numeric>
#include <vector>

struct Island {
    size_t group;
    size_t group_size;
};

void MergeGroups(std::vector<Island>& islands, size_t g_a, size_t g_dest, size_t a, size_t b) {
    islands[g_a].group = g_dest;
    islands[g_dest].group_size += islands[g_a].group_size;
    g_a = g_dest;
    size_t next = a;
    while (islands[next].group != g_dest) {
        islands[next].group = g_dest;
        next = islands[next].group;
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }

    std::vector<Island> islands(n + 1);
    for (size_t i = 0; i < islands.size(); ++i) {
        islands[i] = {.group = i, .group_size = 1};
    }
    
    for (size_t i = 1; i <= m; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        size_t& group_a = a;
        while (islands[group_a].group != group_a) {
            group_a = islands[group_a].group;
        }
        size_t& group_b = b;
        while (islands[group_b].group != group_b) {
            group_b = islands[group_b].group;
        }
        size_t& group_a_size = islands[group_a].group_size;
        size_t& group_b_size = islands[group_b].group_size;
        if (group_a != group_b) {
            if (group_a_size < group_b_size) {
                MergeGroups(islands, group_a, group_b, a, b);
                if (group_b_size == n) {
                    std::cout << i << '\n';
                    break;
                }
            } else {
                MergeGroups(islands, group_b, group_a, b, a);
                if (group_a_size == n) {
                    std::cout << i << '\n';
                    break;
                }
            }
        }
    }

    return 0;
}