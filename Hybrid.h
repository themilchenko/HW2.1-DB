#include <string>
#include <vector>

#pragma once

class Hybrid
{
protected:
	std::string SNP;
	std::string chair;
	size_t semester;

public:
	Hybrid(const std::string& name, const std::string& lvl, size_t sem) : SNP(name), chair(lvl), semester(sem) { };

	virtual bool is_excellent() const = 0;

	virtual void write(std::fstream& file_name) const = 0;  /*запись данных в файл*/

	virtual bool is_name(const std::string& name)
	{
		if (SNP == name)
		{
			return 1;
		}
	};

	std::string get_name() const { return SNP; };
	size_t get_semestr() const { return semester; };
	std::string get_chair() const { return chair; };

	virtual bool is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const = 0;
	virtual void push_name(std::vector<Hybrid*>& vec) const = 0;

	void set_name(const std::string& name) { SNP = name; };
	void set_chair(const std::string& new_ch) { chair = new_ch; };
	void set_semestr(size_t sem) { semester = sem; };
	virtual void set_sems() = 0;

	virtual void print() const = 0;
};
