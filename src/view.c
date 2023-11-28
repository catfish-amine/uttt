#include "../include/common.h"
#include "../include/model.h"
#include "../include/view.h"
#include "../include/ia.h"
#include <ncurses.h>
#include <unistd.h>

struct view{
    s_utictactoe * p_uttt;
    WINDOW* w_uttt;
    WINDOW* w_ttt;
};

int get_x (int k){
switch (k){
    case 0:
            return 2;
    case 1:
            return 4;
    case 2:
            return 6;

    case 3:
            return 2;
    case 4:
            return 4;
    case 5:
            return 6;
    case 6:
            return 2;
    case 7:
            return 4;
    case 8:
            return 6;
    default: 
            return -1;

}

}
int get_y(int k){
    switch (k){
    case 0:
            return 3;
    case 1:
            return 3;
    case 2:
            return 3;

    case 3:
            return 5;
    case 4:
            return 5;
    case 5:
            return 5;
    case 6:
            return 7;
    case 7:
            return 7;
    case 8:
            return 7;
    default: 
            return -1;

}

}
p_view create_view_i2(s_utictactoe * u){
    initscr();
    raw();
    noecho();
    p_view empty_view = (p_view) malloc( sizeof( struct view));
	if (empty_view==NULL){
		fprintf(stderr,"Error! 1");
		exit(EXIT_FAILURE);
	}
    
    empty_view->p_uttt = u;
    mvwprintw(stdscr,2,0,"Inception level %d\n", u->inception_level);
    
    e_player xo = get_next_player_to_play(empty_view->p_uttt);
    e_player xo2;
    mvwprintw(stdscr,3,0,"Player to play: %c\n", xo);
    empty_view->w_ttt = subwin(stdscr, 11, 9, 5, 1); 
    empty_view->w_uttt = subwin(stdscr, 11, 9, 5, 15); 
    box(empty_view->w_ttt,0,0);
    box(empty_view->w_uttt,0,0);
    int y = 3;
    int x = 2;
    int t = 0;
    for (int i = 0 ; i<5 ; i++){
        if ( (i==1)||( i== 3) ) {
            y=y+1;
            x=2;
            mvwprintw(empty_view->w_ttt,y,x,"-----");
            mvwprintw(empty_view->w_uttt,y,x,"-----");
            y=y+1;
            
            }
        else {
            for (int j = 0 ; j<5; j++){
                if ( (j==1)||( j== 3) ) {
                mvwprintw(empty_view->w_ttt,y,x,"|");
                mvwprintw(empty_view->w_uttt,y,x,"|");
                x=x+1;
                }
                else {
                    xo2 = u->outer_tictactoe->content[t];
                    if ( xo2 == NOBODY) {
                        mvwprintw(empty_view->w_ttt,y,x,".");
                        mvwprintw(empty_view->w_uttt,y,x,".");
                    }
                    else if ( xo2 == PLAYER_O) mvwprintw(empty_view->w_ttt,y,x,"O");
                    else if ( xo2 == PLAYER_X) mvwprintw(empty_view->w_ttt,y,x,"X");
                    else if ( xo2 == BOTH) mvwprintw(empty_view->w_ttt,y,x,"#");
                    t++;
                    x=x+1;
                }
            }
        }
    }
    
    wrefresh(empty_view->w_ttt );
    wrefresh(empty_view->w_uttt );
    wrefresh(stdscr);
    return empty_view;
}

p_view create_view_i1(s_utictactoe * u)
{
    initscr();
    raw();
    noecho();
    p_view empty_view = (p_view) malloc( sizeof( struct view));
	if (empty_view==NULL){
		fprintf(stderr,"Error! 1");
		exit(EXIT_FAILURE);
	}
    empty_view->p_uttt = u;
    empty_view->w_uttt = NULL; 
    mvwprintw(stdscr,2,0,"Inception level %d\n", u->inception_level);
    e_player xo = get_next_player_to_play(empty_view->p_uttt);
    mvwprintw(stdscr,3,0,"Player to play: %c\n", xo);
    empty_view->w_ttt = subwin(stdscr, 11, 9, 5, 1); 
    box(empty_view->w_ttt,0,0);
    int y = 3;
    int x = 2;
    int t = 0;
    for (int i = 0 ; i<5 ; i++){
        if ( (i==1)||( i== 3) ) {
            y=y+1;
            x=2;
            mvwprintw(empty_view->w_ttt,y,x,"-----");
            y=y+1;
            
            }
        else {
            for (int j = 0 ; j<5; j++){
                if ( (j==1)||( j== 3) ) {
                mvwprintw(empty_view->w_ttt,y,x,"|");
                x=x+1;
                }
                else {
                    if (u->outer_tictactoe->content[t] == NOBODY) {
                        mvwprintw(empty_view->w_ttt,y,x,".");
                        t++;
                        x=x+1;
                    }
                }
            }
        }
    }
    wrefresh(empty_view->w_ttt );
    wrefresh(stdscr);      
    return empty_view;
}
p_view create_view(s_utictactoe * u){
    if (u->inception_level == 1) return create_view_i1(u);
    else if (u->inception_level == 2) return create_view_i2(u);
    return 0;
}

int get_outer( int x, int y){
    switch(x)
    {
        case 2:
                if (y == 3) return 0;
                if (y == 5) return 3;
                if (y == 7) return 6;
        case 4:
                if (y == 3) return 1;
                if (y == 5) return 4;
                if (y == 7) return 7;
        case 6: 
                if (y == 3) return 2;
                if (y == 5) return 5;
                if (y == 7) return 8;
    }
    return 0;
}
void set_next_player_move_i1(s_move * m,p_view v, e_tactic tactic)
{
    keypad(v->w_ttt, TRUE);
    wrefresh(v->w_ttt);
    int ch=-1;
    int pos_x=2;
    int pos_y=3;
    e_player xo = get_next_player_to_play(v->p_uttt);
    mvwaddch(stdscr,3,16, xo);
    wrefresh(stdscr); 
    if ( (tactic == RANDOM) || (tactic == CLEVER) ) {
        best_move(v->p_uttt,m,tactic);
        pos_y = get_y(m->outer_position);
        pos_x = get_x(m->outer_position);
        mvwaddch(v->w_ttt,pos_y,pos_x, xo);
        wrefresh(v->w_ttt); 
        ch =' ';
    }
    while(ch!=' ')
    {
        wmove(v->w_ttt, pos_y, pos_x);
        wrefresh(v->w_ttt); 
        ch = wgetch(v->w_ttt);
        switch(ch)
	    {	
            case KEY_RIGHT: 
                if(pos_x+2<=6){
                    pos_x=pos_x+2;
                }
                break;
            case KEY_LEFT: 
                if(pos_x-2>=2){
                    pos_x=pos_x-2;
                }
                break;
            case KEY_UP: 
                    if(pos_y-2>=3){
                        pos_y=pos_y-2;
                    }
                break;
            case KEY_DOWN: 
                    if(pos_y+2<=7){
                        pos_y=pos_y+2;
                    }
                break;
            case 10 : 
                    m->outer_position = get_outer(pos_x,pos_y);
                    m->player= xo;
                    if (is_move_valid(v->p_uttt,m) == YES){
                        mvwaddch(v->w_ttt,pos_y,pos_x, xo);
                        wrefresh(v->w_ttt); 
                        ch =' ';
                    }

                    break;
            case 'q':   
                        mvwprintw(v->w_ttt,4,0,"YOU QUIT THE GAME !");
                        wrefresh(v->w_ttt); 
                        m->outer_position=NONE;
                        return;

	    }
        
    }
    
    
}

void set_next_player_move_i2(s_move * m,p_view v, e_tactic tactic)

{
    keypad(v->w_ttt, TRUE);
    int x_inner,y_inner;
    


    e_player xo2;
    for (int k = 0 ; k< 9 ; k++){
                            xo2 = v->p_uttt->outer_tictactoe->content[k];
                            x_inner = get_x(k);
                            y_inner = get_y(k);
                            if ( xo2 == NOBODY) mvwprintw(v->w_ttt,y_inner,x_inner,".");
                            else if ( xo2 == PLAYER_O) mvwprintw(v->w_ttt,y_inner,x_inner,"O");
                            else if ( xo2 == PLAYER_X) mvwprintw(v->w_ttt,y_inner,x_inner,"X");
                            else if ( xo2 == BOTH) mvwprintw(v->w_ttt,y_inner,x_inner,"#");
    }
    wrefresh(v->w_ttt);
    int  outer_p =  get_next_outer_position(v->p_uttt);
    if (outer_p != 9){
        start_color();
        init_pair(1, COLOR_BLACK,COLOR_WHITE);
        init_pair(2, COLOR_BLACK,COLOR_RED);;
        x_inner = get_x(outer_p);
        y_inner = get_y(outer_p);
        wattron(v->w_ttt, COLOR_PAIR(2));
        mvwaddch(v->w_ttt,y_inner,x_inner, '.');
        wattroff(v->w_ttt, COLOR_PAIR(2));
        wrefresh(v->w_ttt);  
    }
    wrefresh(v->w_ttt); 
    int ch=-1;
    int ch3 = -1;
    e_player xo = get_next_player_to_play(v->p_uttt);

    mvwaddch(stdscr,3,16, xo);
    wrefresh(stdscr);
    if ( (tactic == RANDOM) || (tactic == CLEVER) ) {
        best_move(v->p_uttt,m,tactic);
        int pos_y = get_y(m->outer_position);
        int pos_x = get_x(m->outer_position);
        wmove(v->w_ttt,pos_y,pos_x);
        y_inner = get_y(m->inner_position);
        x_inner = get_x(m->inner_position);
        mvwaddch(v->w_uttt,y_inner,x_inner,m->player);
        wrefresh(v->w_uttt); 
        wrefresh(v->w_ttt); 
        ch3 =' ';
    }
    while (ch3!=' '){

    int pos_x;
    int pos_y;
    if (v->p_uttt->history!=NULL){
        pos_x = get_x(v->p_uttt->history->last_move->outer_position);
        pos_y = get_y(v->p_uttt->history->last_move->outer_position);
    }
    else { pos_y = 3; pos_x = 2;}
    int outer = -1;
    int outer_pos = -1;
    wrefresh(v->w_ttt); 
    while(ch!=' ')
    {   
        outer = get_outer(pos_x,pos_y);
        for (int k = 0 ; k< 9 ; k++){
                            xo2 = v->p_uttt->inner_tictactoes[outer]->content[k];
                            x_inner = get_x(k);
                            y_inner = get_y(k);
                            if ( xo2 == NOBODY) mvwprintw(v->w_uttt,y_inner,x_inner,".");
                            else if ( xo2 == PLAYER_O) mvwprintw(v->w_uttt,y_inner,x_inner,"O");
                            else if ( xo2 == PLAYER_X) mvwprintw(v->w_uttt,y_inner,x_inner,"X");
                            else if ( xo2 == BOTH) mvwprintw(v->w_uttt,y_inner,x_inner,"#");
                            wrefresh(v->w_uttt);
        }
        wmove(v->w_ttt, pos_y, pos_x);
        wrefresh(v->w_ttt); 
        ch = wgetch(v->w_ttt);
        switch(ch)
	    {	
            case KEY_RIGHT: 
                if(pos_x+2<=6){
                    pos_x=pos_x+2;
                }
                break;
            case KEY_LEFT: 
                if(pos_x-2>=2){
                    pos_x=pos_x-2;
                }
                break;
            case KEY_UP: 
                    if(pos_y-2>=3){
                        pos_y=pos_y-2;
                    }
                break;
            case KEY_DOWN: 
                    if(pos_y+2<=7){
                        pos_y=pos_y+2;
                    }
                break;
            case 10 : 
                    if ( ((get_next_outer_position(v->p_uttt) == FREE) || (get_next_outer_position(v->p_uttt) == get_outer(pos_x,pos_y)) ) && (v->p_uttt->outer_tictactoe->content[get_outer(pos_x,pos_y)] == NOBODY) ){
                        outer_pos = get_outer(pos_x,pos_y);
                        ch =' ';
                    }

                    break;
            case 'q':   
                        mvwprintw(v->w_ttt,4,0,"YOU QUIT THE GAME !");
                        wrefresh(v->w_ttt); 
                        m->outer_position=NONE;
                        return;

            default:
                        break;
	    }
        
    }

    wrefresh(v->w_ttt );
    wrefresh(v->w_uttt );
    int ch2 = -1;
    ch =-1;
    int inner_pos_x=2;
    int i =-1;
    int inner_pos_y=3;
    while(ch2!=' ')
    {
        wmove(v->w_uttt, inner_pos_y, inner_pos_x);
        wrefresh(v->w_uttt); 
        ch2 = wgetch(v->w_uttt);
        switch(ch2)
	    {	
            case 'C': 
                if(inner_pos_x+2<=6){
                    inner_pos_x=inner_pos_x+2;
                }
                break;
            case 'D': 
                if(inner_pos_x-2>=2){
                    inner_pos_x=inner_pos_x-2;
                }
                break;
            case 'A': 
                    if(inner_pos_y-2>=3){
                        inner_pos_y=inner_pos_y-2;
                    }
                break;
            case 'B': 
                    if(inner_pos_y+2<=7){
                        inner_pos_y=inner_pos_y+2;
                    }
                break;
            case 10 : 
                    i = get_outer(inner_pos_x,inner_pos_y);
                    m->inner_position= i;
                    m->outer_position = outer_pos;
                    if (is_move_valid(v->p_uttt,m) == YES){
                        mvwaddch(v->w_uttt,inner_pos_y,inner_pos_x,xo);
                        wrefresh(v->w_uttt); 
                        wrefresh(v->w_ttt); 
                        ch2=' '; 
                        ch3=' ';
                    }

                    break;
            case 127:   
                        ch2=' ';
                        break;
            case 'q':   
                        mvwprintw(v->w_ttt,4,0,"YOU QUIT THE GAME !");
                        wrefresh(v->w_ttt); 
                        m->outer_position=NONE;
                        return;


            default:    
    
                        break;
	    }
        
    }
}
}

void set_next_player_move(s_move * m,p_view v, e_tactic tactic){
    if (v->p_uttt->inception_level == 1) set_next_player_move_i1(m,v,tactic);
    else if (v->p_uttt->inception_level == 2) set_next_player_move_i2(m,v,tactic);

}

void free_view(p_view s){
    if (s != NULL) free(s);
}

void display_winner(p_view v){
    if (v ==NULL){
		    fprintf(stderr,"Error! 23");
		    exit(EXIT_FAILURE);
	    }
    mvwprintw(stdscr,16,0,"The winner is : %c\n",v->p_uttt->outer_tictactoe->winner);
     wrefresh(stdscr); 
    
}
