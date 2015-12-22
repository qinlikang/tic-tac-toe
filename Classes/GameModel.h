#ifndef __GameModel_H__
#define __GameModel_H__

#include "ttt_ai.h"

class GameScene;
class GameModel
{
public:
	GameModel(GameScene	*scene);
	virtual ~GameModel();

public:
	void Do(int row, int col);
	void DoRobotAction();
	int GetMyChessman() { return _state.players[0].chessman; }

protected:
	ttt_state		_state;
	GameScene		*_scene;
};

#endif