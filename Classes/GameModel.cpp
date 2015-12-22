#include "StdAfx.h"
#include "GameModel.h"
#include "GameScene.h"

GameModel::GameModel(GameScene *scene)
{
	// Init state.
	memset(&_state, 0, sizeof(ttt_state));
	_state.row_size = GAME_ROW;
	_state.col_size = GAME_COL;
	_state.players[0].chessman = TIC_VALUE;
	_state.players[1].chessman = TAC_VALUE;
	_state.remain_steps = GAME_ROW * GAME_COL;
	for (int i = 0; i < _state.row_size; ++i) {
		for (int j = 0; j < _state.col_size; ++j) {
			_state.data[i][j] = INIT_VALUE;
		}
	}

	// ui callback.
	_scene = scene;
}

GameModel::~GameModel()
{
	
}

void GameModel::DoRobotAction()
{
	_state.search_player = 1;
	max_min_result result;
	result.row = result.col = -1;
	max_min_search(&_state, _state.players[1].chessman, 1, &result);
	assert(result.row != -1);
	_state.data[result.row][result.col] = _state.players[1].chessman;
	_state.remain_steps--;

	_scene->DrawChessman(_state.players[1].chessman, result.row, result.col);

	int winner_index = -1;
	if (over_hit(&_state, &winner_index)) {
		if (winner_index == -1) {
			//_scene->PopupWindow("GameOver! Drawn");
			_scene->OnModel_GameOver("GameOver! Drawn");
		} else {
			//_scene->PopupWindow("GameOver! Winner is %d", winner_type);
			_scene->OnModel_GameOver("GameOver! Winner is");
		}
	}
}

void GameModel::Do(int row, int col)
{
	_state.data[row][col] = _state.players[0].chessman;
	_state.remain_steps--;
	int winner_index = -1;
	if (!over_hit(&_state, &winner_index)) {
		DoRobotAction();
	} else {
		if (winner_index == -1) {
			//_scene->PopupWindow("GameOver! Drawn");
			_scene->OnModel_GameOver("GameOver! Drawn");
		} else {
			//_scene->PopupWindow("GameOver! Winner is %d", winner_type);
			_scene->OnModel_GameOver("GameOver! Winner is");
		}
	}
}