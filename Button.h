/*
 * Basic click button implementation. 
 */
#include "cocos2d.h"
#include "2d/CCMenuItem.h"
#include "NodeUtil.h"

class Button : public virtual cocos2d::Layer {

public:
	static Button* create(std::string sprite_name, std::string label, cocos2d::ccMenuCallback callback);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;

	bool init() override;

private:

	bool touchOnButton(cocos2d::Touch* touch, cocos2d::Event* event) ;

	const cocos2d::ccMenuCallback _callback;

	cocos2d::Sprite* button_image;

	Button(std::string sprite_name, std::string label, cocos2d::ccMenuCallback callback);
};
