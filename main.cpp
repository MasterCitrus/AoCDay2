#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> Split(std::string string, std::string delim);
bool IsSafeReport(std::vector<int> report);
bool MakeSafe(std::vector<int> report);

int main()
{
	std::ifstream io;
	io.open("input.txt");
	std::vector<std::vector<int>> reports;
	std::vector<std::vector<int>> reports2;

	for (std::string line; std::getline(io, line);)
	{
		std::vector<std::string> tempLine;
		std::vector<int> report;
		tempLine = Split(line, " ");
		for (auto s : tempLine) report.push_back(std::stoi(s));
		if (IsSafeReport(report)) reports.push_back(report);
		if (MakeSafe(report)) reports2.push_back(report);
	}

	std::cout << "Safe reports: " << reports.size() << '\n';
	std::cout << "Dampener\nSafe Reports: " << reports2.size() << '\n';
}

std::vector<std::string> Split(std::string string, std::string delim)
{
	std::vector<std::string> substrings;
	std::string token;
	while (true)
	{
		std::size_t findFirst = string.find(delim);
		if (findFirst == std::string::npos)
		{
			substrings.push_back(string);
			return substrings;
		}

		token = string.substr(0, string.find(delim));
		string = string.substr(string.find(delim) + delim.size());
		substrings.push_back(token);
	}
	return substrings;
}

bool IsSafeReport(std::vector<int> report)
{
	bool ascending = report[0] < report[1];
	bool descending = report[0] > report[1];

	for (std::size_t i = 0; i < report.size() - 1; i++)
	{
		int diff = std::abs(report[i] - report[i + 1]);
		if (diff < 1 || diff > 3) return false;
		if (ascending && report[i] > report[i + 1]) return false;
		if (descending && report[i] < report[i + 1]) return false;
	}
	return true;
}

bool MakeSafe(std::vector<int> data)
{
	for (std::size_t i = 0; i < data.size(); i++)
	{
		auto report = data;
		report.erase(report.begin() + i);
		if (IsSafeReport(report)) return true;
	}
	return false;
}