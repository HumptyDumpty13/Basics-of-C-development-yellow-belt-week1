#pragma once

#include<vector>
#include<string>
#include<map>
#include<set>
#include<algorithm>
#include<utility>

#include "date.h"

std::ostream& operator<<(std::ostream& stream, const std::map<Date, std::vector<std::string>>& m);

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::string>& p);

std::ostream& operator<<(std::ostream& stream, std::vector<std::pair<Date, std::string>>& v);

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::vector<std::string>>& p);

class Database {
public:
	Database();
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;
	template <class Func> int RemoveIf(Func func) {
		std::vector<Date> empty_dates;
		int counter = 0;
		for (auto& item : base) {
			auto cur_date = item.first;
			//std::cout << cur_date << " Date" << std::endl;
			auto vec_it = std::stable_partition(begin(item.second), end(item.second), [func, cur_date = cur_date](const auto& event) { return func(cur_date, event); } );
			//if (vec_it != end(item.second)) { std::cout << *vec_it << std::endl; }
			for (auto it = begin(item.second); it != vec_it; ++it) {
				events[cur_date].erase(*it);
				//std::cout << *it << std::endl;
				++counter;
			}
			//std::cout << "--------------"<<std::endl;
			base[cur_date].erase(begin(item.second), vec_it);
			//base[cur_date].erase(vec_it, end(item.second));
			/*for (const auto& i : base) {
				for(const auto& str : i.second)
				std::cout << i.first << ' ' << str << std::endl;
			}
			std::cout << "--------------" << std::endl;*/
			if (base[cur_date].empty()) { empty_dates.push_back(cur_date); 
			}
		}
		for (auto iterator = begin(empty_dates); iterator != end(empty_dates); ++iterator) {
			//std::cout << *iterator << std::endl;
			events.erase(*iterator);
			base.erase(*iterator);
		}
		return counter;
	}
	template <class Func>
	std::vector<std::pair<Date, std::string>> FindIf(Func func) const {
		std::vector<std::pair<Date, std::string>> v;
		for(auto& item : base) {
			auto cur_date = item.first;
			auto vec_it = std::find_if(begin(item.second), end(item.second), [func, cur_date = cur_date](const auto& event) {return func(cur_date, event); });
			while (vec_it != end(item.second)) {
				auto it = std::find_if(vec_it, end(item.second), [func, cur_date = cur_date](const auto& event) {return func(cur_date, event); });
				vec_it = it;
				if (vec_it != end(item.second)) { v.push_back(std::make_pair(cur_date, *vec_it)); ++vec_it;} 
			}
		}
		return v;
	}
	std::pair<Date, std::string> Last(const Date& d) const;
private:
	std::map<Date, std::set<std::string>> events;
	std::map<Date, std::vector<std::string>> base;
};