#include <iostream>
#include <string>
#include <forward_list>

int main() {
    int n;
    std::cin >> n;
    std::forward_list<std::string> app_list;
    size_t list_len = 0;
    while (n--) {
        std::string command;
        std::cin >> command;
        std::string app;
        if (command == "Run") {
            char c = std::getchar();
            if (c != '\n' && c != EOF) {
                std::getline(std::cin, app);
                app_list.push_front(app);
                std::cout << app;
                ++list_len;
            } else {
                if (list_len != 0) {
                    std::cout << *app_list.begin();
                }
            }
        } else {
            if (list_len != 0) {
                size_t tab_count = ((command.length() - 3) / 4) % list_len;
                if (tab_count != 0) {
                    auto it = std::next(app_list.begin(), tab_count - 1);
                    app = *std::next(it);
                    app_list.erase_after(it, std::next(it, 2));
                    app_list.push_front(app);
                } else {
                    app = *app_list.begin();
                }
                std::cout << app;
            }
        }
        std::cout << '\n';
    }

    return 0;
}