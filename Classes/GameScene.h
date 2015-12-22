#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "GameModel.h"
#include "BaseLayer.h"

class GameScene : public cocos2d::Layer
{
public:
	virtual ~GameScene();
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	bool onMyTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onMyTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void DrawBoard();
	void DrawChessman(int chessman, int row, int col);

	void OnModel_GameOver(const std::string &strTip);

private:
	GameModel	*_gameMode;
};

#endif