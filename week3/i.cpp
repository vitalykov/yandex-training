#include <iostream>
#include <vector>
#include <bit>

void ReadBits(std::vector<char>& bits) {
    char bit = std::getchar();
    while ((bit = std::getchar()) != '\n') {
        bits.push_back(bit - '0');
    }
}

void PrintBits(std::vector<char>& bits) {
    for (const auto& bit : bits) {
        std::putchar(bit + '0');
    }
    std::cout << '\n';
}

void PrintFixedBits(std::vector<char>& bits) {
    size_t control_index = 1;
    for (size_t i = 0; i < bits.size(); ++i) {
        if (i + 1 == control_index) {
            control_index <<= 1;
        } else {
            std::putchar(bits[i] + '0');
        }
    }
    std::cout << '\n';
}

void ReadAndEncodeBits(std::vector<char>& bits) {
    char bit = std::getchar();
    bits.push_back('\0');
    size_t control_index = 2UL;
    size_t i = 2UL;

    while ((bit = std::getchar()) != '\n') {
        if (control_index == i) {
            bits.push_back('\0');
            ++i;
            control_index <<= 1;
        }
        bits.push_back(bit - '0');
        ++i;
    }

    size_t max_control_index = control_index - 1;
    for (control_index = 1; control_index <= max_control_index; control_index <<= 1) {
        i = control_index - 1;
        char& control_bit = bits[control_index - 1UL];
        while (i < bits.size()) {
            for (size_t j = 0; j < control_index; ++j) {
                control_bit ^= bits[i + j];
            }
            i += 2 * control_index;
        }
    }
}

void FixError(std::vector<char>& bits) {
    size_t max_control_index = 1UL << (8 * sizeof(bits.size()) - std::countl_zero(bits.size()) - 1);
    size_t error_index = 0;
    for (size_t control_index = 1; control_index <= max_control_index; control_index <<= 1) {
        size_t i = control_index - 1UL;
        char& control_bit = bits[i];
        char expected = control_bit;
        control_bit = '\0';
        while (i < bits.size()) {
            for (size_t j = 0; j < control_index; ++j) {
                control_bit ^= bits[i + j];
            }
            i += 2 * control_index;
        }
        if (control_bit != expected) {
            error_index += control_index;
        }
    }
    
    if (error_index > 0) {
        bits[error_index - 1] ^= 1;
    }
}

int main() {
    int launch;
    std::cin >> launch;

    if (launch == 1) {
        std::vector<char> bits;
        ReadAndEncodeBits(bits);
        PrintBits(bits);
    } else if (launch == 2) {
        std::vector<char> bits;
        ReadBits(bits);
        FixError(bits);
        PrintFixedBits(bits);
    }

    return 0;
}