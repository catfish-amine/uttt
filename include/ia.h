#ifndef IA_H
#define IA_H
#include "common.h"
#include "model.h"
/*!
 * This function modify the move in parameter in order to get a valid move (1) randomly if tactic is 0 or 
 * (2) in a clever way if tactic is 1 in the corresponding utictactoe u.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \param p_move a pointer on a s_move to be modified.
 * \param tactic an e_tactic set to 0 for random strategy and 1 for clever one.
 */

void best_move(s_utictactoe* p_uttt, s_move* p_move, e_tactic tactic);
void best_move_clever_i1 (s_utictactoe* p_uttt, s_move* p_move, e_player AI, e_player OTHER);
void best_move_clever (s_utictactoe* p_uttt, s_move* p_move, e_tactic tactic);
int minimax_i1(s_utictactoe* p_uttt, s_move* p_move, int depth, bool isMaximizing, e_player ai, e_player other);

#endif