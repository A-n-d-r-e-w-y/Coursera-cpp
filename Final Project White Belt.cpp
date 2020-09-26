#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>
using namespace std;


class Date {
public:
	int GetYear() const
	{
		return year;
	}
	int GetMonth() const
	{
		return month;
	}
	int GetDay() const
	{
		return day;
	}

	Date()
	{
		year = 2020;
		month = 9;
		day = 24;
	}

	Date(int new_year, int new_month, int new_day)
	{
		year = new_year;

		if (new_month < 1 || new_month > 12)
		{
			string error = "Month value is invalid: " + to_string(new_month);
			throw runtime_error(error);
		}
		month = new_month;

		if (new_day < 1 || new_day > 31)
		{
			string error = "Day value is invalid: " + to_string(new_day);
			throw runtime_error(error);
		}
		day = new_day;
	}

private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.GetYear() == rhs.GetYear())
	{
		if (lhs.GetMonth() == rhs.GetMonth())
			return lhs.GetDay() < rhs.GetDay();
		else
			return lhs.GetMonth() < rhs.GetMonth();
	}
	else
		return lhs.GetYear() < rhs.GetYear();
}


Date ReadDate(const string& date_str)
{
	stringstream ss(date_str);
	int year;
	int month;
	int day;
	char first_hyphen;
	char second_hyphen;

	ss >> year >> first_hyphen >> month >> second_hyphen >> day;


	if (ss && ss.eof() && first_hyphen == '-' && second_hyphen == '-')
		return Date(year, month, day);
	else
		throw runtime_error("Wrong date format: " + date_str);
}




class Database {
public:
	void AddEvent(const Date& date, const string& event)
	{
		date_to_events[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event)
	{
		if (date_to_events.count(date) && date_to_events[date].count(event))
		{
			date_to_events[date].erase(event);
			return true;
		}
		else
			return false;
	}
	int DeleteDate(const Date& date)
	{
		if (date_to_events.count(date))
		{
			int N = date_to_events[date].size();
			date_to_events.erase(date);
			return N;
		}
		else
			return 0;
	}
	void Find(const Date& date) const
	{
		if (date_to_events.count(date))
		{
			for (const auto& event : date_to_events.at(date))
			{
				cout << event << endl;
			}
		}
	}
	void Print() const
	{
		for (const auto& item : date_to_events)
		{
			for (const auto& event : item.second)
			{
				cout << setfill('0') << setw(4) << item.first.GetYear() << "-";
				cout << setfill('0') << setw(2) << item.first.GetMonth() << "-";
				cout << setfill('0') << setw(2) << item.first.GetDay() << " ";
				cout << event << endl;
			}
		}
	}

	Database(){}

private:
	map<Date, set<string>> date_to_events;
};







int main() {
	Database db;

	string line;
	while (getline(cin, line)) {

		if (line == "")
			continue;
		try
		{

			stringstream ss(line);
			string command;
			ss >> command;

			if (command == "Add")
			{
				string date_str;
				ss >> date_str;
				Date date = ReadDate(date_str);
				string event;
				ss >> event;
				db.AddEvent(date, event);
			}
			else if (command == "Del")
			{
				string date_str;
				ss >> date_str;
				Date date = ReadDate(date_str);
				string event;
				ss >> event;

				if (event == "")
				{
					auto N = db.DeleteDate(date);
					cout << "Deleted " << N << " events" << endl;
				}
				else
				{
					if (db.DeleteEvent(date, event))
						cout << "Deleted successfully" << endl;
					else
						cout << "Event not found" << endl;
				}
			}
			else if (command == "Find")
			{
				string date_str;
				ss >> date_str;
				Date date = ReadDate(date_str);
				db.Find(date);
			}
			else if (command == "Print")
			{
				db.Print();
			}
			else
				throw runtime_error("Unknown command: " + command);

		}
		catch (const exception& exc)
		{
			cout << exc.what() << endl;
			return 0;
		}
	}

	return 0;
}
