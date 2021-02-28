#include <iostream>
#include<vector>
#include <exception>
#include <string>



int main() {
    int N;
    std::cin >> N;
    std::vector<int32_t> v;
    for (size_t i = 0; i < N; ++i) {
        int32_t temp;
        std::cin >> temp;
        v.push_back(temp);
    }

    int64_t sum = 0;
    for (auto item : v) {
        sum += item;
    }
    int64_t avg = sum / static_cast<int64_t>(N);
    unsigned counter = 0;
    for (auto it : v) {
        if (it > avg) ++counter;
    }
    std::cout << counter << std::endl;
    int x = 0;
    for (auto it : v) {

        if (it > avg) { std::cout << x << " "; }
        ++x;
    }

    return 0;
}