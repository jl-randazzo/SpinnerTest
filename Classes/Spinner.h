/****************************************************************************
Spinner class def is intended to encapsulate 
*****************************************************************************/

#define SPINNER_SECTIONS 8

#ifndef __SPINNER_NODE_H__
#define __SPINNER_NODE_H__

#include "cocos2d.h"
#include "Prize.h"
#include "../PropertyAnimator.h"

class Spinner : public cocos2d::Sprite {
public:
	bool init() override;

	void spin(cocos2d::Ref* ref);

	void update(float delta) override;

	static Spinner* create(const std::string& file_name, const std::vector<Prize*> prizes);

private:
	Spinner(const std::string& file_name, const std::vector<Prize*>& prizes);

	const std::vector<Prize*> prizes;
	PropertyAnimator<cocos2d::Quaternion>* rot_animator;
	float probabilityLevels[SPINNER_SECTIONS];
};

#endif // __SINNER_NODE_H__
