#include <iostream>
#include <vector>
#include <limits>

#define DEFAULT std::numeric_limits<int>::min()

struct SegmentTreeNode {
    int value;
    int index;
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
    size_t index = 1;

    tree[0].value = DEFAULT;
    tree[0].index = 0;

    while (i < count) {
        std::cin >> tree[i].value;
        tree[i].index = index;
        ++i;
        ++index;
    }

    while (i < tree.size()) {
        tree[i].value = DEFAULT;
        tree[i].index = index;
        ++i;
        ++index;
    }

    for (size_t j = tree.size() / 2 - 1; j > 0; --j) {
        SegmentTreeNode& parent = tree[j];
        SegmentTreeNode& left = tree[2 * j];
        SegmentTreeNode& right = tree[2 * j + 1];

        if (left.value > right.value) {
            parent = left;
        } else {
            parent = right;
        }
    }
}

SegmentTreeNode& MaxNode(SegmentTreeNode& node1, SegmentTreeNode& node2) {
    if (node1.value > node2.value) {
        return node1;
    } else {
        return node2;
    }
}

int GetNextMaxIndex(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int index, int x) {
    SegmentTreeNode& parent = tree[i];

    if (parent.value < x || index > high) {
        return -1;
    }
    if (low == high) {
        return static_cast<int>(i - tree.size() / 2 + 1);
    }

    int left_index = GetNextMaxIndex(tree, 2 * i, low, (low + high) / 2, index, x);
    if (left_index >= 0) {
        return left_index;
    } else {
        return GetNextMaxIndex(tree, 2 * i + 1, (low + high) / 2 + 1, high, index, x);
    }
}

void UpdateTree(std::vector<SegmentTreeNode>& tree, size_t i, int value) {
    i += tree.size() / 2 - 1;
    tree[i].value = value;
    i /= 2;

    while (i > 0) {
        tree[i] = MaxNode(tree[2 * i], tree[2 * i + 1]);
        i /= 2;
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    int tree_size = ClosestPower2(n);
    std::vector<SegmentTreeNode> segment_tree(tree_size * 2);
    BuildTree(segment_tree, n);

    while (k--) {
        int command;
        std::cin >> command;

        if (command == 1) {
            int i, x;
            std::cin >> i >> x;
            int index = GetNextMaxIndex(segment_tree, 1, 1, tree_size, i, x);
            std::cout << index << '\n';
        } else if (command == 0) {
            size_t index;
            int value;
            std::cin >> index >> value;
            UpdateTree(segment_tree, index, value);
        }
    }

    return 0;
}