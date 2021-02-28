#include <iostream>
#include<vector>
#include<map>
#include <utility>
#include <string>
#include<tuple>
#include<ctime>

template <class first, class second> std::pair<first, second> Sqr (const std::pair<first, second>& p1);
template <typename key, typename value> std::map<key, value> Sqr (const std::map<key, value> m);
template<typename T> std::vector<T> Sqr (const std::vector<T>& v1);
template <class  T> T Sqr(T x);

template <class first, class second>
std::pair<first, second> Sqr(const std::pair<first, second>& p1) {
    first f = Sqr(p1.first);
    second s = Sqr(p1.second);
    return std::make_pair(f, s);
}

template <typename key, typename value>
std::map<key, value> Sqr(const std::map<key, value> m) {
    std::map<key, value> m1;
    for (auto& i : m) {
        m1[i.first] = Sqr(i.second);
    }
    return m1;
}

template<typename T>
std::vector<T> Sqr(const std::vector<T>& v) {
    std::vector<T> v1;
    for (auto& i : v) {
        v1.push_back(Sqr(i));
    }
    return v1;
}

template <class  T>
T Sqr(T x) { return x * x; }


int main() {
    std::vector<int> v = { 1, 2, 3 };
    std::cout << "vector:";
    for (int x : Sqr(v)) {
        std::cout << ' ' << x;
    }
    std::cout << std::endl;

    std::map<int, std::pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    std::cout << "map of pairs:" << std::endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
    }
}