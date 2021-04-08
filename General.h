#include "Student.h"
#include "Hybrid.h"
#include <set>

#pragma once

class General final: public Student, public Hybrid
{ 
private:
	/*семестр - предметы - оценка за предмет*/
	std::set<std::set<std::pair<std::string, size_t>>> semestrs;

public:
	General(const std::string& name, const std::string& chair, const size_t& semestr, std::set<std::set<std::pair<std::string, size_t>>> sem) :
		Student(name, chair, semestr),
		semestrs(sem)
	{ };

	void write(std::fstream& file_name) const override;

	bool is_name(const std::string& name) override;

	std::string get_name() const override { return SNP; };
	size_t get_semestr() const override { return semester; };
	std::string get_chair() const override { return chair; };

	bool is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const override;

	void push_name(std::vector<Hybrid*>& vec) const override;

	void set_name(const std::string& name) override { SNP = name; };
	void set_chair(const std::string& new_ch) override { chair = new_ch; };
	void set_semestr(size_t sem) override { semester = sem; };
	void set_sems() override;

	bool is_excellent() const override;

	void print() const override;

};