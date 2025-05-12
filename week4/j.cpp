#include <iostream>
#include <list>

#define BANKRUPTCY 1
#define SPLIT 2

void BankruptFactory(std::list<long long>& factories, std::list<long long>::iterator& it, long long& sum, size_t& i) {
    long long right = 0;
    long long left = 0;
    long long delta = 0;
    if (it == factories.begin()) {
        right = *std::next(it);
        delta = 2 * (*it) * right;
        *it += right;
        factories.erase(std::next(it));
    } else if (it == std::prev(factories.end())) {
        left = *std::prev(it);
        delta = 2 * (*it) * left;
        left += *it;
        std::advance(it, -1);
        *it = left;
        factories.erase(std::next(it));
        --i;
    } else {
        long long l = *it / 2;
        long long r = *it - l;
        auto left = std::prev(it);
        auto right = std::next(it);
        delta = 2 * (l * (*left) + r * (*right) - l * r);
        *left += l;
        *right += r;
        std::advance(it, 1);
        factories.erase(std::prev(it));
    }
    sum += delta;
}

void SplitFactory(std::list<long long>& factories, std::list<long long>::iterator& it, long long& sum) {
    long long left = *it / 2;
    long long right = *it - left;
    *it = left;
    factories.insert(std::next(it), right);
    long long delta = left * left + right * right - (*it) * (*it);
    sum += delta;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    long long sum_squares = 0;
    std::list<long long> factories;
    while (n--) {
        long long river_len;
        std::cin >> river_len;
        factories.push_back(river_len);
        sum_squares += river_len * river_len;
    }
    std::cout << sum_squares << '\n';

    int k;
    std::cin >> k;
    size_t i = 1;
    auto current = factories.begin();
    while (k--) {
        int event;
        size_t factory;
        std::cin >> event >> factory;
        std::advance(current, factory - i);
        i += factory - i;
        if (event == BANKRUPTCY) {
            BankruptFactory(factories, current, sum_squares, i);
        } else if (event == SPLIT) {
            SplitFactory(factories, current, sum_squares);
        }
        std::cout << sum_squares << '\n';
    }

    return 0;
}