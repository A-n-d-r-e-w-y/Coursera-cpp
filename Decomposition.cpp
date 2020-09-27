#include <iostream>
#include <vector>
#include <string>
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
    
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS") {

        q.type = QueryType::NewBus;
        is >> q.bus;

        int stop_count;
        is >> stop_count;
        q.stops.clear();
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP") {
        
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS") {

        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES") {

        q.type = QueryType::AllBuses;
    }

    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
    string stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    
    if (r.buses.size() == 0) {
        os << "No stop";
    }
    else {
        for (const string& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    vector<pair<string, vector<string>>> stop_buses;;
    string bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    
    if (r.stop_buses.size() == 0) {
        os << "No bus";
    }
    else {
        for (int i = 0; i < r.stop_buses.size(); ++i)
        {
            os << "Stop " << r.stop_buses[i].first << ": ";
            if (r.stop_buses[i].second.size() == 1)
                os << "no interchange";
            else
            {
                for (const string& other_bus : r.stop_buses[i].second) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            if (i < r.stop_buses.size() - 1)
                os << endl;
        }
    }
    return os;
}


struct AllBusesResponse {
    vector<pair<string, vector<string>>> bus_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    
    if (r.bus_to_stops.size() == 0)
        os << "No buses";
    else
    {
        for (int i = 0; i < r.bus_to_stops.size(); ++i)
        {
            os << "Bus " << r.bus_to_stops[i].first << ": ";
            for (const string& stop : r.bus_to_stops[i].second)
                os << stop << " ";
            if (i < r.bus_to_stops.size() - 1)
                os << endl;
        }
    }
    return os;
}


class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {

        for (const string& stop : stops) {
            buses_to_stops[bus].push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        result.stop = stop;
        if (stops_to_buses.count(stop) != 0) {
            for (const string& bus : stops_to_buses.at(stop))
                result.buses.push_back(bus);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {

        StopsForBusResponse result;
        result.bus = bus;

        if (buses_to_stops.count(bus)) {
            for (const string& stop : buses_to_stops.at(bus)) {
                vector<string> buses;
                if(stops_to_buses.count(stop))
                    buses = stops_to_buses.at(stop);
                result.stop_buses.push_back(make_pair(stop, buses));
            }
        }

        return result;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse result;
        if (buses_to_stops.size()) {
            
            for (const auto& bus_item : buses_to_stops) {
                vector<string> stops;
                for (const string& stop : bus_item.second)
                    stops.push_back(stop);
                result.bus_to_stops.push_back(make_pair(bus_item.first, stops));
            }
        }
        return result;
    }

private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};



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