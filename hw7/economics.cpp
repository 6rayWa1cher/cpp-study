//
// Created by 6rayWa1cher on 04.02.2020.
//

#include "economics.h"
#include <numeric>

void makeYearReport(const std::map<std::string, std::vector<int>>& employeeToSalaries, std::ostream& ostream) {
	std::vector<std::pair<std::string, int>> employeeToYearSalary;
	employeeToYearSalary.resize(employeeToSalaries.size());
	std::transform(employeeToSalaries.begin(), employeeToSalaries.end(), employeeToYearSalary.begin(),
	               [](auto it) -> std::pair<std::string, int> {
		               const std::string& name = it.first;
		               const std::vector<int>& salaries = it.second;
		               int sum = std::accumulate(salaries.begin(), salaries.end(), 0);
		               return std::pair<std::string, int>(name, sum);
	               });
	std::sort(employeeToYearSalary.begin(), employeeToYearSalary.end(),
	          [](std::pair<std::string, int>& a, std::pair<std::string, int>& b) -> bool {
		          return a.second < b.second;
	          }
	);
	for (const std::pair<std::string, int>& pair : employeeToYearSalary) {
		ostream << pair.first << ' ' << pair.second << '\n';
	}
}
