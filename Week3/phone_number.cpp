#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "phone_number.h"

 PhoneNumber::PhoneNumber(const std::string& international_number) {
	stringstream stream(international_number);
	if (stream.peek() != '+') {
		throw invalid_argument("");
	}
	stream.ignore(1);
	getline(stream, country_code_, '-');
	getline(stream, city_code_, '-');
	getline(stream, local_number_);
	if (country_code_.empty() || city_code_.empty() || local_number_.empty()) {
		throw invalid_argument("");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	string s = '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
	return s;
}