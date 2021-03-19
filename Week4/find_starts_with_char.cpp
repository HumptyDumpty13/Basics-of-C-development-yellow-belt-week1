#include <iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {
    std::string str;
    str = prefix;
    char new_prefix = static_cast<char>(prefix + 1);
    std::string str1;
    str1 = new_prefix;
    auto it = std::lower_bound(range_begin, range_end, str);
    auto it2 = std::upper_bound(range_begin, range_end, str1);
    return std::make_pair(it, it2);
}

int main() {
    const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << std::endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << std::endl;

    return 0;
}
