#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
void RemoveDuplicates(std::vector<T>& elements) {
    std::sort(begin(elements), end(elements));
    auto it = std::unique(begin(elements), end(elements));
    elements.erase(it, end(elements));
}

int main() {
    std::vector<int> v1 = { 6, 4, 7, 6, 4, 4, 0, 1 };
    RemoveDuplicates(v1);
    for (int x : v1) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> v2 = { "C", "C++", "C++", "C", "C++" };
    RemoveDuplicates(v2);
    for (const std::string& s : v2) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    return 0;
}