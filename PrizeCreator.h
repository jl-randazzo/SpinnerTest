#pragma once

#include "Classes/Prize.h"

/**
* The PrizeCreator class is a simple builder-pattern class that can be used to generate
* multiple prizes with similar, only slightly changed information. It is an extensible solution
* that decouples the Prize class's init() call from it's constructor
*/
class PrizeCreator {

public:
	PrizeCreator() : count(0), value(0.0f), prize_name(), png_file_name(), type(PRIZE_VALUE_TYPE_INVENTORY){};

	PrizeCreator& setPrizeName(std::string prize_name);

	PrizeCreator& setPrizeIcon(std::string png_file_name);

	PrizeCreator& setPrizeRelativeProbability(float value);

	PrizeCreator& setPrizeCount(unsigned int count);

	PrizeCreator& setPrizeValueType(PRIZE_VALUE_TYPE type);

	Prize* create();

private:
	unsigned int count;
	float value;
	PRIZE_VALUE_TYPE type;

	std::string prize_name;
	std::string png_file_name;
};
