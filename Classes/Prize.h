/**
* Prize class is designed to be immutable after instantiation. The PrizeCreator is a friend that can call the
* private constructor. That is the interface through which prizes will be created. 
*/

#ifndef __PRIZE_NODE_H__
#define __PRIZE_NODE_H__

#include "cocos2d.h"
#include "NodeUtil.h"

enum PRIZE_VALUE_TYPE {
	PRIZE_VALUE_TYPE_INVENTORY, PRIZE_VALUE_TYPE_MINUTES
};

// forward declaration for friend
class PrizeCreator;

class Prize : public cocos2d::Sprite {
public:
	friend PrizeCreator;

	float getRelativeProbability() const;
	unsigned int getCount() const;
	PRIZE_VALUE_TYPE getPrizeValueType() const;

private:
	Prize(const std::string& file_name, const std::string& prize_name, const unsigned int count, const float relative_probability, const PRIZE_VALUE_TYPE type);

	bool init() override;

	const float relative_probability;
	const unsigned int count;
	const std::string& prize_name;
	const PRIZE_VALUE_TYPE type;
};

#endif
