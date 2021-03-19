#include <stdexcept>
#include <tuple>
#include <iomanip>

#include "date.h"

    Date::Date(const int& new_year, const int& new_month, const int& new_day) : year(new_year), month(new_month), day(new_day) {
    }

    int Date::GetYear() const {
        return year;
    }
    int Date::GetMonth() const {
        return month;
    }
    int Date::GetDay() const {
        return day;
    }

bool operator==(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
        std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}
bool operator<(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
        std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}
bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}


std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() <<
        "-" << std::setw(2) << std::setfill('0') << date.GetMonth() <<
        "-" << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
}

Date ParseDate(std::istream& is) {
    int y, m, d;
    bool ok = true;

    int year;
    ok = ok && (is >> year);
    ok = ok && (is.peek() == '-');
    is.ignore(1);

    int month;
    ok = ok && (is >> month);
    ok = ok && (is.peek() == '-');
    is.ignore(1);

    int day;
    ok = ok && (is >> day);
    ok = ok && is.eof();

    return Date(year, month, day);
}