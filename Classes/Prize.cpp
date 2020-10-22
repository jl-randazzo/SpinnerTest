#include "Prize.h"

using namespace cocos2d;

#define LABEL_SIZE 24 
#define SUB_LABEL_SIZE_DIF 8
#define LABEL_OFFSET Vec2(10, -20)
#define SUB_LABEL_OFFSET Vec2(5, -15)
#define LABEL_FONT "fonts/arial.ttf"
#define OUTLINE_COLOR Color4B(40, 95, 140, 255)

bool Prize::init() {
	std::string value_label;
	Label* label = nullptr;

	switch (type) {
		case PRIZE_VALUE_TYPE_INVENTORY:
			value_label = std::string("x") + std::to_string(count);
			label = Label::createWithTTF(value_label, LABEL_FONT, LABEL_SIZE);
			break;
		case PRIZE_VALUE_TYPE_MINUTES:
			label = Label::createWithTTF(std::to_string(count), LABEL_FONT, LABEL_SIZE);
			Label* child = Label::createWithTTF("Min.", LABEL_FONT, LABEL_SIZE - SUB_LABEL_SIZE_DIF);
			child->enableOutline(OUTLINE_COLOR, 1);
			makeChildOfAndCenter(child, label, -1);
			child->setPosition(child->getPosition() + SUB_LABEL_OFFSET);
			break;
	}

	if (label) {
		label->enableOutline(OUTLINE_COLOR, 1);
		makeChildOfAndCenter(label, this, 2);
		label->setPosition(label->getPosition() + LABEL_OFFSET);
		return true;
	} else {
		return false;
	}
};

unsigned int Prize::getCount() const {
	return count;
}

PRIZE_VALUE_TYPE Prize::getPrizeValueType() const{
	return type;
}
;

float Prize::getRelativeProbability() const {
	return relative_probability;
};

Prize::Prize(const std::string& file_name, const std::string& prize_name, const unsigned int count, const float relative_probability, PRIZE_VALUE_TYPE type) 
	: Sprite(), prize_name(prize_name), relative_probability(relative_probability), count(count), type(type) {

	// initialize base Sprite class
	initWithFile(file_name);
}