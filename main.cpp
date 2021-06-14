#include <algorithm>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

#include "Hybrid.h"
#include "Individual.h"
#include "General.h"

namespace fs = std::filesystem;

size_t count_excellent(const std::vector<Hybrid*>& vec)
{
	size_t counter = 0;

	for (const auto& i : vec)
		if (i->is_excellent())
			++counter;

	return counter;
}

bool search(const std::string& name, const std::vector<Hybrid*>& vec)
{
	for (const auto& i : vec)
		if (i->get_name() == name)
		{
			i->print();
			return true;
		}
	return false;
}

void help()
{
	std::cout << std::endl;
	std::cout << "===================================\n";
	std::cout << "> If you want to create database, press '1'\n"
		"> If you want to see list of current DB press '2'\n"
		"> If you want to delete DB press 3;\n"
		"> If you want to rename DB press 4;\n"
		"> If you want to open DB press 5;\n"
		"> If you want to save DB press 6;\n"
		"> If you want to add notes in DB press 7;\n"
		"> If you want to delete notes in DB press 8'\n"
		"> If you want to read DB press 9;\n"
		"> If you want to sort DB press 10;\n"
		"> If you want to create subset press 11;\n"
		"> If you want to save subset such as new DB press 12'\n"
		"> If you want to edit notes press 13;\n"
		"> If you want to count the number of people who've got onle excellent marks press 14;\n"
		"> If you want to search people in DB press 15;\n"
		"> If you want to finish work press '0'.\n";
	std::cout << "===================================\n";
	std::cout << "-- Also don't write the name of file with '.txt'.\n";
	std::cout << "-- Don't forget to close DB after finish of working with it.\n";
	std::cout << std::endl;
}

void read(std::fstream& input, std::vector<Hybrid*>& vec)
{
	while (!input.eof())
	{
		size_t counter = 0;
		std::string current;
		std::getline(input, current);

		if (current.find("Individual") != -1)
		{
			std::string snp;
			std::string chair;
			size_t semesetr;
			std::set<std::pair<std::string, size_t>> semestrs;

			while (!input.eof())
			{
				std::getline(input, current);

				if (current.find("Name") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					snp = current;
				}

				else if (current.find("Chair") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					chair = current;
				}

				else if (current.find("Semestr") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					semesetr = std::stoi(current);
				}

				else if (current.find("Subjects") != -1)
				{
					while (!input.eof())
					{
						std::getline(input, current);

						if (current == "")
							break;

						std::string second = current;
						size_t position = current.find('-');
						current.erase(current.begin() + position - 1, current.end());
						second.erase(second.begin(), second.begin() + position + 1);
						std::pair<std::string, size_t> p;
						p.first = current;
						p.second = std::stoi(second);
						semestrs.insert(p);
					}
					vec.push_back(new Individual(snp, chair, semesetr, semestrs));
					break;
				}
			}
		}

		else if (current.find("General") != -1)
		{
			std::string snp;
			std::string chair;
			size_t semesetr;
			std::set<std::set<std::pair<std::string, size_t>>> semestrs;

			while (!input.eof())
			{
				std::getline(input, current);

				if (current.find("Name") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					snp = current;
				}

				else if (current.find("Chair") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					chair = current;
				}

				else if (current.find("Semestr") != -1)
				{
					size_t pos = current.find(':');
					current.erase(current.begin(), current.begin() + pos + 2);
					semesetr = std::stoi(current);
				}

				else if (current.find("Subjects") != -1)
				{
					std::getline(input, current);
					std::set<std::pair<std::string, size_t>> part;

					while (!input.eof())
					{
						std::getline(input, current);

						if (current == "")
						{
							semestrs.insert(part);
							part.clear();
							break;
						}

						if (current.find("semestr") != -1)
						{
							semestrs.insert(part);
							part.clear();
							continue;
						}

						std::string second = current;
						size_t position = current.find('-');
						current.erase(current.begin() + position - 1, current.end());
						second.erase(second.begin(), second.begin() + position + 1);
						std::pair<std::string, size_t> p;
						p.first = current;
						p.second = std::stoi(second);
						part.insert(p);
					}
					vec.push_back(new General(snp, chair, semesetr, semestrs));
					break;
				}
			}
		}
	}
}

bool is_empty()
{
	size_t counter = 0;

	for (const auto& i : fs::directory_iterator(fs::current_path() / "DB"))
		++counter;

	if (counter == 0)
		return true;
	else
		return false;
}

bool sort_name(const Hybrid* left, const Hybrid* right)
{
	return left->get_name() < right->get_name();
}

bool sort_semestr(const Hybrid* left, const Hybrid* right)
{
	return left->get_semestr() < right->get_semestr();
}

int main()
{
	if (!fs::exists(fs::current_path() / "DB"))             /*если нет ктатлога с БД - создать его*/
		fs::create_directory(fs::current_path() / "DB");

	std::string str_command = "";
	std::string file_name = "";
	std::string reserv_file_name = "";
	std::fstream file(fs::current_path() / "DB");
	file.close();

	std::vector<Hybrid*> DB;
	std::vector<Hybrid*> DB_subset;

	std::cout << "Hello, user!\n";

	try
	{
		do
		{

			help();
			std::cout << "Your choise: ";
			std::cin >> str_command;
			std::transform(str_command.begin(), str_command.end(), str_command.begin(), ::tolower);

			switch (std::stoi(str_command))
			{
			case 1: /*Создание однотипных БД и гибридных БД.*/
			{
				std::string DB_name;
				std::cout << "Name your database: ";
				std::cin >> DB_name;
				DB_name += ".txt";

				try
				{
					if (fs::exists(fs::current_path() / "DB" / DB_name))
						throw std::exception("The DB with the same name is already exists, try again\n");
					std::ofstream OutputFile(fs::current_path() / "DB" / DB_name);
					OutputFile.close();
					std::cout << "The DB was created sucsessfully.\n";
				}
				catch (const std::exception& error)
				{
					std::cerr << error.what();
				}
				system("pause");
				break;
			}

			case 2: /*Вывод на экран списка существующих БД.*/
			{
				std::cout << std::endl;

				if (!is_empty())
					for (const auto& i : fs::directory_iterator(fs::current_path() / "DB"))
						std::cout << '>' << i.path().filename() << std::endl;
				else
					std::cout << "There aren't databases.";
				std::cout << std::endl;

				system("pause");
				break;
			}

			case 3: /*Удаление БД.*/
			{
				std::string removable_file;
				std::cout << "Type, what DB you want to delete: ";
				std::cin >> removable_file;

				removable_file += ".txt";

				if (fs::exists(fs::current_path() / "DB" / removable_file))
				{
					fs::remove(fs::current_path() / "DB" / removable_file);
					std::cout << "Deleting was finished sucsessfully.\n";
				}
				else
					std::cout << "The DB with this name doesn't exist.\n";

				system("pause");
				break;
			}

			case 4: /*Переименовывание БД.*/
			{
				std::string old_file;
				std::string new_file;

				std::cout << "Type the file you want to rename: ";
				std::cin >> old_file;
				old_file += ".txt";

				if (fs::exists(fs::current_path() / "DB" / old_file))
				{
					std::cout << "Type the name you want to change to: ";
					std::cin >> new_file;
					new_file += ".txt";
					fs::rename(fs::current_path() / "DB" / old_file, fs::current_path() / "DB" / new_file);
					std::cout << "Renaming have finished sucsessfully.\n";
				}
				else
				{
					std::cout << "File with this name doesnt't exist.\n";
				}

				system("pause");
				break;
			}

			case 5: /*Открытие БД.*/
			{
				std::cout << "Type the name of file you want to open: ";
				std::cin >> file_name;
				file_name += ".txt";

				if (fs::exists(fs::current_path() / "DB" / file_name))
				{
					file.open(fs::current_path() / "DB" / file_name);
					std::cout << "File has opened sucsessfully.\n";
				}
				else
					std::cout << "File doesen't exist.\n";

				system("pause");
				break;
			}

			case 6: /*Сохранение БД.*/
			{

				if (file_name != "")
				{
					file.close();

					for (Hybrid* i : DB)
						delete i;
					DB.clear();

					file_name = "";
					std::cout << "File has saved sucsessfully.\n";
				}
				else
					std::cout << "File hasn't been opened yet.\n";

				system("pause");
				break;
			}

			case 7: /*Добавление записей в БД.*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					std::string plan;

					std::cout << "Enter plan of student ('individual' or 'general'): ";
					std::cin >> plan;
					std::transform(plan.begin(), plan.end(), plan.begin(), ::tolower);

					std::string name;
					std::cout << "Enter the name, surname and patronymic of student: ";
					std::cin.ignore();
					std::getline(std::cin, name);

					std::string chair;
					std::cout << "Enter the chair of student: ";
					std::cin >> chair;

					size_t semestr;
					std::cout << "Enter the semestr of student: ";
					std::cin >> semestr;

					if (plan == "individual")
					{
						std::set<std::pair<std::string, size_t>> list;
						size_t subject_num;
						std::cout << "Enter the num of subjects: ";
						std::cin >> subject_num;

						for (size_t i = 0; i < subject_num; ++i)
						{
							std::pair<std::string, size_t> element;
							std::cout << "Enter the name of subject: ";
							std::cin.ignore();
							std::getline(std::cin, element.first);
							std::cout << "Enter the mark for this subject: ";
							std::cin >> element.second;

							list.insert(element);
						}

						read(file, DB);
						DB.push_back(new Individual(name, chair, semestr, list));

						file.close();
						file.open(fs::current_path() / "DB" / file_name, std::ofstream::out | std::ofstream::trunc);
						
						for (const auto& i : DB)
							i->write(file);

						std::cout << "Your note has sucsessfully written.\n";
					}
					else if (plan == "general")
					{

						std::set<std::set<std::pair<std::string, size_t>>> list;

						for (int i = 0; i < semestr; ++i)
						{
							size_t num;
							std::cout << "Enter the num of subjects in " << i + 1 << " semest: ";
							std::cin >> num;
							std::set<std::pair<std::string, size_t>> part;
							for (int j = 0; j < num; ++j)
							{
								std::pair<std::string, size_t> element;
								std::cout << "Enter the name of subject: ";
								std::cin.ignore();
								std::getline(std::cin, element.first);
								std::cout << "Enter the mark for this subject: ";
								std::cin >> element.second;
								part.insert(element);
							}
							list.insert(part);
						}

						read(file, DB);
						DB.push_back(new General(name, chair, semestr, list));

						file.close();
						file.open(fs::current_path() / "DB" / file_name, std::ofstream::out | std::ofstream::trunc);

						for (const auto& i : DB)
							i->write(file);

						std::cout << "Your note has sucsessfully written.\n";
					}
					else
						std::cout << "Incorrect input.\n";
				}
				else
					std::cout << "File doesen't open.\n";

				system("pause");
				break;
			}

			case 8: /*Удаление записей в БД.*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					std::string people;

					std::cout << "Type the SNP of people which notes you want to delete: ";
					std::cin.ignore();
					std::getline(std::cin, people);

					read(file, DB);

					int counter = 0;
					size_t people_counter = 0;

					for (Hybrid* i : DB)
					{
						if (i->is_name(people))
						{
							++people_counter;
							delete i;
							DB.erase(DB.begin() + counter);
							--counter;
						}
						++counter;
					}

					if (people_counter > 0)
					{
						file.close();
						file.open(fs::current_path() / "DB" / file_name, std::ofstream::out | std::ofstream::trunc);
						for (Hybrid*& i : DB)
							i->write(file);
						std::cout << "Deleting was finished sucsessfully.\n";
					}
					else
						std::cout << "People you've searched not found.\n";
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			case 9: /*Вывод на экран записей БД.*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					if (fs::file_size(fs::current_path() / "DB" / file_name) == 0)
						std::cout << "File is empty.\n";
					else
					{
						std::string current;
						while (!file.eof())
						{
							std::getline(file, current);
							std::cout << current << std::endl;
						}
					}
				}
				else
					std::cout << "File not open\n";

				system("pause");
				break;
			}

			case 10: /*Сортировка записей БД.*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					std::string sort_cmnd;
					std::cout << "Press 'name' to sort students by SNP and press 'semestr' to sort by semestr: ";
					std::cin >> sort_cmnd;

					for (auto& i : DB)
						delete i;
					DB.clear();

					read(file, DB);

					if (sort_cmnd == "name")
						std::sort(DB.begin(), DB.end(), sort_name);
					else if (sort_cmnd == "semestr")
						std::sort(DB.begin(), DB.end(), sort_semestr);

					file.close();
					file.open(fs::current_path() / "DB" / file_name, std::ofstream::out | std::ofstream::trunc);

					for (const auto& i : DB)
						i->write(file);

					std::cout << "Sorting finished sucsessfully.\n";
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			case 11: /*Выборка записей БД по правилу (подмножество записей).*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					std::string cmnd;
					std::cout << "If you want to chose people by name of chair press 'name'\n"
						"If you want to chose people by subject press 'subject'\n"
						"Your choise: ";
					std::cin >> cmnd;

					for (auto& i : DB)
						delete i;
					DB.clear();

					read(file, DB);

					if (cmnd == "name")
					{
						std::cout << "Enter the chair of student: ";
						std::cin >> cmnd;

						for (const auto& i : DB)
							if (i->get_chair() == cmnd)
								i->push_name(DB_subset);

						for (auto& i : DB)
							delete i;

						DB.clear();

						if (DB_subset.size() == 0)
							std::cout << "There are no one student you search.\n";
						else
						{
							std::cout << "The set of students has createdif you want to save this press 13 in menu.\n";
							std::cout << "There are students you have choosen:\n";

							for (const auto& i : DB_subset)
								i->print();
						}
					}
					else if (cmnd == "subject")
					{
						std::cout << "Enter the name of subject: ";
						std::cin >> cmnd;

						for (const auto& i : DB)
							i->is_same_subjects(cmnd, DB_subset);

						for (auto& i : DB)
							delete i;

						DB.clear();

						if (DB_subset.size() == 0)
							std::cout << "There are no one student you search.\n";
						else
						{
							std::cout << "The set of students has created, if you want to save this press 13 in menu.\n";
							std::cout << "There are students you have choosen:\n";

							for (const auto& i : DB_subset)
								i->print();
						}
					}
					else
						std::cout << "Incorrect input.\n";
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			case 12: /*Сохранение выборки как новой БД (по желанию пользователя).*/
			{
				if (DB_subset.size() > 0)
				{
					std::cout << "Enter the name of new DB: ";
					std::cin >> reserv_file_name;
					reserv_file_name += ".txt";

					std::fstream File(fs::current_path() / "DB" / reserv_file_name, std::ios::out);

					if (File.is_open())
						for (const auto& i : DB_subset)
							i->write(File);

					File.close();
					reserv_file_name = "";

					std::cout << "The set has successfully writen in file.\n";
				}
				else
					std::cout << "To go to this point you should press previous point.\n";
				system("pause");
				break;
			}

			case 13: /*Редактирование записей в БД.*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					for (auto& i : DB)
						delete i;

					DB.clear();

					read(file, DB);

					int num;
					std::string name;
					std::cout << "Enter the SNP of student you want to change parametres: ";
					std::cin.ignore();
					std::getline(std::cin, name);

					std::cout << "Enter the parametr you want to change. There are \n"
						"1. SNP;\n"
						"2. Chair;\n"
						"3. Semestr;\n"
						"4. Subjects.\n"
						"Enter the number: ";
					std::cin >> num;

					for (auto& i : DB)
					{
						if (i->get_name() == name)
						{
							switch (num)
							{
								case 1:
								{
									std::string new_str;
									std::cout << "Enter the new SNP: ";
									std::cin.ignore();
									std::getline(std::cin, new_str);

									i->set_name(new_str);
									std::cout << "Name has editten.\n";
									break;
								}
								case 2:
								{
									std::string new_ch;
									std::cout << "Enter the new chair: ";
									std::cin >> new_ch;

									i->set_chair(new_ch);
									std::cout << "Chair has editten.\n";
									break;
								}
								case 3:
								{
									size_t sem;
									std::cout << "Enter the new semestr: ";
									std::cin >> sem;

									i->set_semestr(sem);
									std::cout << "Semestr has editten.\n";
									break;
								}
								case 4:
								{
									i->set_sems();
									break;
								}

							}
						}
					}
					file.close();
					file.open(fs::current_path() / "DB" / file_name, std::ofstream::out | std::ofstream::trunc);

					for (auto& i : DB)
						i->write(file);
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			case 14: /*Подсчет количества отличников*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					read(file, DB);
					size_t num = count_excellent(DB);
					if (num != 0)
						std::cout << "There are " << num << " students who've got only excellent marks";
					else
						std::cout << "There aren't excellent students.\n";

					for (auto& i : DB)
						delete i;
					DB.clear();
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			case 15: /*Поиск студента*/
			{
				file.close();
				file.open(fs::current_path() / "DB" / file_name);

				if (file.is_open())
				{
					read(file, DB);
					std::string name;
					std::cout << "Enter the SNP of student: ";
					std::cin.ignore();
					std::getline(std::cin, name);

					if (search(name, DB))
						continue;
					else
						std::cout << "There aren't students with this name.\n";

					for (auto& i : DB)
						delete i;
					DB.clear();
				}
				else
					std::cout << "File not open.\n";

				system("pause");
				break;
			}

			default:
			{
				std::cout << "Incorrect input\n";
				break;
			}

			}

		} while (std::stoi(str_command) != 0);
	}
	catch(const std::exception& error)
	{
		std::cerr << error.what();
	}

	return 0;
}
