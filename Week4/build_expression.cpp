#include <iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>
#include<deque>

void PrintDeque(std::deque<std::string>& deq) {
    deq.pop_front();
    deq.pop_back();
    for (size_t i = 0; i < deq.size(); ++i) {
        std::cout << deq[i];
    }
    std::cout<<std::endl;
}


int main() {
    int x = 0;
    std::cin >> x;
    int n = 0;
    std::cin >> n;
    std::deque<std::string> sdeq;
    sdeq.push_front("(");
    sdeq.push_back(std::to_string(x));
    sdeq.push_back(")");
    if (n == 0) { std::cout << x; } 
    else {
        for (int i = 0; i < n; ++i) {
            std::string op;
            int operand = 0;
            std::cin >> op >> operand;
            sdeq.push_front("(");
            sdeq.push_back(" ");
            sdeq.push_back(op);
            sdeq.push_back(" ");
            sdeq.push_back(std::to_string(operand));
            sdeq.push_back(")");
        }
        PrintDeque(sdeq);
    }
}