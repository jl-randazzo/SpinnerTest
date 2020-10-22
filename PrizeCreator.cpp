#include "PrizeCreator.h"

PrizeCreator& PrizeCreator::setPrizeName(std::string prize_name){
	this->prize_name = prize_name;
	return *this;
}

PrizeCreator& PrizeCreator::setPrizeIcon(std::string png_file_name){
	this->png_file_name = png_file_name;
	return *this;
}

PrizeCreator& PrizeCreator::setPrizeRelativeProbability(float value){
	this->value = value;
	return *this;
}

PrizeCreator& PrizeCreator::setPrizeCount(unsigned int count){
	this->count = count;
	return *this;
}

PrizeCreator& PrizeCreator::setPrizeValueType(PRIZE_VALUE_TYPE type) {
	this->type = type;
	return *this;
}

Prize* PrizeCreator::create(){
	Prize* prize = new Prize(png_file_name, prize_name, count, value, type);
	CCASSERT(prize->init(), (std::string("Failed to initialize Prize ") + prize_name).data());
	return prize;
}
