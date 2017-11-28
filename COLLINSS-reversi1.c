#include <stdio.h> 
#include "reversi.h"

/*
 * Initialise_Board()
 *
 * Initialises all squares on board to empty (zero)
 * Initialises central positions with two pieces for each player.
 * Initialises the scores for each player at two points each
 */

void Initialise_Board(void) {
        int row, col;

        for (col = 0; col <= size; col++) { /*loops through the columns first*/ 
            for (row = 0; row < size; row++) { /*loops through the rows after*/
            
                /* sets the board to the starting state depending on "size" */ 
                if ((col == (size / 2) && row + 1 == (size / 2)) || (col == ((size / 2) + 1) && row + 1 == ((size / 2) + 1))) { 
                    board[col][row] = PLAYER2;
                } else if ((col == ((size / 2) + 1) && row + 1 == size / 2) || (col == size / 2 && row + 1 == ((size / 2) + 1)))
                    board[col][row] = PLAYER1;
                else
                    board[col][row] = EMPTY_SPACE;
            }
        }

        player1_score = 2;
        player2_score = 2;
    }
    /*
     * Print_Board()
     *
     * Prints the board to the screen in the format given in the assignment sheet
     */
void Print_Board(void) {
    int col, row;
    fprintf(stdout,"\n");
    fprintf(stdout,"    ");
    
    /* ensures the board is of the correct format */for (col = 1; col <= size; col++) {
        if (col < 9) {
            if (col != size)
                fprintf(stdout,"%i ", col);
            else if (col == size)
                fprintf(stdout,"%i", col);
        } else
            fprintf(stdout,"%i", col);
    }

    fprintf(stdout,"\n");
    fprintf(stdout,"    "); /* formatting */
    for (col = 1; col <= size; col++) {
        fprintf(stdout,"_ ");
    }
    fprintf(stdout,"\n");
    for (row = 0; row < size; row++) {
        for (col = 0; col <= size; col++) {
            if (col == 0) {
                if ((row + 1) < 10)
                    fprintf(stdout," %i: ", row + 1);
                else
                    fprintf(stdout,"%i: ", row + 1);
            } else if (col != 0 && col <= size) {
                if (board[col][row] == PLAYER1)
                    fprintf(stdout,"O ");

                else if (board[col][row] == PLAYER2) {
                    fprintf(stdout,"* ");
                } else
                    fprintf(stdout,". ");
            }
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
    
		/* prints off the current score of player1 and player 2 */
    fprintf(stdout,"Player 1 (O) score: %i\n", player1_score);
    fprintf(stdout,"Player 2 (*) score: %i\n", player2_score);

}
