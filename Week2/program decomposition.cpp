#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    std::string str;
    is >> str;
    if (is) {
        if (str == "NEW_BUS") {
            q.type = QueryType::NewBus;
            int stop_count = 0;
            is >> q.bus;
            is >> stop_count;
            q.stops= vector<string>(stop_count);
            for (string& stop : q.stops) {
                is >> stop;
               
            }
        }
        else if (str == "BUSES_FOR_STOP") { q.type = QueryType::BusesForStop; is >> q.stop; }
        else if (str == "STOPS_FOR_BUS") { q.type = QueryType::StopsForBus; is >> q.bus; }
        else if (str == "ALL_BUSES") { q.type = QueryType::AllBuses; }
    }
    return is;
}

struct BusesForStopResponse {
    string stop_;
    map<string, vector<string>> stops_to_buses_;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.stops_to_buses_.count(r.stop_)==0) {
        os << "No stop";
    }
    else {
        for (const auto& bus : r.stops_to_buses_.at(r.stop_)) {
            os << bus << " ";
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    string bus_;
    map<string, vector<string>> buses_to_stops_;
    map<string, vector<string>> stops_to_buses_;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.buses_to_stops_.count(r.bus_) == 0) {
        os << "No bus";
    }
    else {
        for (const string& stop : r.buses_to_stops_.at(r.bus_)) {
            os << "Stop " << stop << ": ";
            if (r.stops_to_buses_.at(stop).size() == 1) {
                os << "no interchange";
            }
            else {
                for (const string& other_bus : r.stops_to_buses_.at(stop)) {
                    if (r.bus_ != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
           os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops_;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops_.empty()) {
        os << "No buses";
    }
    else {
        for (const auto& bus_item : r.buses_to_stops_) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus]=stops;
        for (const auto& item : stops) {
            stops_to_buses[item].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse response;
        response.stop_ = stop;
        response.stops_to_buses_ = stops_to_buses;
        return response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse response;
        response.bus_ = bus;
        response.buses_to_stops_ = buses_to_stops;
        response.stops_to_buses_ = stops_to_buses;
        return response;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse response;
        response.buses_to_stops_ = buses_to_stops;
        return response;
    }
private:
    map<string, vector<string>> stops_to_buses, buses_to_stops;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}