#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ia.h"
/* ================================================
=================== OTHER FUNCTIONS ===============
================================================*/
int max (int m, int m2)
{
    if (m>m2) return m;
    else return m2;
}
int min (int m, int m2)
{
    if (m<m2) return m;
    else return m2;
}

int get_score ( e_player win , e_player ai_player, e_player opp_player){
    if (win == BOTH) return 0;
    else if ( win == opp_player) return -10;
    else if (win == ai_player) return 10;
    return 0;
}


/* ================================================
=================== FOR INCEPTION LEVEL 2 ===============
================================================*/



int block_three(e_player p1 ,e_player p2,  s_tictactoe *p_ttt)
{
    int res = 0 ;
    if ( (p_ttt->content[0] == p2) && (p_ttt->content[1] == p2) && (p_ttt->content[2] == p1)) res++;
    if ( (p_ttt->content[0] == p2) && (p_ttt->content[3] == p2) && (p_ttt->content[6] == p1)) res++;
    if ( (p_ttt->content[0] == p2) && (p_ttt->content[4] == p2) && (p_ttt->content[8] == p1)) res++;

    if ( (p_ttt->content[1] == p2) && (p_ttt->content[2] == p2) && (p_ttt->content[0] == p1)) res++;
    if ( (p_ttt->content[1] == p2) && (p_ttt->content[4] == p2) && (p_ttt->content[7] == p1) ) res++;

    if ( (p_ttt->content[2] == p2) && (p_ttt->content[5] == p2) && (p_ttt->content[8] == p1)) res++;
    if ( (p_ttt->content[2] == p2) && (p_ttt->content[4] == p2) && (p_ttt->content[6] == p1)) res++;
    
    if ( (p_ttt->content[3] == p2) && (p_ttt->content[4] == p2) && (p_ttt->content[5] == p1)) res++;
    if ( (p_ttt->content[3] == p2) && (p_ttt->content[6] == p2) && (p_ttt->content[0] == p1)) res++;

    if ( (p_ttt->content[4] == p2) && (p_ttt->content[5] == p2) && (p_ttt->content[3] == p1)) res++;
    if ( (p_ttt->content[4] == p2) && (p_ttt->content[7] == p2) && (p_ttt->content[1] == p1)) res++;
    if ( (p_ttt->content[4] == p2) && (p_ttt->content[8] == p2) && (p_ttt->content[0] == p1)) res++;
    if ( (p_ttt->content[4] == p2) && (p_ttt->content[6] == p2) && (p_ttt->content[2] == p1)) res++;

    if ( (p_ttt->content[5] == p2) && (p_ttt->content[8] == p2) && (p_ttt->content[2] == p1)) res++;

    if ( (p_ttt->content[6] == p2) && (p_ttt->content[7] == p2) && (p_ttt->content[8] == p1)) res++;
    if ( (p_ttt->content[7] == p2) && (p_ttt->content[8] == p2) && (p_ttt->content[6] == p1)) res++;
    return res;
}


int two_in_arrow(e_player p , s_tictactoe *p_ttt)
{
    int res = 0 ;
    if ( (p_ttt->content[0] == p) && (p_ttt->content[1] == p) ) res++;
    if ( (p_ttt->content[0] == p) && (p_ttt->content[3] == p) ) res++;
    if ( (p_ttt->content[0] == p) && (p_ttt->content[4] == p) ) res++;

    if ( (p_ttt->content[1] == p) && (p_ttt->content[2] == p) ) res++;
    if ( (p_ttt->content[1] == p) && (p_ttt->content[4] == p) ) res++;

    if ( (p_ttt->content[2] == p) && (p_ttt->content[5] == p) ) res++;
    if ( (p_ttt->content[2] == p) && (p_ttt->content[4] == p) ) res++;
    
    if ( (p_ttt->content[3] == p) && (p_ttt->content[4] == p) ) res++;
    if ( (p_ttt->content[3] == p) && (p_ttt->content[6] == p) ) res++;

    if ( (p_ttt->content[4] == p) && (p_ttt->content[5] == p) ) res++;
    if ( (p_ttt->content[4] == p) && (p_ttt->content[7] == p) ) res++;
    if ( (p_ttt->content[4] == p) && (p_ttt->content[8] == p) ) res++;
    if ( (p_ttt->content[6] == p) && (p_ttt->content[4] == p) ) res++;

    if ( (p_ttt->content[5] == p) && (p_ttt->content[8] == p) ) res++;

    if ( (p_ttt->content[6] == p) && (p_ttt->content[7] == p) ) res++;
    if ( (p_ttt->content[7] == p) && (p_ttt->content[8] == p) ) res++;
    return res;
}
int evaluate_board(s_tictactoe *p_ttt,e_player ai_player, e_player opp_player){
    int res = 0;
    int add = two_in_arrow(ai_player,p_ttt);
    int del = two_in_arrow(opp_player,p_ttt);
    res  = res + (add*30) - (del*30);

    for (int i =0; i<9; i++){
        if (i == 4 ){
            if (p_ttt->content[i] == ai_player ) res=res+10;
            if (p_ttt->content[i] == opp_player) res=res-10;
            if (p_ttt->content[i] == BOTH) res=res +2;
        }
        if ( (i == 0 )  || (i == 2 ) || (i == 6 )  || (i == 8 )){
            if (p_ttt->content[i] == ai_player ) res=res+8;
            if (p_ttt->content[i] == opp_player) res=res-8;
            if (p_ttt->content[i] == BOTH) res=res +1;
        }
        else {
            if (p_ttt->content[i] == ai_player ) res=res+5;
            if (p_ttt->content[i] == opp_player) res=res-5;
            if (p_ttt->content[i] == BOTH) res=res +1;

        }
            

    }
    add = block_three(ai_player,opp_player,p_ttt);
    del = block_three(opp_player,ai_player,p_ttt);
    res  = res + (add*10) - (del*10);
    return res;

}

int get_score_i2 ( s_utictactoe *p_uttt , e_player ai_player, e_player opp_player){
    int final_score = 0;
    if (p_uttt->outer_tictactoe->winner == BOTH) return 0;
    else if ( p_uttt->outer_tictactoe->winner  == opp_player) return -9000;
    else if (p_uttt->outer_tictactoe->winner  == ai_player) return 9000;
    int score1 = 0;
    int score2 = 0;
    for (int i =0; i<9; i++){
        score1 = score1 + evaluate_board(p_uttt->inner_tictactoes[i],ai_player,opp_player);
        

    }
    score2 = score2 + (evaluate_board(p_uttt->outer_tictactoe,ai_player,opp_player)*100);
    final_score=score1 + score2;

    return final_score;
}

int minimax_i2(s_utictactoe* p_uttt, s_move* p_move, int depth, bool isMaximizing, e_player ai_player, e_player opp_player, int alpha, int beta) 
{
  if ((p_uttt->outer_tictactoe->winner != NOBODY) || (depth == 5)) {
    return get_score_i2(p_uttt,ai_player,opp_player);
  }

  if (isMaximizing){

        int bestscore = -10000;
        p_move->outer_position= get_next_outer_position(p_uttt);
        if (p_move->outer_position!=FREE){
        for (int i = 0; i<9;i++)
        {
            p_move->player= ai_player;
            p_move->inner_position=i;
            if (is_move_valid(p_uttt,p_move))
            {
                play_move(p_uttt,p_move);
                int score = minimax_i2(p_uttt,p_move,depth+1,false,ai_player,opp_player,alpha,beta);
                undo_last_move(p_uttt);
                bestscore = max(score, bestscore);
                alpha = max(bestscore,alpha);
                if (beta <= alpha ) return bestscore;

            }

        }
    }
    else{
        for (int i = 0; i<9; i++){
            for (int j = 0 ; j<9; j++){
                p_move->outer_position=i;
                p_move->player= ai_player;
                p_move->inner_position=j;
                if (is_move_valid(p_uttt,p_move))
                {
                    play_move(p_uttt,p_move);
                    int score = minimax_i2(p_uttt,p_move,depth+1,false,ai_player,opp_player,alpha,beta);
                    undo_last_move(p_uttt);
                    bestscore = max(score, bestscore);
                    alpha = max(bestscore,alpha);
                    if (beta <= alpha ) return bestscore;

                }
            }
        }
    }
    return bestscore;
  }
  else 
  {   
      int bestscore = 10000;
        p_move->outer_position= get_next_outer_position(p_uttt);
        if (p_move->outer_position!=FREE){
        for (int i = 0; i<9;i++)
        {
            p_move->player= opp_player;
            p_move->inner_position=i;
            if (is_move_valid(p_uttt,p_move))
            {
                play_move(p_uttt,p_move);
                int score = minimax_i2(p_uttt,p_move,depth+1,true,ai_player,opp_player,alpha,beta);
                undo_last_move(p_uttt);
                bestscore = min(score, bestscore);
                beta = min(bestscore,beta);
                if (beta <= alpha ) return bestscore;                

            }

        }
    }                                                                                       
    else{
        for (int i = 0; i<9; i++){
            for (int j = 0 ; j<9; j++){
                p_move->outer_position=i;
                p_move->player= opp_player;
                p_move->inner_position=j;
                if (is_move_valid(p_uttt,p_move))
                {
                    play_move(p_uttt,p_move);
                    int score = minimax_i2(p_uttt,p_move,depth+1,true,ai_player,opp_player,alpha,beta);
                    undo_last_move(p_uttt);
                    bestscore = min(score, bestscore);
                    beta = min(bestscore,beta);
                    if (beta <= alpha ) return bestscore;

                }
            }
        }
    }
    return bestscore;
  }
    
  }
void best_move_clever_i2 (s_utictactoe* p_uttt, s_move* p_move, e_player ai_player, e_player opp_player)
{

    int clever_outer,clever_inner;
    int bestscore = -10000;
    int alpha = -10000;
    int beta = 10000;
    p_move->outer_position =get_next_outer_position(p_uttt);
    clever_outer = p_move->outer_position;
    if (p_move->outer_position!=FREE){
        for (int i = 0; i<9;i++)
        {
            p_move->player= ai_player;
            
            p_move->inner_position=i;
            if (is_move_valid(p_uttt,p_move))
            {
                play_move(p_uttt,p_move);
                int score = minimax_i2(p_uttt,p_move,0,false,ai_player,opp_player,alpha,beta);
                undo_last_move(p_uttt);
                if (score > bestscore) 
                {
                    bestscore = score;
                    clever_inner=i;
                }
                
            }
            p_move->outer_position =clever_outer;

        }
    }
    else{
        for (int i = 0; i<9; i++){
            
            for (int j = 0 ; j<9; j++){
                p_move->outer_position=i;
                p_move->player= ai_player;
                p_move->inner_position=j;
                if (is_move_valid(p_uttt,p_move))
                {
                    play_move(p_uttt,p_move);
                    int score = minimax_i2(p_uttt,p_move,0,false,ai_player,opp_player,alpha,beta);
                    undo_last_move(p_uttt);
                    if (score > bestscore) 
                    {
                        bestscore = score;
                        clever_outer=i;
                        clever_inner=j;
                    }
                }
            }
        }
    }
    p_move->player= ai_player;
    p_move->outer_position=clever_outer;
    p_move->inner_position=clever_inner;


}



/* ================================================
=================== FOR INCEPTION LEVEL 1 ===============
================================================*/
void best_move_clever_i1 (s_utictactoe* p_uttt, s_move* p_move, e_player ai_player, e_player opp_player)
{
    int clever_move;

    int bestscore = -100;
    for (int i = 0; i<9;i++)
    {
        p_move->outer_position=i;
        p_move->player= ai_player;
        if (is_move_valid(p_uttt,p_move))
        {
            play_move(p_uttt,p_move);
            int score = minimax_i1(p_uttt,p_move,0,false,ai_player,opp_player);
            undo_last_move(p_uttt);
            if (score > bestscore) 
            {
                bestscore = score;
                clever_move=i;
            }
        }
    }
    p_move->player= ai_player;
    p_move->outer_position=clever_move;


}


int minimax_i1(s_utictactoe* p_uttt, s_move* s_move, int depth, bool isMaximizing, e_player ai_player, e_player opp_player) 
{
  if (p_uttt->outer_tictactoe->winner != NOBODY) {
    return get_score(p_uttt->outer_tictactoe->winner,ai_player,opp_player);
  }

  if (isMaximizing) {
    int bestscore = -100;
    for (int i = 0; i < 9; i++) {
        s_move->player=ai_player;
        s_move->outer_position = i;
        if (is_move_valid(p_uttt,s_move)) {
          play_move(p_uttt,s_move);
          int score = minimax_i1(p_uttt,s_move, depth + 1, false,ai_player,opp_player);
           undo_last_move(p_uttt);
          bestscore = max(score, bestscore);
        }
    }
    return bestscore;
  } 
  else 
  {
    int bestscore =100;
    for (int i = 0; i < 9; i++) {
           s_move->player=opp_player;
           s_move->outer_position = i;
       if (is_move_valid(p_uttt,s_move)) {
           play_move(p_uttt,s_move);
           int score = minimax_i1(p_uttt,s_move, depth + 1, true,ai_player,opp_player);
           undo_last_move(p_uttt);
          bestscore = min(score, bestscore);
        }
    }
    return bestscore;
  }
}



/* ================================================
=================== MAIN FUNCTIONS ===============
================================================*/
void best_move_clever (s_utictactoe* p_uttt, s_move* p_move, e_tactic tactic){
    e_player ai_player,opp_player;
    if (p_move->player == PLAYER_O) {
        ai_player = PLAYER_O;
        opp_player = PLAYER_X;
    }
    else {
        ai_player = PLAYER_X;
        opp_player = PLAYER_O;
    }
    if (p_uttt->inception_level == 1) best_move_clever_i1(p_uttt,p_move,ai_player,opp_player);
    else best_move_clever_i2(p_uttt,p_move,ai_player,opp_player);

}

void best_move_random(s_utictactoe* p_uttt, s_move* p_move, e_tactic tactic){
    if (p_uttt->inception_level == 1) {
        int available[9];
        int x = 0;
        for (int i = 0 ; i<9 ; i++)
        if (p_uttt->outer_tictactoe->content[i] == NOBODY) {
            available[x] = i;
            x++;
        }
        int r = rand()%x;
        p_move->outer_position = available[r];
    }
    if (p_uttt->inception_level == 2) {
        int inner,outer;
        //gurantee a first valid move
        for (int i = 0 ; i<9 ; i++){
            p_move->outer_position = i;
            for (int j =0 ; j< 9 ; j ++){
                p_move->inner_position =j;
                if (is_move_valid(p_uttt,p_move) == YES) {
                    outer = i;
                    inner =j;
                    break;
                }
            }

        }
        //try to randomize it if possible

        for (int i = 0 ; i < 20 ; i++){
            int r1 = rand()%9;
            int r2  = rand()%9;
            p_move->outer_position = r1;
            p_move->inner_position = r2;
            if (is_move_valid(p_uttt,p_move) == YES) return;
        }
        
        p_move->outer_position = outer;
        p_move->inner_position = inner;
    }
    
}



void best_move(s_utictactoe* p_uttt, s_move* p_move, e_tactic tactic){
    if (tactic == RANDOM)  best_move_random(p_uttt,p_move,tactic);
    else if (tactic == CLEVER) best_move_clever(p_uttt,p_move,tactic);

}


