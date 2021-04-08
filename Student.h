#include <string>
#include <vector>
#include "Hybrid.h"

#pragma once

class Student 
{

protected:

	std::string SNP;
	std::string chair;
	size_t semester;

public:

	Student(const std::string& name, const std::string& lvl, size_t sem) : SNP(name), chair(lvl), semester(sem) { };

};