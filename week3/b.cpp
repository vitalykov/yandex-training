#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<char>> matrix(n, std::vector<char>(n));
    for (auto& row : matrix) {
        for (auto& num : row) {
            std::cin >> num;
            num -= '0';
        }
    }

    std::vector<char> result;
    result.reserve(n);

    for (const auto& row : matrix) {
        char x = 0;
        for (const auto& num : row) {
            x |= num;
        }
        result.push_back(x);
    }

    for (const auto& num : result) {
        std::cout << static_cast<int>(num) << ' ';
    }

    return 0;
}