#include <iostream>
#include <vector>
#include <limits>

#define DEFAULT std::numeric_limits<unsigned>::min()

struct SegmentTreeNode {
    unsigned value;
    unsigned to_add;
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
    tree[0].to_add = 0;

    while (i < count) {
        std::cin >> tree[i].value;
        tree[i].to_add = 0;
        ++i;
    }

    while (i < tree.size()) {
        tree[i].value = DEFAULT;
        tree[i].to_add = 0;
        ++i;
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
    if ((node1.value + node1.to_add) > (node2.value + node2.to_add)) {
        return node1;
    } else {
        return node2;
    }
}

SegmentTreeNode& GetMax(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int l, int r) {
    if (l <= low && r >= high) {
        return tree[i];
    } else if (r < low || l > high) {
        return tree[0];
    } else {
        SegmentTreeNode& left = GetMax(tree, i * 2, low, (low + high) / 2, l, r);
        SegmentTreeNode& right = GetMax(tree, i * 2 + 1, (low + high) / 2 + 1, high, l, r);
        return MaxNode(left, right);
    }
}

void UpdateTree(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int l, int r, unsigned value) {    
    SegmentTreeNode& parent = tree[i];
    unsigned parent_add = parent.to_add;
    parent.value += parent_add;
    parent.to_add = 0;
    if (low < high) {
        tree[2 * i].to_add += parent_add;
        tree[2 * i + 1].to_add += parent_add;
    }
    
    if (l <= low && high <= r) {
        parent.value += value;
        if (low < high) {
            tree[2 * i].to_add += value;
            tree[2 * i + 1].to_add += value;
        }

        size_t index = i / 2;
        while (index > 0) {
            auto const& max_node = MaxNode(tree[2 * index], tree[2 * index + 1]);
            tree[index].value = max_node.value + max_node.to_add;
            index /= 2;
        }
    } else if (low <= r && high >= l) {
        UpdateTree(tree, i * 2, low, (low + high) / 2, l, r, value);
        UpdateTree(tree, i * 2 + 1, (low + high) / 2 + 1, high, l, r, value);
    }
}

unsigned FindNumber(std::vector<SegmentTreeNode>& tree, size_t i) {
    size_t index = 1;
    // unsigned parent_add = parent.to_add;
    // parent.value += parent_add;
    // parent.to_add = 0;
    size_t low = 1;
    size_t high = tree.size() / 2;
    while (low < high) {
        // std::cout << low << ' ' << high << '\n';
        SegmentTreeNode& parent = tree[index];
        SegmentTreeNode& left = tree[2 * index];
        SegmentTreeNode& right = tree[2 * index + 1];
        left.to_add += parent.to_add;
        right.to_add += parent.to_add;
        parent.to_add = 0;
        
        size_t mid = (low + high) / 2;
        if (i <= mid) {
            high = mid;
            index *= 2;
        } else {
            low = mid + 1;
            index += index + 1;
        }

    }

    SegmentTreeNode& parent = tree[index];

    return parent.value + parent.to_add;
}

int main() {
    int n;
    std::cin >> n;
    int tree_size = ClosestPower2(n);
    std::vector<SegmentTreeNode> segment_tree(tree_size * 2);
    BuildTree(segment_tree, n);

    // for (size_t i = 1; i < segment_tree.size(); ++i) {
    //     const auto& node = segment_tree[i];
    //     std::cout << node.value << ' ' << node.to_add << '\n';
    // }

    int k;
    std::cin >> k;
    while (k--) {
        char command;
        std::cin >> command;

        if (command == 'g') {
            size_t i;
            std::cin >> i;

            // std::cout << 'g' << ' ' << i << " = ";

            unsigned value = FindNumber(segment_tree, i);
            std::cout << value << '\n';
            
            // for (size_t i = 1; i < segment_tree.size(); ++i) {
            //     const auto& node = segment_tree[i];
            //     std::cout << node.value << ' ' << node.to_add << '\n';
            // }
        } else if (command == 'a') {
            int l, r;
            unsigned value;
            std::cin >> l >> r >> value;

            // std::cout << 'a' << l << ' ' << r << ' ' << value << '\n';

            UpdateTree(segment_tree, 1, 1, tree_size, l, r, value);

            // for (size_t i = 1; i < segment_tree.size(); ++i) {
            //     const auto& node = segment_tree[i];
            //     std::cout << node.value << ' ' << node.to_add << '\n';
            // }
        }
    }
    // std::cout << '\n';

    return 0;
}