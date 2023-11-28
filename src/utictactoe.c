#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>
#include <stdbool.h>
#include<getopt.h>
#include <time.h>
#include "utictactoe.h"
#include "model.c"
#include "view.c"
#include "ia.c"
int main(int argc, char* argv[])
{
    static struct option long_opts []= {
    {"inception-level", 1,0,'i'},
    {"contest", 1,0,'c'},
    {"cross-ai", 1,0,'x'},
    {"round-ai", 1,0,'o'},
    {"verbose", 0,0,'v'},
    {"help", 0,0,'h'},
    {"version", 0,0,'V'},
    {0,0,0,0}
    };

    int myAtoi(char* str)
    {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
    }

    int optc,x;
    bool verbose = false;
    bool  contest_mode =false;
    int inception_level = 2;
    e_tactic tactic_cross = HUMAN;
    e_tactic tactic_round = CLEVER;

    
    optc = getopt_long (argc, argv, "i:x:o:c:vVh", long_opts, NULL);
    while (optc != -1)
    {
        switch (optc)
        {
        case 'h': 
                    printf("Usage: utictactoe ([-i LEVEL|-x N|-o N|-v|-V|-h] | -c FILE)\n"
                    "Play a utictactoe game with human or program players.\n" 
                    "-i, --inception-level LEVEL deepness of the game (min=1, max=3 (default=2))\n"
                    "-x, --cross-ai N set tactic of cross player 'X'\n"
                    "-o, --round-ai N set tactic of round player 'O'\n"
                    "-c, --contest enable 'contest' mode\n"
                    "-v, --verbose verbose output\n"
                    "-V, --version display version and exit\n"
                    "-h, --help display this help and exit\n"
                    "Tactics list: random (0), clever (1)\n");
                    exit (EXIT_SUCCESS);
                    break;
                    
        case 'V':
                    printf("utictactoe %d.%d.%d\n",VERSION,SUBVERSION,REVISION);
                    printf("This software implements a full ultimate tictactoe game.\n");
                    exit (EXIT_SUCCESS);
                    
                    break;
        case 'v':
                    verbose = true;
                    optc = -1;
                    break;
        case 'c':   
                    contest_mode = true;
                    if( !access( argv[2], R_OK ) ) {
                        printf( "ok to read %s\n", argv[2] );
                        optc = -1;
                        break;
                    } 
                    else {
                        perror( argv[2] );
                        exit (EXIT_FAILURE);

                    }

        case 'o':   
                    x = myAtoi(argv[2]);
                    if ((x == 0) || (x == 1)|| (x == 2))
                    {
                        tactic_round= x;
                        optc = -1;
                        break;
                    }
                    else exit (EXIT_FAILURE);
                     
        case 'x':   
                    x = myAtoi(argv[2]);

                    if (x == 0)
                    {
                        tactic_cross= HUMAN;
                        optc = -1;
                        break;
                    }
                    else if (x == 1)
                    {
                        tactic_cross= RANDOM;
                        optc = -1;
                        break;
                    }
                    else if (x == 2)
                    {
                        tactic_cross= CLEVER;
                        optc = -1;
                        break;
                    }
                    else exit (EXIT_FAILURE);

        case 'i':   
        
                    x = atoi(argv [2]);
                    if ((x<= 3) && (x>= 1))
                    {
                        inception_level = x;
                        optc = -1;
                        break;
                    }
                    else exit (EXIT_FAILURE);
        default:
                    printf("Try `utictactoe --help' for more information. \n");
                    exit (EXIT_FAILURE);
        }
        break;
    }
  srand(time(NULL));
  s_utictactoe *s = create_empty_utictactoe(inception_level);
  s_move *m = create_empty_move();
  p_view v = create_view(s);
  while (s->outer_tictactoe->winner == NOBODY) {
    m->player = get_next_player_to_play(s);
    if (m->player == PLAYER_X) {
      set_next_player_move(m, v, tactic_cross);
    } else {
      set_next_player_move(m, v, tactic_round);
    }
    if (m->outer_position == NONE) break;
    play_move(s, m);
  }
  display_winner(v);
  free_view(v);
  //draw_utictactoe_history(s);
  getchar();//just to pause before quitting the program
  free_move(m);
  free_utictactoe(s);
  exit(EXIT_SUCCESS);
}   