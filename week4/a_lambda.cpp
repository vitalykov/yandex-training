#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

int main() {
    std::stack<int> st;
    auto Push = [&st]() {
        int n;
        std::cin >> n;
        st.push(n);
        std::cout << "ok";
    };
    auto Pop = [&st]() {
        if (!st.empty()) {
            int n = st.top();
            st.pop();
            std::cout << n;
        } else {
            std::cout << "error";
        }
    };
    auto Back = [&st]() {
        if (!st.empty()) {
            std::cout << st.top();
        } else {
            std::cout << "error";
        }
    };
    auto Size = [&st]() {
        std::cout << st.size();
    };
    auto Clear = [&st]() {
        while (!st.empty()) {
            st.pop();
        }
        std::cout << "ok";
    };
    auto Exit = []() {
        std::cout << "bye" << '\n';
        exit(0);
    };

    std::unordered_map<std::string, std::function<void()>> func;
    func["push"] = Push;
    func["pop"] = Pop;
    func["back"] = Back;
    func["size"] = Size;
    func["clear"] = Clear;
    func["exit"] = Exit;

    while ("xD") {
        std::string command;
        std::cin >> command;
        func[command]();
        std::cout << '\n';
    }

    return 0;
}