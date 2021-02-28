#include<iostream>
#include<vector>
#include<map>
#include<exception>
#include<utility>
#include<string>
#include<tuple>
#include<ctime>




template<typename T, typename V>
V& GetRefStrict(std::map<T, V>& m, T key) {
    if (m.count(key)==0) {
        throw std::runtime_error(" ");
    }
    return m[key];
}


int main() {
    std::map<int, std::string> m = { {0, "value"} };
    std::string& item = GetRefStrict(m, 0);
    item = "newvalue";
    std::cout << m[0] << std::endl; // выведет newvalue
}