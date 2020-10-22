#include "Button.h"

#define LABEL_FONT "fonts/arial.ttf"
#define LABEL_SIZE 30

Button::Button(std::string sprite_name, std::string label, cocos2d::ccMenuCallback callback): Layer(), _callback(callback) {
	// sprite image initiated
	button_image = cocos2d::Sprite::create(sprite_name);
	cocos2d::Label* label_node = cocos2d::Label::createWithTTF(label, LABEL_FONT, LABEL_SIZE);
	makeChildOfAndCenter(label_node, button_image, 1);
	makeChildOfAndCenter(button_image, this, 0);
}

bool Button::init() {

	printf("initialized");
	return true;
}

Button* Button::create(std::string sprite_name, std::string label, cocos2d::ccMenuCallback callback){
	auto button = new Button(sprite_name, label, callback);
	button->init();
	return button;
}

bool Button::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event){
	return touchOnButton(touch, unused_event);
}

void Button::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (touchOnButton(touch, event)) {
		_callback(this);
	}
}

bool Button::touchOnButton(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto position = button_image->getPosition();
	position = button_image->convertToWorldSpace(position);
	auto size = button_image->getContentSize();
	cocos2d::Rect control_rect = cocos2d::Rect(position, size);

	return control_rect.containsPoint(touch->getLocation());
}
