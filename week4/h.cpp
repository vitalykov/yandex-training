#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#define ASK 0UL
#define CUT 1UL

struct Operation {
    size_t command;
    size_t v1;
    size_t v2;
};

struct Vertice {
    size_t parent;
    size_t size;
};

inline int Ask(std::vector<Vertice>& vertices, size_t v1, size_t v2) {
    while (vertices[v1].parent != v1) {
        v1 = vertices[v1].parent;
    }
    while (vertices[v2].parent != v2) {
        v2 = vertices[v2].parent;
    }
    return (v1 == v2) ? 1 : 0;
}

inline int Cat(std::vector<Vertice>& vertices, size_t v1, size_t v2) {
    while (vertices[v1].parent != v1) {
        v1 = vertices[v1].parent;
    }
    while (vertices[v2].parent != v2) {
        v2 = vertices[v2].parent;
    }
    if (vertices[v1].size > vertices[v2].size) {
        vertices[v2].parent = v1;
        vertices[v2].size += vertices[v1].size;
        size_t next = v1;
        while (vertices[next].parent != v1) {
            vertices[next].parent = v1;
            next = vertices[next].parent;
        }
    } else {
        vertices[v1].parent = v2;
        vertices[v1].size += vertices[v2].size;
        size_t next = v2;
        while (vertices[next].parent != v2) {
            vertices[next].parent = v2;
            next = vertices[next].parent;
        }
    }

    return 0;
}

inline int Execute(Operation& operation, std::vector<Vertice>& vertices) {
    static std::vector<std::function<int(std::vector<Vertice>&, size_t, size_t)>> execute = {Ask, Cat};
    return execute[operation.command](vertices, operation.v1, operation.v2);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    size_t n, m, k;
    std::cin >> n >> m >> k;
    while (m--) {
        int a, b;
        std::cin >> a >> b;
    }
    std::vector<Vertice> vertices(n + 1);
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i] = {.parent = i, .size = 1};
    }
    std::stack<Operation> st;
    while (k--) {
        std::string command;
        size_t v1, v2;
        std::cin >> command >> v1 >> v2;
        if (command == "ask") {
            st.push({.command = ASK, .v1 = v1, .v2 = v2});
        } else if (command == "cut") {
            st.push({.command = CUT, .v1 = v1, .v2 = v2});
        }
    }

    std::stack<int> answers;
    while (!st.empty()) {
        auto operation = st.top();
        st.pop();
        int code = Execute(operation, vertices);
        if (operation.command == ASK) {
            answers.push(code);
        }
    }

    while (!answers.empty()) {
        int answer = answers.top();
        answers.pop();
        std::cout << (answer ? "YES" : "NO") << '\n'; 
    }

    return 0;
}