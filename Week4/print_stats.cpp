#include <iostream>
#include <algorithm>
#include <vector>


void PrintStats(std::vector<Person> persons) {
    auto women_end = partition(begin(persons), end(persons), [](const Person& p) {return p.gender == Gender::FEMALE;});
    auto employed_women_end = partition(begin(persons), women_end, [](const Person& p) {return p.is_employed;});
    auto employed_men_end = partition(women_end, end(persons), [](const Person& p) {return p.is_employed;} );

    std::cout << "Median age = "
        << ComputeMedianAge(begin(persons), end(persons)) << std::endl;
    std::cout << "Median age for females = "
        << ComputeMedianAge(begin(persons), women_end) << std::endl;
    std::cout << "Median age for males = "
        << ComputeMedianAge(women_end, end(persons)) << std::endl;
    std::cout << "Median age for employed females = "
        << ComputeMedianAge(begin(persons), employed_women_end) << std::endl;
    std::cout << "Median age for unemployed females = "
        << ComputeMedianAge(employed_women_end, women_end) << std::endl;
    std::cout << "Median age for employed males = "
        << ComputeMedianAge(women_end, employed_men_end) << std::endl;
    std::cout << "Median age for unemployed males = "
        << ComputeMedianAge(employed_men_end, end(persons)) << std::endl;
}
int main() {
    std::vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}