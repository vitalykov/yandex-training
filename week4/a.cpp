#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<int> st;
    while ("xD") {
        std::string command;
        std::cin >> command;
        if (command == "push") {
            int n;
            std::cin >> n;
            st.push(n);
            std::cout << "ok";
        } else if (command == "pop") {
            if (!st.empty()) {
                int n = st.top();
                st.pop();
                std::cout << n;
            } else {
                std::cout << "error";
            }
        } else if (command == "back") {
            if (!st.empty()) {
                std::cout << st.top();
            } else {
                std::cout << "error";
            }
        } else if (command == "size") {
            std::cout << st.size();
        } else if (command == "clear") {
            while (!st.empty()) {
                st.pop();
            }
            std::cout << "ok";
        } else if (command == "exit") {
            break;
        }
        std::cout << '\n';
    }

    std::cout << "bye" << '\n';

    return 0;
}