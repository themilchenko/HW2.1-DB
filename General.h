#include "Hybrid.h"
#include <set>
#include <iostream>

#pragma once

class General final: public Hybrid
{ 
private:
	/*семестр - предметы - оценка за предмет*/
	std::set<std::set<std::pair<std::string, size_t>>> semestrs;

public:
	General(const std::string& name, const std::string& chair, const size_t& semestr, std::set<std::set<std::pair<std::string, size_t>>> sem) :
		Hybrid(name, chair, semestr),
		semestrs(sem)
	{ };

	void write(std::fstream& file_name) const override;

	bool is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const override;

	void push_name(std::vector<Hybrid*>& vec) const override;

	void set_sems() override;

	bool is_excellent() const override;

	void print() const override;

};
