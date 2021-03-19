#include <iostream>
#include <algorithm>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
        std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
        auto it = begin(elements)+ (range_end - range_begin) / 3;
        auto it2 = begin(elements) + (range_end - range_begin) / 3*2;
        MergeSort(begin(elements), it);
        MergeSort(it, it2);
        MergeSort(it2, end(elements));
        std::vector<typename RandomIt::value_type> tmp;
        std::merge(begin(elements), it, it, it2, std::back_inserter(tmp));
        std::merge(begin(tmp), end(tmp), it2, end(elements), range_begin);
}

int main() {
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}