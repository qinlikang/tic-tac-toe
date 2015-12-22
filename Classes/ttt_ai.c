#include "StdAfx.h"
#include "ttt_ai.h"

#ifdef __cplusplus
extern "C" {
#endif

int evaluate(ttt_state *s)
{
	// row
	int result;
	int i, j;
	for (i = 0; i < s->row_size; ++i) {
		result = s->data[i][0];
		for (j = 0; j < s->col_size; ++j) {
			result &= s->data[i][j];
		}
		if (result != 0) break;
	}

	// col
	if (result == 0) {
		for (j = 0; j < s->col_size; ++j) {
			result = s->data[0][j];
			for (i = 0; i < s->row_size; ++i) {
				result &= s->data[i][j];
			}
			if (result != 0) break;
		}
	}

	// cross '\'
	if (result == 0) {
		result = s->data[0][0];
		i = 1;
		j = 1;
		for (; i < s->row_size && j < s->col_size; ++i, ++j) {
			result &= s->data[i][j];
		}
	}

	// cross '/'
	if (result == 0) {
		result = s->data[0][s->col_size-1];
		i = 1;
		j = s->col_size - 2;
		for (; i < s->row_size && j >= 0; ++i, --j) {
			result &= s->data[i][j];
		}
	}
	return result;
}

int over_hit(ttt_state *s, int *winner_index)
{
	int rt = 0;
	int i;
	if (s->remain_steps == 0) {
		rt = 1;
	} else {
		int eval = evaluate(s);
		if (eval != 0) {
			for (i = 0; i < MAX_PLAYER_COUNT; ++i) {
				if (eval == s->players[i].chessman) {
					*winner_index = i;
					rt = 1;
					break;
				}
			}
		}
	}
	return rt;
}

void max_min_search(ttt_state *s, int value, int max_min, max_min_result *result)
{
	int i, j;
	result->eval = (max_min == 1 ? GAME_RESULT_LOSS : GAME_RESULT_WIN);
	for (i = 0; i < s->row_size; ++i) {
		for (j = 0; j < s->col_size; ++j) {
			if (s->data[i][j] == INIT_VALUE) {

				int old_value = s->data[i][j];
				int winner_index = -1;
				s->data[i][j] = value;
				--s->remain_steps;

				if (over_hit(s, &winner_index)) {
					if (winner_index != -1) {
						if (winner_index == s->search_player) {
							result->eval = GAME_RESULT_WIN;
						} else {
							result->eval = GAME_RESULT_LOSS;
						}
					} else {
						result->eval = GAME_RESULT_DRAW;
					}
					result->row = i;
					result->col = j;
				} else {
					max_min_result next_result;
					max_min_search(s, NEXT_VALUE(value), max_min^1, &next_result);
					if (max_min == 1) {
						if (result->eval < next_result.eval) {
							result->eval = next_result.eval;
							result->row = i;
							result->col = j;
						}
					} else if (max_min == 0) {
						if (result->eval > next_result.eval) {
							result->eval = next_result.eval;
							result->row = i;
							result->col = j;
						}
					}
				}

				s->data[i][j] = old_value;
				++s->remain_steps;
			}
		}
	}
}

#ifdef __cplusplus
}
#endif