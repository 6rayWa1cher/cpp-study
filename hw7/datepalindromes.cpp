//
// Created by 6rayWa1cher on 11.02.2020.
//

#include <sstream>
#include "datepalindromes.h"

bool isSpecialYear(int year) {
	if (year % 4 != 0) {
		return false;
	}
	if (year % 100 == 0) {
		return year % 400 == 0;
	} else {
		return true;
	}
}

class Date {
private:
	int day;
	int month;
	int year;
public:
	Date(int day, int month, int year) : day(day), month(month), year(year) {}

	bool operator==(const Date& rhs) const {
		return day == rhs.day &&
		       month == rhs.month &&
		       year == rhs.year;
	}

	bool operator!=(const Date& rhs) const {
		return !(rhs == *this);
	}

	int getDay() const {
		return day;
	}

	int getMonth() const {
		return month;
	}

	int getYear() const {
		return year;
	}

	Date getTomorrow() {
		int monthDays[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (isSpecialYear(year)) {
			monthDays[1]++;
		}
		if (day == 31 && month == 12) {
			return {1, 1, year + 1};
		}
		if (day == monthDays[month]) {
			return {1, month + 1, year};
		}
		return {day + 1, month, year};
	}

	std::string toString(const std::string& delimiter) {
		char buff[30];
		std::snprintf(buff, sizeof(buff),
		              "%02d%s%02d%s%04d", day, delimiter.c_str(), month, delimiter.c_str(), year);
		return buff;
	}

	bool operator<(const Date& rhs) const;
};

bool Date::operator<(const Date& rhs) const {
	if (day < rhs.day)
		return true;
	if (rhs.day < day)
		return false;
	if (month < rhs.month)
		return true;
	if (rhs.month < month)
		return false;
	return year < rhs.year;
}

Date parse(const std::string& input) {
	if (input.size() != 2 + 1 + 2 + 1 + 4) {
		throw std::invalid_argument("Invalid date");
	}
	std::string dayToken = input.substr(0, 2);
	std::string monthToken = input.substr(3, 2);
	std::string yearToken = input.substr(6, 4);
	int day = std::stoi(dayToken);
	int month = std::stoi(monthToken);
	int year = std::stoi(yearToken);
	return {day, month, year};
}

std::vector<std::string> getPalindromeDatesBetween(const std::string& left, const std::string& right) {
	Date leftDate = parse(left);
	Date rightDate = parse(right);
	if (right < left) {
		return std::vector<std::string>();
	}
	Date curr = leftDate;
	std::vector<std::string> out;
	while (curr != rightDate) {
		std::string str = curr.toString("");
		bool result = true;
		for (size_t i = 0, j = str.size() - 1; i <= j; i++, j--) {
			if (str[i] != str[j]) {
				result = false;
				break;
			}
		}
		if (result) {
			out.push_back(curr.toString("."));
		}
		curr = curr.getTomorrow();
	}
	return out;
}
