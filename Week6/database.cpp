#include "database.h"

std::ostream& operator<<(std::ostream& stream, const std::map<Date, std::vector<std::string>>& m) {
	for (const auto& it : m) {
		for (const auto& string : it.second) {
			stream << it.first << " " << string<<std::endl;
		}
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::string>& p) {
	return stream << p.first << ' ' << p.second;
}

std::ostream& operator<<(std::ostream& stream, std::vector<std::pair<Date, std::string>>& v) {
	for (const auto& i : v) {
		stream << i << std::endl;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::pair<Date, std::vector<std::string>>& p) {
	for (const auto& string : p.second) {
		stream << p.first << ' ' << string;
	}
	return stream;
}


	Database::Database() {}
	void Database::Add(const Date& date, const std::string& event) {
		if (events[date].insert(event).second) {
			base[date].push_back(event);
		}
	}
	void Database::Print(std::ostream& os) const {
		for (const auto& item : base) {
			for (const std::string& event : item.second) {
				os << item.first << " " << event << std::endl;
			}
		}
	}
	std::pair<Date, std::string> Database::Last(const Date& d) const {
		//if (d > begin(base)->first) {
		//	throw invalid_argument("");
		//}
		auto it = base.upper_bound(d);
		if (it != base.begin()) {
			--it;
			return std::make_pair(it->first, it->second.back());
		}
		else {
			throw std::invalid_argument("");
		}
	}