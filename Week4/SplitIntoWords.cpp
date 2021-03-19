#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

std::vector<std::string> SplitIntoWords(const std::string& s) {
    std::vector<std::string> words;
    auto iterator = begin(s);
    while(true) {
        auto it = std::find(iterator, end(s), ' ');
        std::string str(iterator, it);
        words.push_back(str);
        if (it == end(s)) { break; }
        iterator = it;
        ++iterator;
    }
    return words;
}

int main() {
    std::string s = "C Cpp Java Python";

    std::vector<std::string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            std::cout << "/";
        }
        std::cout << *it;
    }
    std::cout << std::endl;

    return 0;
}