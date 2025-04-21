#include <iostream>
#include <vector>
#include <limits>

#define DEFAULT std::numeric_limits<int>::min()

struct SegmentTreeNode {
    int all;
    int prefix;
    int suffix;
    int length;
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

void CombineNodes(const SegmentTreeNode& left, const SegmentTreeNode& right, SegmentTreeNode& parent) {
    if (left.prefix < left.length) {
        parent.prefix = left.prefix;
    } else {
        parent.prefix = left.prefix + right.prefix;
    }
    if (right.suffix < right.length) {
        parent.suffix = right.suffix;
    } else {
        parent.suffix = right.suffix + left.suffix;
    }
    int max_all = std::max(left.all, right.all);
    int max_pref_suf = std::max(parent.prefix, parent.suffix);
    parent.all = std::max(std::max(max_all, max_pref_suf), left.suffix + right.prefix);
    parent.length = left.length + right.length;
}

void BuildTree(std::vector<SegmentTreeNode>& tree, int n) {
    size_t i = tree.size() / 2;
    size_t count = i + static_cast<size_t>(n);
    size_t index = 1;

    tree[0] = {0, 0, 0, 0};

    while (i < count) {
        int a;
        std::cin >> a;
        if (a == 0) {
            tree[i] = {1, 1, 1, 1};
        } else {
            tree[i] = {0, 0, 0, 1};
        }
        ++i;
    }

    while (i < tree.size()) {
        tree[i] = {0, 0, 0, 0};
        ++i;
    }

    for (size_t j = tree.size() / 2 - 1; j > 0; --j) {
        CombineNodes(tree[2 * j], tree[2 * j + 1], tree[j]);
    }
}

SegmentTreeNode GetMaxZeros(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int l, int r) {
    if (l <= low && r >= high) {
        return tree[i];
    } else if (r < low || l > high) {
        return tree[0];
    } else {
        SegmentTreeNode left = GetMaxZeros(tree, i * 2, low, (low + high) / 2, l, r);
        SegmentTreeNode right = GetMaxZeros(tree, i * 2 + 1, (low + high) / 2 + 1, high, l, r);
        SegmentTreeNode combined_node;
        CombineNodes(left, right, combined_node);
        return combined_node;
    }
}

void UpdateTree(std::vector<SegmentTreeNode>& tree, size_t i, int value) {
    i += tree.size() / 2 - 1;
    
    if (value == 0) {
        tree[i] = {1, 1, 1, 1};
    } else {
        tree[i] = {0, 0, 0, 1};
    }

    i /= 2;

    while (i > 0) {
        CombineNodes(tree[2 * i], tree[2 * i + 1], tree[i]);
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
        std::string command;
        std::cin >> command;

        if (command == "QUERY") {
            int l, r;
            std::cin >> l >> r;
            SegmentTreeNode node = GetMaxZeros(segment_tree, 1, 1, tree_size, l, r);
            std::cout << node.all << '\n';
        } else if (command == "UPDATE") {
            size_t index;
            int value;
            std::cin >> index >> value;
            UpdateTree(segment_tree, index, value);
        }
    }
    // std::cout << '\n';

    return 0;
}