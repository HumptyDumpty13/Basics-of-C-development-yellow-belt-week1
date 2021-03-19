#include <iostream>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers) {
   auto it = begin(numbers);
   for (; it != end(numbers); ++it) {
        if (*it < 0) {  break; }
    }
   while (it != begin(numbers)) {
       --it;
       std::cout << *it << " ";
    }
}

int main() {
    PrintVectorPart({ 6, 1, 8, -5, 4 });
    std::cout << std::endl;
    PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
    std::cout << std::endl;
    PrintVectorPart({ 6, 1, 8, 5, 4 });
    std::cout << std::endl;
    return 0;
}