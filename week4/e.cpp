#include <iostream>
#include <vector>

template <typename T>
class CircularList {
public:
    struct Node {
        Node* next;
        Node* prev;
        T value;

        Node(Node* next, Node* prev, T value) : next(next), prev(prev), value(value) {}
    };

    Node* head_ = nullptr;
    
    CircularList() {}
    
    void AddFront(T value) {
        if (head_ != nullptr) {
            Node* prev = head_->prev;
            Node* current = new Node(head_, prev, value);
            prev->next = current;
            head_->prev = current;
            head_ = current;
        } else {
            head_ = new Node(nullptr, nullptr, value);
            head_->next = head_->prev = head_;
        }
    }

    void Erase(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        if (node != next) {
            prev->next = next;
            next->prev = prev;
            if (node == head_) {
                head_ = prev;
            }
        } else {
            head_ = nullptr;
        }
        delete node;
    }

    ~CircularList() {
        while (head_ != nullptr) {
            Erase(head_);
        }
    }
};

struct Player {
    int index;
    int rating;
    int round;

    Player(int index, int rating, int round = 1) : index(index), rating(rating), round(round) {}
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> ratings(n + 1);
    for (size_t i = 1; i < ratings.size(); ++i) {
        std::cin >> ratings[i];
    }
    auto players = CircularList<Player>();
    for (size_t i = size_t(n); i != 0; --i) {
        players.AddFront(Player(i, ratings[i]));
    }
    
    std::vector<int> player_rounds(n + 1, 0);
    auto current = players.head_;
    int eliminated = 0;

    while (true) {
        auto next = current->next;
        auto prev = current->prev;
        if (next == prev) {
            break;
        }
        int current_rating = current->value.rating;
        int prev_rating = prev->value.rating;
        int next_rating = next->value.rating;
        if (current_rating < prev_rating && current_rating < next_rating) {
            player_rounds[current->value.index] = std::max(current->value.round, prev->value.round);
            prev->value.round = player_rounds[current->value.index] + 1;
            players.Erase(current);
            ++eliminated;
        }
        current = next;
        if (current == players.head_) {
            if (eliminated == 0) {
                break;
            }
            eliminated = 0;
        }
    }

    for (size_t i = 1; i < player_rounds.size(); ++i) {
        std::cout << player_rounds[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}