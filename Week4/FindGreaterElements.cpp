#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
    std::vector<T> GreaterElements;
    for (auto it = begin(elements); it != end(elements); ++it) {
        if (*it > border) { GreaterElements.push_back(*it); }
    }
        return GreaterElements;
}

int main() {
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string to_find = "Python";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
    return 0;
}