#include "NodeUtil.h"

void makeChildOfAndCenter(cocos2d::Node* child, cocos2d::Node* parent, int relative_z){
	parent->addChild(child, relative_z);
	cocos2d::Size size = parent->getContentSize();
	child->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2));
}
