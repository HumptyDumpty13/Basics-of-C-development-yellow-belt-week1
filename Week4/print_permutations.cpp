#include <iostream>
#include <algorithm>
#include <vector>




int main() {
    int N = 0;
    std::cin >> N;
    std::vector<int> v;
    while(N>0) {
        v.push_back(N);
        --N;
    }
    do {
        for (const auto& it : v)
            std::cout << it<<' ';
        std::cout << std::endl;
    } while (std::prev_permutation(v.begin(), v.end()));
   
}
