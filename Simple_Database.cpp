// TRUE.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
using namespace std;
class Date {
private:
	int Year;
	int Month;
	int Day;
public:
	Date(const int& New_Year, const int& new_Month, const int& new_Day) {
		Year = New_Year;
		Month = new_Month;
		Day = new_Day;
	}
	int GetYear() const { return Year; }
	int GetMonth() const { return Month; }
	int GetDay() const { return Day; }
};
Date parseDate(const string& input_string) { 
	if (input_string.empty()) {
		cout << "Wrong date format: " << endl;
		throw 0;
	}
	stringstream isstream(input_string);
	int year = 0, month = 0, day = 0;
	string error_msg = "Wrong date format: ";
	char s, s1 = 0, s2 = 0;
	if (!isdigit(isstream.peek()) && isstream.peek() != ' ') {
		cout << error_msg << input_string << endl; 
		throw 0;
	}
	else {
		while (isdigit(isstream.peek())) { 
			s = isstream.peek();
			year = year * 10 + (s - 48); 
			isstream.ignore(1); 
		}
		if (isstream.peek() != '-') {
			cout << error_msg << input_string << endl;
			throw 0;
		}
		isstream >> s1;
		if (!isdigit(isstream.peek()) && isstream.peek() != '-') {
			cout << error_msg << input_string << endl;
			throw 0;
		}
		char z = isstream.peek();
		if (z == '-')
			isstream.ignore(1);
		while (isdigit(isstream.peek())) {
			s = isstream.peek();
			month = month * 10 + (s - 48);
			isstream.ignore(1);
		}
		if (z == '-')
			month *= -1;
		if (isstream.peek() != '-') {
			cout << error_msg << input_string << endl;
			throw 0;

		}
		isstream >> s2;
		if (!isdigit(isstream.peek()) && isstream.peek() != '-') { 
			cout << error_msg << input_string << endl;
			throw 0;
		}
		char z1 = isstream.peek();
		if (z1 == '-')
			isstream.ignore(1);
		while (isdigit(isstream.peek())) {
			s = isstream.peek();
			day = day * 10 + (s - 48); 
			isstream.ignore(1);
		}
		if (z1 == '-')
			day *= -1;

		if (isstream.peek() != ' ' && !isstream.eof()) {
			cout << error_msg << input_string << endl;
			throw 0;
		}
	}
	if (year > 9999 || year < 0 || month < 0 || day < 0) { 
		cout << error_msg << input_string << endl;
		throw 0;
	}
	if (month > 12 || month <= 0) { 
		cout << "Month value is invalid: " << to_string(month) << endl;
		throw 0;
	}
	else if (day > 31 || day <= 0) {
		cout << "Day value is invalid: " << to_string(day) << endl;
		throw 0;
	}
	Date d(year, month, day); 
	return d; 
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
}
bool operator==(const Date& lhs, const Date& rhs) { 
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay()) return true;
	else { return false; }
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) { 
		DateEvents[date].insert(event);
	}
	void DeleteEvent(const Date& date, const string& event) {
		if (DateEvents.count(date) > 0) {
			set<string>& g = DateEvents[date]; 
			if (g.count(event) > 0) { 
				g.erase(event); 
				cout << "Deleted successfully" << endl;
			}
			else {
				cout << "Event not found" << endl;
			}
		}
		else {
			cout << "Event not found" << endl;
		}
	}
	void DeleteDate(const Date& date) { 
		if (DateEvents.count(date) > 0) {
			int i = DateEvents[date].size();
			DateEvents.erase(date);
			cout << "Deleted " << to_string(i) << " events" << endl;
		}
		else {
			cout << "Deleted 0 events" << endl;
		}
	}
	void Find(const Date& date) const { 
		if (DateEvents.count(date) > 0) {
			if (DateEvents.at(date).size() > 0) {
				for (const auto& i : DateEvents.at(date)) {
					if (i != "" && i != " ") {
						cout << i << endl;
					}
				}
			}
		}
	}
	void Print() const { 
		for (const auto& i : DateEvents) {
			if (i.second.size() > 0) {
				for (const auto& j : i.second) {
					if (j != "" && j != " ") { 
						cout << setw(4) << setfill('0') << i.first.GetYear() << "-" <<
							setw(2) << setfill('0') << i.first.GetMonth() << "-" <<
							setw(2) << setfill('0') << i.first.GetDay() << " " << j << endl;
					}
				}
			}
		}
	}
private:
	map<Date, set<string>> DateEvents; 
};
int main() {
	//map<Date, set<string>> DateEvents;
	Database db;
	string line;
	while (getline(cin, line)) { 
		try
		{
			istringstream f(line); 
			string l;
			vector<string> vec; 
			while (f >> l) { 
				vec.push_back(l); 
			}
			if (vec.size() == 0 || vec[0] == "" || vec[0] == " ") { break; } 
			else if (vec[0] == "Add") { 
				if (vec.size() == 1) { 
					cout << "Wrong date format: " << endl;
				}
				else if (vec.size() == 2) { 
					parseDate(vec[1]);
				}
				else if (vec[2] != "" && vec[2] != " ") { 
					db.AddEvent(parseDate(vec[1]), vec[2]); 
				}
				else {
					cout << "Wrong date format: " << vec[1] << endl;
				}
			}
			else if (vec[0] == "Del") {
				if (vec.size() == 2) { 
					db.DeleteDate(parseDate(vec[1])); 
				}
				else if (vec.size() == 1) { 
					cout << "Wrong date format: " << endl;
				}
				else if (vec.size() >= 3) { 
					db.DeleteEvent(parseDate(vec[1]), vec[2]);
				}
				else throw 999; 
			}
			else if (vec[0] == "Find") {
				if (vec.size() == 2) {
					db.Find(parseDate(vec[1]));
				}
				else if (vec.size() == 1) {
					cout << "Wrong date format: " << endl;
				}
			}
			else if (vec[0] == "Print") {
				db.Print();
			}
			else cout << "Unknown command: " << vec[0] << endl;
		}
		catch (const int& f) { 
			if (f == 999) return 0;
		}
		catch (...) { 
			return 0; 
		}
	}
	return 0;
}