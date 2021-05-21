#include "General.h"
#include <fstream>
#include <iostream>

void General::write(std::fstream& file_name) const
{
	file_name << "General Student: \n";
	file_name << "Name: " << SNP << std::endl;
	file_name << "Chair: " << chair << std::endl;
	file_name << "Semestr: " << semester << std::endl;
	file_name << "Subjects: " << std::endl;

	size_t counter = 1;
	for (const std::set<std::pair<std::string, size_t>>& i : semestrs)
	{
		file_name << counter << " semestr:\n";
		for (const std::pair<std::string, size_t>& j : i)
			file_name << j.first << " - " << j.second << std::endl;
		++counter;
	}

	file_name << std::endl;
}

bool General::is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const
{
	for (const auto& i : semestrs)
		for (const auto& j : i)
			if (j.first == key)
			{
				vec.push_back(new General(SNP, chair, semester, semestrs));
				return true;
			}

	return false;
}

void General::push_name(std::vector<Hybrid*>& vec) const
{
	vec.push_back(new General(SNP, chair, semester, semestrs));
}

void General::set_sems()
{
	std::string operation;
	std::string command;
	std::string sub;

	std::cout << "Enter the semestr where you want to change something: ";
	std::cin >> command;

	if (std::stoi(command) > semester)
	{
		std::cout << "The maximal semestr is " << semester << ".\n";
		return;
	}

	std::cout << "Enter the subject: ";
	std::cin >> sub;

	std::cout << "Enter 'mark' if you want to change mark of subject or 'subject' if you want to change the name of subject: ";
	std::cin >> operation;

	if (operation == "subject")
	{
		std::cout << "Enter the new name of subject: ";
		std::cin >> operation;

		std::set<std::set<std::pair<std::string, size_t>>> sub_set;

		size_t counter = 0;
		for (auto& i : semestrs)
		{
			std::set<std::pair<std::string, size_t>> sub_sub_set;
			for (auto& k : i)
				sub_sub_set.insert(k);
			++counter;
			if (counter == std::stoi(command))
			{
				bool flag = false;
				std::vector<std::pair<std::string, size_t>> keys;
				std::set<std::pair<std::string, size_t>> as;

				for (auto& j : i)
				{
					if (j.first == sub)
					{
						keys.push_back(std::pair<std::string, size_t>(j.first, j.second));
						flag = true;

						std::pair<std::string, size_t> element;
						element.first = operation ;
						element.second = j.second;

						as.insert(element);
					}
				}

				for (auto& l : keys)
					sub_sub_set.erase(l);

				for (auto& l : as)
					sub_sub_set.insert(l);
			}

			sub_set.insert(sub_sub_set);
		}
		semestrs = sub_set;
	}
	else if (operation == "mark")
	{
		std::cout << "Enter the new mark of subject: ";
		std::cin >> operation;

		std::set<std::set<std::pair<std::string, size_t>>> sub_set;

		size_t counter = 0;
		for (auto& i : semestrs)
		{
			std::set<std::pair<std::string, size_t>> sub_sub_set;
			for (auto& k : i)
				sub_sub_set.insert(k);
			++counter;
			if (counter == std::stoi(command))
			{
				bool flag = false;
				std::vector<std::pair<std::string, size_t>> keys;
				std::set<std::pair<std::string, size_t>> as;

				for (auto& j : i)
				{
					if (j.first == sub)
					{
						keys.push_back(std::pair<std::string, size_t>(j.first, j.second));
						flag = true;

						std::pair<std::string, size_t> element;
						element.first = j.first;
						element.second = std::stoi(operation);

						as.insert(element);
					}
				}

				for (auto& l : keys)
					sub_sub_set.erase(l);

				for (auto& l : as)
					sub_sub_set.insert(l);
			}

			sub_set.insert(sub_sub_set);
		}
		semestrs = sub_set;
	}
	else
		std::cout << "Incorrect input.\n";

}

bool General::is_excellent() const
{
	size_t counter = 0;

	for (const auto& i : *semestrs.rbegin())
		if (i.second == 5)
			++counter;

	if (counter == (*semestrs.rbegin()).size())
		return true;
	else
		return false;
}

void General::print() const
{
	std::cout << std::endl;
	std::cout << "General Student: \n";
	std::cout << "Name: " << SNP << std::endl;
	std::cout << "Chair: " << chair << std::endl;
	std::cout << "Semestr: " << semester << std::endl;
	std::cout << "Subjects: " << std::endl;

	size_t counter = 1;
	for (const std::set<std::pair<std::string, size_t>>& i : semestrs)
	{
		std::cout << counter << " semestr:\n";
		for (const std::pair<std::string, size_t>& j : i)
			std::cout << j.first << " - " << j.second << std::endl;
		++counter;
	}

	std::cout << std::endl;
}
