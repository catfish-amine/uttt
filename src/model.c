#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/model.h"

    s_move *create_empty_move(){
        s_move *empty_move = (s_move*) malloc( sizeof( s_move));
	    if (empty_move==NULL){
		    fprintf(stderr,"Error! 1");
		    exit(EXIT_FAILURE);
	    }
        empty_move->outer_position=FREE;
        empty_move->inner_position=FREE;
        empty_move->player=NOBODY;
        return empty_move;
    }

    s_tictactoe *create_empty_tictactoe(){
        s_tictactoe *empty_tictactoe = (s_tictactoe*) malloc( sizeof(s_tictactoe));
	    if (empty_tictactoe ==NULL){
		    fprintf(stderr,"Error! 2");
		    exit(EXIT_FAILURE);
	    }
        empty_tictactoe->winner=NOBODY;
        empty_tictactoe->content = (e_player*) malloc( sizeof(e_player)* TICTACTOE_SIZE);
        if (empty_tictactoe->content ==NULL){
		    fprintf(stderr,"Error! 3");
		    exit(EXIT_FAILURE);
	    }
        for (int i=0 ; i<TICTACTOE_SIZE; i++)
	    {
		    empty_tictactoe->content[i]=NOBODY;

	    }
        return empty_tictactoe;

    }

    s_utictactoe *create_empty_utictactoe(uint inception_level) {
        if (inception_level > 3 || inception_level < 1){
            fprintf(stderr,"Error! 4");
		    exit(EXIT_FAILURE);
        }
        s_utictactoe *empty_utictactoe = (s_utictactoe*) malloc( sizeof(s_utictactoe));
	    if (empty_utictactoe ==NULL){
		    fprintf(stderr,"Error! 5");
		    exit(EXIT_FAILURE);
	    }
        empty_utictactoe->history =NULL;

        empty_utictactoe->outer_tictactoe = create_empty_tictactoe();
        empty_utictactoe->inception_level=inception_level;
         if (inception_level == 1 ){
            empty_utictactoe->inner_tictactoes=NULL;
        }
        else if (inception_level == 2 ){
            empty_utictactoe->inner_tictactoes = (s_tictactoe**) malloc( TICTACTOE_SIZE*sizeof(s_tictactoe*));
            for (int i=0 ; i<TICTACTOE_SIZE; i++)
	        {
		        empty_utictactoe->inner_tictactoes[i]=create_empty_tictactoe();
	        }
        }
        return empty_utictactoe;
        
    }
    
    void free_move(s_move *p_move){
        assert(p_move);
        if (p_move != NULL) free(p_move);
    }

    void free_tictactoe(s_tictactoe *p_ttt){
        assert(p_ttt);
        if (p_ttt->content != NULL) free(p_ttt->content);
	    if(p_ttt != NULL) free(p_ttt);

    }
    
    void free_utictactoe(s_utictactoe *p_uttt){
        assert(p_uttt);
        if (p_uttt ==NULL){
		    fprintf(stderr,"Error! 7");
		    exit(EXIT_FAILURE);
	    }
        list_element_s_move *tmp;
        while (p_uttt->history != NULL)  {
            if (p_uttt->history->last_move!=NULL) free_move(p_uttt->history->last_move);
            tmp = p_uttt->history;
            p_uttt->history=p_uttt->history->next;
            free(tmp);
        }
        
        if (p_uttt->outer_tictactoe != NULL)  free_tictactoe(p_uttt->outer_tictactoe);
        if (p_uttt->inception_level==2){
            for (int i=0 ; i<TICTACTOE_SIZE; i++)
	        {
		        if (p_uttt->inner_tictactoes[i] != NULL) free_tictactoe(p_uttt->inner_tictactoes[i]);

	        }
        }
        if(p_uttt->inner_tictactoes != NULL) free(p_uttt->inner_tictactoes);
	    if(p_uttt != NULL) free(p_uttt);

    }

    e_player get_next_player_to_play(s_utictactoe *p_uttt){
        assert(p_uttt);
        if (p_uttt ==NULL){
		    fprintf(stderr,"Error! 8");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->outer_tictactoe ==NULL){
		    fprintf(stderr,"Error! 9");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->outer_tictactoe->winner != NOBODY) return NOBODY;
        if (p_uttt->history ==NULL)return PLAYER_X;
        if (p_uttt->history->last_move == NULL) {
		    fprintf(stderr,"Error! 10");
		    exit(EXIT_FAILURE);
	    }
        else if (p_uttt->history->last_move->player == PLAYER_O) return PLAYER_X;
        else if (p_uttt->history->last_move->player == PLAYER_X) return PLAYER_O;
        return 0;
    }

    e_location get_next_outer_position(s_utictactoe *p_uttt){
        assert(p_uttt);
        if (p_uttt ==NULL){
		    fprintf(stderr,"Error! 11");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->inception_level == 1) return FREE;
        else if (p_uttt->inception_level == 2){

            if (p_uttt->history ==NULL)return FREE;
            if (p_uttt->history->last_move==NULL)
            {
		        fprintf(stderr,"Error! 12");
		        exit(EXIT_FAILURE);
	        }
            e_location x = p_uttt->history->last_move->inner_position;
            if (p_uttt->inner_tictactoes[x]->winner==NOBODY) return x;
            else return FREE;
        }
        return 0;
        
    }

    e_status is_move_valid_i2(s_utictactoe *p_uttt, s_move *p_move){

        if (p_uttt->inner_tictactoes == NULL){
		    fprintf(stderr,"Error! 14");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->inner_tictactoes[p_move->outer_position]->content[p_move->inner_position]!=NOBODY)  return NO; //occupied spot
        else if (p_uttt->outer_tictactoe->winner!=NOBODY) return NO; //uttt game won already
        else if (p_uttt->inner_tictactoes[p_move->outer_position]->winner!=NOBODY) return NO;//ttt game won already
        
        if (p_uttt->history==NULL){
    
            if (p_move->player!=PLAYER_X) return NO; //player X should always start the game
            else return YES;
        }

        else {
            if (p_uttt->history->last_move==NULL)
            {
		        fprintf(stderr,"Error! 15");
		        exit(EXIT_FAILURE);
	        }
            if (p_uttt->history->last_move->player == p_move->player) return NO;  // same player can't play again
            else if ( (p_uttt->inner_tictactoes[p_uttt->history->last_move->inner_position]->winner==NOBODY) && (p_move->outer_position != p_uttt->history->last_move->inner_position) )  return NO; //Play in the outer side if the game not won
            else return YES;
        }

    }

    e_status is_move_valid_i1(s_utictactoe *p_uttt, s_move *p_move){

        if (p_uttt->outer_tictactoe->content[p_move->outer_position]!=NOBODY)  return NO; //occupied spot
        else if (p_uttt->outer_tictactoe->winner!=NOBODY) return NO; //uttt game won already        

        if (p_uttt->history==NULL){
            
            if (p_move->player!=PLAYER_X) return NO;//player X should always start the game
            else return YES;
        } 
        else {
            if (p_uttt->history->last_move==NULL)
            {
		        fprintf(stderr,"Error! 16");
		        exit(EXIT_FAILURE);
	        }
            else if (p_uttt->history->last_move->player == p_move->player) return NO;  // same player can't play again       
            else return YES;        

        }
    }


    e_status is_move_valid(s_utictactoe *p_uttt, s_move *p_move){
        if ((p_uttt ==NULL) || (p_move==NULL)){
		    fprintf(stderr,"Error! 13");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->inception_level == 2) return is_move_valid_i2(p_uttt,p_move);
        if (p_uttt->inception_level == 1) return is_move_valid_i1(p_uttt,p_move);
        return 0;
        
    }
    
    void set_tictactoe_winner(s_tictactoe *p_ttt){
        if (p_ttt ==NULL){
		    fprintf(stderr,"Error! 17");
		    exit(EXIT_FAILURE);
	    }
        assert(p_ttt);
        if ((p_ttt->content[0] == p_ttt->content[1]) && (p_ttt->content[1] == p_ttt->content[2]) && (p_ttt->content[2] != NOBODY)){
            p_ttt->winner=p_ttt->content[0];
            return; 
        }
        else if ((p_ttt->content[3] == p_ttt->content[4]) && (p_ttt->content[4] == p_ttt->content[5]) && (p_ttt->content[5] != NOBODY)){
            p_ttt->winner=p_ttt->content[3];
            return;  
        }
        else if ((p_ttt->content[6] == p_ttt->content[7]) && (p_ttt->content[7] == p_ttt->content[8]) && (p_ttt->content[8] != NOBODY)){
            p_ttt->winner=p_ttt->content[8];
            return; 
        }
        else if ((p_ttt->content[0] == p_ttt->content[3]) && (p_ttt->content[3] == p_ttt->content[6]) && (p_ttt->content[6] != NOBODY)){
            p_ttt->winner=p_ttt->content[6];
            return; 
        }
        else if ((p_ttt->content[1] == p_ttt->content[4]) && (p_ttt->content[4] == p_ttt->content[7]) && (p_ttt->content[7] != NOBODY)){
            p_ttt->winner=p_ttt->content[7];
            return;  
        }
        else if ((p_ttt->content[2] == p_ttt->content[5]) && (p_ttt->content[5] == p_ttt->content[8]) && (p_ttt->content[8] != NOBODY)){
            p_ttt->winner=p_ttt->content[8];
            return;  
        }
        else if ((p_ttt->content[0] == p_ttt->content[4]) && (p_ttt->content[4] == p_ttt->content[8]) && (p_ttt->content[8] != NOBODY)){
            p_ttt->winner=p_ttt->content[8];
            return;  
        }
        else if ((p_ttt->content[2] == p_ttt->content[4]) && (p_ttt->content[4] == p_ttt->content[6]) && (p_ttt->content[6] != NOBODY)){
            p_ttt->winner=p_ttt->content[6];
            return;  
        }
        else {  
                int j =0;
                for (int i = 0; i<TICTACTOE_SIZE ; i++){
                    if (p_ttt->content[i]!= NOBODY) j++;
                }
                if (j == TICTACTOE_SIZE) {
                    p_ttt->winner=BOTH;
                    return;
                }
             }
    }

    e_status play_move(s_utictactoe *p_uttt, s_move *p_move){
        if ((p_uttt ==NULL) || (p_move==NULL)){
		    fprintf(stderr,"Error! 18");
		    exit(EXIT_FAILURE);
	    }
        if (p_uttt->outer_tictactoe== NULL){
		    fprintf(stderr,"Error! 19");
		    exit(EXIT_FAILURE);
	     }
        assert(p_uttt);
        e_status x = is_move_valid(p_uttt,p_move);
        if (x == NO) return NO;
        if (p_uttt->inception_level==2){
            if (p_uttt->inner_tictactoes ==NULL){
		        fprintf(stderr,"Error! 20");
		        exit(EXIT_FAILURE);
	        }
            p_uttt->inner_tictactoes[p_move->outer_position]->content[p_move->inner_position]= p_move->player;
            set_tictactoe_winner(p_uttt->inner_tictactoes[p_move->outer_position]);
            p_uttt->outer_tictactoe->content[p_move->outer_position]=p_uttt->inner_tictactoes[p_move->outer_position]->winner;
            set_tictactoe_winner(p_uttt->outer_tictactoe);
        }
        else if (p_uttt->inception_level==1){
            p_uttt->outer_tictactoe->content[p_move->outer_position]= p_move->player;
            set_tictactoe_winner(p_uttt->outer_tictactoe);
        }
        
        list_element_s_move *new_element;
        new_element = (list_element_s_move *) malloc(sizeof(list_element_s_move ));
        if (new_element==NULL){
		    fprintf(stderr,"Error! 21");
		    exit(EXIT_FAILURE);
	    }
        s_move* tmp = create_empty_move();
        *tmp = *p_move;
        new_element->last_move= tmp;
        new_element->next= p_uttt->history;
        p_uttt->history = new_element;
        return YES;
    }

    void draw_ith_line_of_ttt(s_tictactoe *p_ttt, uint line) {
    assert(p_ttt);
    printf("%c%c%c", p_ttt->content[line * TICTACTOE_WIDTH],
            p_ttt->content[line * TICTACTOE_WIDTH + 1],
            p_ttt->content[line * TICTACTOE_WIDTH + 2]);
    }

    void draw_tictactoe(s_tictactoe *p_ttt) {
    assert(p_ttt);
    for (uint line = 0; line < TICTACTOE_WIDTH; line++) {
        draw_ith_line_of_ttt(p_ttt, line);
        printf("\n");
    }
    }

    void draw_utictactoe_history(s_utictactoe *p_uttt) {
    assert(p_uttt);
    char *e_location_name[] = {"TL", "TC", "TR", "ML",   "MC",  "MR",
                                 "BL", "BC", "BR", "FREE", "NONE"};
    list_element_s_move *tmp = p_uttt->history;
    while (tmp != NULL) {
        if (tmp->last_move) {
            printf(" - %s %s %c \n", e_location_name[tmp->last_move->inner_position],
             e_location_name[tmp->last_move->outer_position],
             tmp->last_move->player);
        }
        tmp = tmp->next;
    }
    }

    void draw_utictactoe(s_utictactoe *p_uttt) {
    assert(p_uttt);
    if (p_uttt->inception_level == 1) {
        draw_tictactoe(p_uttt->outer_tictactoe);
    } else {
        for (uint id_ttt = 0; id_ttt < TICTACTOE_SIZE;
            id_ttt = id_ttt + TICTACTOE_WIDTH) {
        for (uint line = 0; line < TICTACTOE_WIDTH; line++) {
            draw_ith_line_of_ttt(p_uttt->inner_tictactoes[id_ttt], line);
            printf("|");
            draw_ith_line_of_ttt(p_uttt->inner_tictactoes[id_ttt + 1], line);
            printf("|");
            draw_ith_line_of_ttt(p_uttt->inner_tictactoes[id_ttt + 2], line);
            printf("\n");
        }
        if (id_ttt + TICTACTOE_WIDTH < TICTACTOE_SIZE) {
            printf("-----------");
            printf("\n");
        }
        }
    }
    printf("\n####\n");
    }
    
    void save_a_utictactoe_to_file(FILE *p_f, s_utictactoe *p_uttt){
        assert(p_uttt);
        if ((p_uttt ==NULL) || (p_f==NULL)){
		    fprintf(stderr,"Error! 22");
		    exit(EXIT_FAILURE);
        }
	
        fprintf(p_f,"%d\n",p_uttt->inception_level);
        char *e_location_name[] = {"TL", "TC", "TR", "ML",   "MC",  "MR",
                                 "BL", "BC", "BR", "FREE", "NONE"};
        list_element_s_move *tmp = p_uttt->history;
        while (tmp != NULL) {
            if (tmp->last_move) {
                fprintf(p_f,"%s %s %c\n", e_location_name[tmp->last_move->inner_position],
                e_location_name[tmp->last_move->outer_position],
                tmp->last_move->player);
            }
            tmp = tmp->next;
        }
        

    }   
e_status undo_last_move(s_utictactoe *p_uttt){
  assert(p_uttt);
  if (p_uttt->inception_level == 1){
      if(p_uttt->history == NULL) return NO;
    e_location last = p_uttt->history->last_move->outer_position;
    p_uttt->outer_tictactoe->content[last] = NOBODY;
    list_element_s_move *tmp;
    tmp = p_uttt->history;
    p_uttt->history = p_uttt->history->next;
    free(tmp);
    p_uttt->outer_tictactoe->winner=NOBODY;
    return YES;
  }
    else if (p_uttt->inception_level == 2){
      if(p_uttt->history == NULL) return NO;
    e_location last_outer = p_uttt->history->last_move->outer_position;
    e_location last_inner = p_uttt->history->last_move->inner_position;
    p_uttt->inner_tictactoes[last_outer]->content[last_inner] = NOBODY;
    p_uttt->inner_tictactoes[last_outer]->winner = NOBODY;
    p_uttt->outer_tictactoe->content[last_outer]= NOBODY;
    list_element_s_move *tmp;
    tmp = p_uttt->history;
    p_uttt->history = p_uttt->history->next;
    free(tmp);
    p_uttt->outer_tictactoe->winner=NOBODY;
    return YES;
  }
  return NO;
  
}
    