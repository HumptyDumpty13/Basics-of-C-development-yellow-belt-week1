#include <iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>
#include<deque>

void PrintDeque(std::deque<std::string>& deq) {
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
    sdeq.push_back(std::to_string(x));
    int prev_number = 2;
    if (n == 0) { std::cout << x; } 
    else {
        for (int i = 0; i < n; ++i) {
            std::string op;
            int operand = 0;
            std::cin >> op >> operand;
            int number = 0;
            if (op == "+" || op == "-") {
                number = 1;
            }
            else if (op == "*" || op == "/") { number = 2; }
            if (number > prev_number) {
                sdeq.push_front("(");
            }
            if (number > prev_number) {
                sdeq.push_back(")");
            }
            sdeq.push_back(" ");
            sdeq.push_back(op);
            sdeq.push_back(" ");
            sdeq.push_back(std::to_string(operand));
            prev_number = number;
        }
        PrintDeque(sdeq);
    }
}