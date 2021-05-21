#include "Individual.h"
#include <fstream>
#include <iostream>

void Individual::write(std::fstream& file_name) const
{
	file_name << std::endl;

	file_name << "Individual Student: \n";
	file_name << "Name: " << SNP << std::endl;
	file_name << "Chair: " << chair << std::endl;
	file_name << "Semestr: " << semester << std::endl;
	file_name << "Subjects: " << std::endl;

	for (const std::pair<std::string, size_t>& i : semestrs)
		file_name << i.first << " - " << i.second << std::endl;

	file_name << std::endl;
}

bool Individual::is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const
{
	for (const auto& i : semestrs)
		if (i.first == key)
		{
			vec.push_back(new Individual(SNP, chair, semester, semestrs));
			return true;
		}

	return false;
}

void Individual::push_name(std::vector<Hybrid*>& vec) const
{
	vec.push_back(new Individual(SNP, chair, semester, semestrs));
}

void Individual::set_sems()
{
	std::string command;
	std::string sub;
	std::cout << "Enter the subject: ";
	std::cin >> sub;


	std::cout << "Enter 'mark' if you want to change mark of subject or 'subject' if you want to change the name of subject: ";
	std::cin >> command;

	if (command == "subject")
	{
		std::set<std::pair<std::string, size_t>> as;
		bool flag = false;

		std::vector<std::pair<std::string, size_t>> keys;

		for (auto& j : semestrs)
			if (j.first == sub)
			{
				keys.push_back(std::pair<std::string, size_t>(j.first, j.second));
				flag = true;
				std::cout << "Enter the new name of subject: ";
				std::cin >> command;

				std::pair<std::string, size_t> element;
				element.first = command;
				element.second = j.second;

				as.insert(element);
			}

		for (auto& i : keys)
			semestrs.erase(i);


		if (as.size() != 0)
			for (const std::pair<std::string, size_t>& j : semestrs)
				as.insert(j);

		semestrs = as;

		if (flag)
			std::cout << "Renaming have sucsessfully finished.\n";
		else
			std::cout << "This subject not found.\n";


	}
	else if (command == "mark")
	{
		std::set<std::pair<std::string, size_t>> as;
		bool flag = false;

		std::vector<std::pair<std::string, size_t>> keys;

		for (auto& j : semestrs)
			if (j.first == sub)
			{
				keys.push_back(std::pair<std::string, size_t>(j.first, j.second));
				flag = true;
				std::cout << "Enter the new mark of subject: ";
				std::cin >> command;

				std::pair<std::string, size_t> element;
				element.first = j.first;
				element.second = std::stoi(command);

				as.insert(element);
			}

		for (auto& i : keys)
			semestrs.erase(i);


		if (as.size() != 0)
			for (const std::pair<std::string, size_t>& j : semestrs)
				as.insert(j);

		semestrs = as;

		if (flag)
			std::cout << "Renaming have sucsessfully finished.\n";
		else
			std::cout << "This subject not found.\n";

	}
	else
		std::cout << "Incorrect input.\n";
}

bool Individual::is_excellent() const
{
	size_t counter = 0;
	for (const auto& i : semestrs)
		if (i.second == 5)
			++counter;

	if (counter == semestrs.size())
		return true;
	else
		return false;
}

void Individual::print() const
{
	std::cout << "Individual Student: \n";
	std::cout << "Name: " << SNP << std::endl;
	std::cout << "Chair: " << chair << std::endl;
	std::cout << "Semestr: " << semester << std::endl;
	std::cout << "Subjects: " << std::endl;

	for (const std::pair<std::string, size_t>& i : semestrs)
		std::cout << i.first << " - " << i.second << std::endl;
}
