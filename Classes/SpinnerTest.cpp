/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
* This class was adapted from the initial 'SpinnerTestScene' root class provided in the Cocos2D
* basic project. Some elements of this class will likely be unchanged from that original implementation
* though the name has changed. 
*
* All other related classes were written by me specifically, Luke Randazzo
*/

#include "SpinnerTest.h"

#define PI 3.1415926535897932385f
#define BUTTON_OFFSET Vec2(0, -340)
#define ARROW_OFFSET Vec2(0, 290)

USING_NS_CC;

Scene* SpinnerTest::createScene()
{
    return SpinnerTest::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SpinnerTestScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SpinnerTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SpinnerTest::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
	// decided to leave this as a simple way to exit the program - Luke Randazzo
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	// initializing the prize builders
	PrizeCreator coin_creator, brush_creator, heart_creator, gem_creator, hammer_creator;
	coin_creator.setPrizeIcon("coin.png").setPrizeName("Coin");
	hammer_creator.setPrizeIcon("hammer.png").setPrizeName("Hammer");
	gem_creator.setPrizeIcon("gem.png").setPrizeName("Gem");
	heart_creator.setPrizeIcon("heart.png").setPrizeName("Life").setPrizeValueType(PRIZE_VALUE_TYPE_MINUTES);
	brush_creator.setPrizeIcon("brush.png").setPrizeName("Brush");

	// populating the prizes list
	std::vector<Prize*> prizes;
	prizes.push_back(brush_creator.setPrizeCount(1).setPrizeRelativeProbability(.2f).create());
	prizes.push_back(coin_creator.setPrizeCount(750).setPrizeRelativeProbability(.05f).create());
	prizes.push_back(gem_creator.setPrizeCount(35).setPrizeRelativeProbability(.1f).create());
	prizes.push_back(heart_creator.setPrizeCount(30).setPrizeRelativeProbability(.2f).create());
	prizes.push_back(hammer_creator.setPrizeCount(1).setPrizeRelativeProbability(.2f).create());
	prizes.push_back(gem_creator.setPrizeCount(75).setPrizeRelativeProbability(.05f).create());
	prizes.push_back(brush_creator.setPrizeCount(3).setPrizeRelativeProbability(.1f).create());
	prizes.push_back(hammer_creator.setPrizeCount(3).setPrizeRelativeProbability(.2f).create());

	// creating the spinner
	auto spinner = Spinner::create("wheel_sections_8.png", prizes);
	spinner->setScale(1.5);
	spinner->setAnchorPoint(Vec2(.5, .5));
	this->addChild(spinner, 0);
	Quaternion init_rot = Quaternion(Vec3::UNIT_Z, PI / 8);
	spinner->setRotationQuat(init_rot);
	spinner->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	ccMenuCallback callback = CC_CALLBACK_1(Spinner::spin, spinner);
	auto button = Button::create("spin_button.png", "Spin", callback);
	makeChildOfAndCenter(button, this, 1);
	button->setPosition(button->getPosition() + BUTTON_OFFSET);

	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, button);
	touchListener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, button);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, button);

	auto arrow = Sprite::create("wheel_arrow.png");
	arrow->setScale(1.5);
	makeChildOfAndCenter(arrow, this, 4);
	arrow->setPosition(arrow->getPosition() + ARROW_OFFSET);

    return true;
}


void SpinnerTest::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
