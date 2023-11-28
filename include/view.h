#ifndef VIEW_H
#define VIEW_H
#include <ncurses.h>
#include "common.h"
#include "model.h"

typedef struct view * p_view; 

/*!
 * This function allocates dynamically a struct view in order to handle the corresponding u_tictactoe.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \return a reference to the s_utictactoe memory space allocated, NULL in case
 * of allocation problem.
 */
p_view  create_view(s_utictactoe * p_uttt);

/*!
 * This function retrieves a valid move proposal from the user using the corresponding view.
 *
 * \param p_move a pointer on a s_move to be modified.
 * \param v a pointer on the view to use.
 */
void set_next_player_move(s_move * p_move, p_view v, e_tactic t);

/*!
 * This function free all the memory used by a given view which
 * reference is given.
 *
 * \param v a pointer on a view to be freed.
 */
void free_view(p_view v);
/*!
 * This function display the winner of a corresponding view.
 *
 * \param v a pointer on a view to be freed.
 */
void display_winner(p_view v);

#endif /* VIEW_H */