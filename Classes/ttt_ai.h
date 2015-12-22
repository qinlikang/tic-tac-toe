#ifndef __ttt_ai_h__
#define __ttt_ai_h__

#include "GamePlayer.h"

#define INIT_VALUE				0
#define TIC_VALUE				1		// cross 
#define TAC_VALUE				2		// circle
#define NEXT_VALUE(cur)			((cur) == 1 ? 2 : 1)

#define MAX_PLAYER_COUNT		2
// Player type, also index in player array (_players).
#define PLAYER_TYPE_TIC			0
#define PLAYER_TYPE_TAC			1
#define PLAYER_TYPE_INVALID		MAX_PLAYER_COUNT

#define GAME_RESULT_LOSS		-1
#define GAME_RESULT_DRAW		0
#define GAME_RESULT_WIN			1

#define GAME_ROW 3
#define GAME_COL 3

typedef struct tag_ttt_state
{
	// board
	int data[GAME_ROW][GAME_COL];
	int row_size;
	int col_size;
	int remain_steps;

	// players
	game_player players[MAX_PLAYER_COUNT];

	// other
	int winner_index;
	int search_player;	// index
} ttt_state;

typedef struct tag_max_min_result
{
	int eval;
	int row;
	int col;
} max_min_result;

#ifdef __cplusplus
extern "C" {
#endif

extern int evaluate(ttt_state *s);
extern int over_hit(ttt_state *s, int *winner_index);
extern void max_min_search(ttt_state *s, int value, int max_min, max_min_result *result);

#ifdef __cplusplus
}
#endif

#endif