#include <string>

#pragma once

class Hybrid
{
public:
	virtual bool is_excellent() const = 0;
	//virtual std::string& find_student(std::string& name) const = 0;*/

	virtual void write(std::fstream& file_name) const = 0;  /*запись данных в файл*/

	virtual bool is_name(const std::string& name) = 0;

	virtual std::string get_name() const = 0;
	virtual size_t get_semestr() const = 0;
	virtual std::string get_chair() const = 0;

	virtual bool is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const = 0;
	virtual void push_name(std::vector<Hybrid*>& vec) const = 0;

	virtual void set_name(const std::string& name) = 0;
	virtual void set_chair(const std::string& new_ch) = 0;
	virtual void set_semestr(size_t sem) = 0;
	virtual void set_sems() = 0;

	virtual void print() const = 0;
};