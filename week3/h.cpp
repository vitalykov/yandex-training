#include <iostream>
#include <vector>

// typedef std::vector<std::vector<std::vector<int>>> Vec3d;

class Vec3d {
private:
    size_t width_;
    size_t height_;
    std::vector<int> data_;

public:
    Vec3d(size_t length, size_t width, size_t height, int init_value) :
        width_(width), height_(height), data_(length * width * height, init_value)
    {}

    inline int& operator()(size_t x, size_t y, size_t z) {
        return data_[x + y * width_  + z * width_ * height_];
    }

    inline constexpr size_t size() {
        return width_;
    }
};

inline int SumPrefix(Vec3d& arr, int x, int y, int z) {
    int result = 0;
    for (int i = x; i > 0; i -= i & -i) {
        for (int j = y; j > 0; j -= j & -j) {
            for (int k = z; k > 0; k -= k & -k) {
                result += arr(i, j, k);
            }
        }
    }
    return result;
}

int Sum(Vec3d& arr, int x1, int x2, int y1, int y2, int z1, int z2) {
    int sq_small_low = SumPrefix(arr, x1 - 1, y1 - 1, z1 - 1);
    int rect_right_low = SumPrefix(arr, x2, y1 - 1, z1 - 1);
    int rect_up_low = SumPrefix(arr, x1 - 1, y2, z1 - 1);
    int sq_big_low = SumPrefix(arr, x2, y2, z1 - 1);
    int under = sq_big_low - (rect_right_low + (rect_up_low - sq_small_low));

    int sq_small_high = SumPrefix(arr, x1 - 1, y1 - 1, z2);
    int rect_right_high = SumPrefix(arr, x2, y1 - 1, z2);
    int rect_up_high = SumPrefix(arr, x1 - 1, y2, z2);
    int rest = rect_right_high + (rect_up_high - sq_small_high);

    int sq_big_high = SumPrefix(arr, x2, y2, z2);

    return sq_big_high - rest - under;
}

inline void Add(Vec3d& arr, int x, int y, int z, int value) {
    int n = static_cast<int>(arr.size() - 1);
    for (int i = x; i <= n; i += i & -i) {
        for (int j = y; j <= n; j += j & -j) {
            for (int k = z; k <= n; k += k & -k) {
                arr(i, j, k) += value;
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    // Vec3d arr(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1, 0)));
    Vec3d arr(n + 1, n + 1, n + 1, 0);

    while (true) {
        int command;
        std::cin >> command;
        if (command == 1) {
            int x, y, z, value;
            std::cin >> x >> y >> z >> value;
            Add(arr, x + 1, y + 1, z + 1, value);
        } else if (command == 2) {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << Sum(arr, x1 + 1, x2 + 1, y1 + 1, y2 + 1, z1 + 1, z2 + 1) << '\n';
        } else if (command == 3) {
            break;
        }
    }

    return 0;
}