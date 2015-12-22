#include "StdAfx.h"
#include "BaseLayer.h"

USING_NS_CC;

void BaseLayer::appear()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto label = LabelTTF::create("Game Over", "Arial", 50);
	addChild(label);
	
	this->setPosition(Point(origin.x+visibleSize.width/2, origin.y-visibleSize.height/2));
	auto moveTo = MoveTo::create(0.5, Point(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	auto easeBounceOut = EaseBackOut::create(moveTo);
	this->runAction(easeBounceOut);
}

void BaseLayer::disappear()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto moveTo = MoveTo::create(0.5, Point(origin.x+visibleSize.width/2, origin.y-visibleSize.height/2));
	auto easeBounceIn = EaseBackIn::create(moveTo);
	Sequence *seq = Sequence::create(easeBounceIn, RemoveSelf::create(true), NULL);
	this->runAction(seq);
}

void BaseLayer::close()
{
	disappear();
}