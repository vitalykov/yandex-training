#include <iostream>
#include <vector>
#include <limits>

#define DEFAULT std::numeric_limits<int>::max()

struct SegmentTreeNode {
    int value;
    int count;
};

int ClosestPower2(int a) {
    --a;
    a |= a >> 1;
    a |= a >> 2;
    a |= a >> 4;
    a |= a >> 8;
    a |= a >> 16;
    ++a;

    return a;
}

void BuildTree(std::vector<SegmentTreeNode>& tree, int n) {
    size_t i = tree.size() / 2;
    size_t count = i + static_cast<size_t>(n);

    tree[0].value = DEFAULT;
    tree[0].count = 0;

    while (i < count) {
        std::cin >> tree[i].value;
        tree[i].count = 1;
        ++i;
    }

    while (i < tree.size()) {
        tree[i].value = DEFAULT;
        tree[i].count = 1;
        ++i;
    }

    for (size_t j = tree.size() / 2 - 1; j > 0; --j) {
        SegmentTreeNode& parent = tree[j];
        SegmentTreeNode& left = tree[2 * j];
        SegmentTreeNode& right = tree[2 * j + 1];

        if (left.value == right.value) {
            parent.value = left.value;
            parent.count = left.count + right.count;
        } else if (left.value < right.value) {
            parent = left;
        } else {
            parent = right;
        }
    }
}

SegmentTreeNode MinNode(SegmentTreeNode& node1, SegmentTreeNode& node2) {
    if (node1.value == node2.value) {
        return {.value = node1.value, .count = node1.count + node2.count};
    } else if (node1.value < node2.value) {
        return node1;
    } else {
        return node2;
    }
}

SegmentTreeNode GetMin(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int l, int r) {
    if (l > r) {
        return {.value = DEFAULT, .count = 0};
    }
    if (l <= low && r >= high) {
        return tree[i];
    } else if (r < low || l > high) {
        return {.value = DEFAULT, .count = 1};
    } else {
        SegmentTreeNode left = GetMin(tree, i * 2, low, (low + high) / 2, l, r);
        SegmentTreeNode right = GetMin(tree, i * 2 + 1, (low + high) / 2 + 1, high, l, r);
        return MinNode(left, right);
    }
}

int GetZeroIndex(std::vector<SegmentTreeNode>& tree, int zero_count, int l, int r) {
    size_t i = 1;
    SegmentTreeNode& current = tree[i];

    while (i < tree.size() / 2) {
        SegmentTreeNode& left = tree[2 * i];
        SegmentTreeNode& right = tree[2 * i + 1];

        if (left.value == 0 && left.count >= zero_count) {
            current = left;
            i += i;
        } else {
            current = right;
            if (left.value == 0) {
                zero_count -= left.count;
            }
            i += i + 1;
        }
    }

    return i - tree.size() / 2 + 1;
}

void UpdateTree(std::vector<SegmentTreeNode>& tree, size_t i, int value) {
    i += tree.size() / 2 - 1;
    tree[i].value = value;
    i /= 2;

    while (i > 0) {
        tree[i] = MinNode(tree[2 * i], tree[2 * i + 1]);
        i /= 2;
    }
}

int main() {
    int n;
    std::cin >> n;
    int tree_size = ClosestPower2(n);
    std::vector<SegmentTreeNode> segment_tree(tree_size * 2);
    BuildTree(segment_tree, n);

    int k;
    std::cin >> k;
    while (k--) {
        char command;
        std::cin >> command;

        if (command == 's') {
            int l, r, k;
            std::cin >> l >> r >> k;
            
            int prefix_zeros = 0;
            SegmentTreeNode prefix = GetMin(segment_tree, 1, 1, tree_size, 1, l - 1);
            if (prefix.value == 0) {
                prefix_zeros = prefix.count;
            }

            int base_zeroes = 0;
            SegmentTreeNode base = GetMin(segment_tree, 1, 1, tree_size, l, r);
            if (base.value == 0) {
                base_zeroes = base.count;
            }
            if (base_zeroes < k) {
                std::cout << -1 << ' ';
            } else {
                int zero_index = GetZeroIndex(segment_tree, k + prefix_zeros, l, r);
                std::cout << zero_index << ' ';
            }
        } else if (command == 'u') {
            size_t index;
            int value;
            std::cin >> index >> value;
            UpdateTree(segment_tree, index, value);
        }
    }

    return 0;
}