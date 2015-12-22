#include "StdAfx.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene::~GameScene()
{
	if (_gameMode != NULL) {
		delete _gameMode;
		_gameMode = NULL;
	}
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// draw board
	DrawBoard();

	// events
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onMyTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onMyTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_gameMode = new GameModel(this);
	_gameMode->DoRobotAction();
	return true;
}

bool GameScene::onMyTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}

void GameScene::onMyTouchEnded(Touch *touch, Event *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float xstep = visibleSize.width / 3.0;
	float ystep = visibleSize.height / 3.0;

	int idest = 0;
	int jdest = 0;
	bool stoploop = false;
	Vec2 loc = touch->getLocation();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			//if (cocos2d::Rect(origin.x + (i * xstep), origin.y + (j * ystep), xstep, ystep).containsPoint(touch->getLocation())) {
			if (cocos2d::Rect(origin.x + (i * xstep), origin.y + (j * ystep), xstep, ystep).containsPoint(loc)) {
				idest = i;
				jdest = j;
				stoploop = true;
				break;
			}
		}
		if (stoploop) break;
	}
	DrawChessman(_gameMode->GetMyChessman(), idest, jdest);
	_gameMode->Do(idest, jdest);
}

void GameScene::DrawBoard()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto draw = DrawNode::create();
	draw->drawLine(Vec2(origin.x, origin.y + visibleSize.height / 3)
		, Vec2(origin.x + visibleSize.width, visibleSize.height / 3)
		, Color4F(0.5,0.5,0.5,0.5));
	draw->drawLine(Vec2(origin.x, origin.y + visibleSize.height * 2 / 3)
		, Vec2(origin.x + visibleSize.width, visibleSize.height * 2 / 3)
		, Color4F(0.5,0.5,0.5,0.5));

	draw->drawLine(Vec2(origin.x + visibleSize.width / 3, origin.y)
		, Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height)
		, Color4F(0.5,0.5,0.5,0.5));
	draw->drawLine(Vec2(origin.x + visibleSize.width * 2 / 3, origin.y)
		, Vec2(origin.x + visibleSize.width * 2 / 3, origin.y + visibleSize.height)
		, Color4F(0.5,0.5,0.5,0.5));
	addChild(draw);
}

void GameScene::DrawChessman(int chessman, int idest, int jdest)
{
	int tag = (idest<<16) | jdest;
	auto child = getChildByTag(tag);
	if (child != nullptr) {
		removeChild(child, true);
	} else {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		float xstep = visibleSize.width / 3.0;
		float ystep = visibleSize.height / 3.0;
		if (chessman == TIC_VALUE) {
			float crossoffset = xstep * 1 / 8;
			auto draw = DrawNode::create();
			draw->drawLine(Vec2(origin.x + xstep * idest + crossoffset, origin.y + ystep * jdest + crossoffset),
				Vec2(origin.x + xstep * (idest + 1) - crossoffset, origin.y + ystep * (jdest + 1) - crossoffset),
				Color4F(0.5,0.5,0.5,0.5));
			draw->drawLine(Vec2(origin.x+xstep*idest+crossoffset, origin.y+ystep*(jdest+1)-crossoffset),
				Vec2(origin.x+xstep*(idest+1)-crossoffset, origin.y+ystep*jdest+crossoffset),
				Color4F(0.5,0.5,0.5,0.5));
			addChild(draw, 0, tag);
		} else {
			auto draw = DrawNode::create();
			draw->drawCircle(Vec2(origin.x+xstep*idest+xstep/2, origin.y+ystep*jdest+ystep/2), std::min(xstep, ystep) / 2 - 10.0f, 0.0f, 30, false, Color4F(0.5f,0.5f,0.5f,0.5f));
			addChild(draw, 0, tag);
		}
	}
}

void GameScene::OnModel_GameOver(const std::string &strTip)
{
	BaseLayer *ly = (BaseLayer*)BaseLayer::create();
	ly->appear();
	this->addChild(ly);
}