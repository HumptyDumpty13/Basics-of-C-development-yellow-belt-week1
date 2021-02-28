#include <iostream>
#include<vector>
#include <exception>
#include <string>



int main() {
    unsigned N;
    uint64_t R;
    std::cin >> N>>R;
    uint64_t summary = 0;
    for (size_t i = 0; i < N; ++i) {
        uint64_t w=0, h=0, d=0;
        std::cin >> w >> h >> d;
       uint64_t whd = w * h * d* R;
        summary += whd;
    }
    std::cout << summary;


    return 0;
}