#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    int max_simple = 0;
    std::vector<int> sds, dsd;
    int ssd_count = 0;
    int ds_profit = 0;

    std::getchar();

    for (int i = 0; i < n; ++i) {
        int odd_simple = 0;
        int even_simple = 0;
        int len = 0;
        char c = 'a';

        while (true) {
            c = std::getchar();

            if (c == 'S') {
                ++even_simple;
            } else if (c == '\n') {
                break;
            }

            ++len;

            c = std::getchar();

            if (c == 'S') {
                ++odd_simple;
            } else if (c == '\n') {
                break;
            }

            ++len;
        }

        if (odd_simple == even_simple) {
            if (len & 1) {
                ++ssd_count;
            }

            max_simple += even_simple;
        } else {
            if (! (len & 1)) {
                if (even_simple > odd_simple) {
                    max_simple += even_simple;
                } else {
                    ds_profit += odd_simple - even_simple;
                    max_simple += odd_simple;
                }
            } else {
                if (even_simple > odd_simple) {
                    sds.push_back(even_simple - odd_simple);
                    max_simple += even_simple;
                } else {
                    dsd.push_back(odd_simple - even_simple);
                    max_simple += odd_simple;
                }
            }
        }
    }

    // std::cout << max_simple << '\n';

    std::sort(sds.begin(), sds.end(), std::greater<int>());
    std::sort(dsd.begin(), dsd.end(), std::greater<int>());

    int sds_index = 0;
    int dsd_index = 0;
    int max_dsd_index = dsd.size() - 1;

    bool odd_day = false;

    if (ds_profit > 0) {
        if (sds.size() > 0) {
            ++sds_index;
            odd_day = true;
        } else if (ssd_count > 0) {
            --ssd_count;
            odd_day = true;
        } else if (dsd.size() > 0) {
            int dsd_profit = dsd[max_dsd_index];

            if (ds_profit > dsd_profit) {
                max_simple -= dsd_profit;
                --max_dsd_index;
            }

            odd_day = true;
        } else {
            max_simple -= ds_profit;
        }
    }

    // std::cout << sds.size() << ' ' << dsd.size() << '\n';

    int dsd_count = max_dsd_index - dsd_index + 1;
    int sds_count = sds.size() - sds_index;

    // std::cout << sds_count << ' ' << dsd_count << '\n';

    if (dsd_count > sds_count) {
        dsd_count -= sds_count + ssd_count + static_cast<int>(odd_day);
        dsd_index = max_dsd_index - dsd_count + 1;

        for (; dsd_index <= max_dsd_index; ++dsd_index, --max_dsd_index) {
            // std::cout << dsd_index << ' ' << max_dsd_index << '\n';
            max_simple -= dsd[max_dsd_index];
            
        }
    } else {
        sds_count -= dsd_count + ssd_count + static_cast<int>(!odd_day);
        int max_sds_index = sds.size() - 1;
        sds_index = max_sds_index - sds_count + 1;

        for (; sds_index <= max_sds_index; ++sds_index, --max_sds_index) {
            max_simple -= sds[max_sds_index];
        }
    }

    std::cout << max_simple << '\n';

    return 0;
}