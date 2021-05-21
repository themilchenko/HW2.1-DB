#include "Hybrid.h"
#include <set>
#include <string>
#include <iostream>

#pragma once

class Individual final : public Hybrid
{
private:
	std::set<std::pair<std::string, size_t>> semestrs;

public:
	Individual(const std::string& snp, const std::string& ch, size_t sem, const std::set<std::pair<std::string, size_t>>& sems) :
		Hybrid(snp, ch, sem), semestrs(sems) { };

	void write(std::fstream& file_name) const override;

	bool is_same_subjects(const std::string& key, std::vector<Hybrid*>& vec) const override;

	void push_name(std::vector<Hybrid*>& vec) const override;

	void set_sems() override;

	bool is_excellent() const override;

	void print() const override;

};
