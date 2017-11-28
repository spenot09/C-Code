#include <stdio.h>
#include "reversi.h"

/*
 * Best_Move()
 *
 * This function finds the best move that given <player> can make
 *
 * Returns the score of the best move that given player can make, i.e. the
 *     number of squares converted from the opponent's colour to the player's
 *     colour by the best move, plus one for the move itself.
 *
 * Returns 0 if no move can be made
 *
 

	 
 * Fills <xposition> and <yposition> pointers to the best move in the grid
 * If several moves give the same best score, uses the first move when
 * scanning the board in "raster scan" order (see image processing assignment)
 */
int Best_Move(int player, int *xposition, int *yposition){
	
   /* the function returns -1 because that indicates to the calling function
    * that the given player can't move, which is the behaviour we want when
    * the function isn't implemented. When you write the function, replace
    * the return value with the score for the best move.
    */
    int col, row, score, FinalScore=0, enemy;
    
   /* "enemy" is set based on which player's turn it is */
   if (player==PLAYER1)
   				enemy=PLAYER2;
   if (player==PLAYER2)
   				enemy=PLAYER1;
   				
   /* each location on the board is looped through */
   for (row=0; row<size; row++){
		for (col=1; col<=size; col++){
     			/* location is checked if it's an empty space and if it's surrounded by "enemy" tiles */
     			if (board[col][row]==EMPTY_SPACE && (board[col-1][row-1]==enemy||(board[(col)-1][row]==enemy)||(board[(col)-1][(row)+1]==enemy)||board[col][(row)+1]==enemy||board[col][(row)-1]==enemy||board[(col)+1][(row)+1]==enemy||board[(col)+1][row]==enemy||board[(col)+1][(row)-1]==enemy)){			
						score=Get_Score(player, col, row);
						/* always the move that will yield the highest score is updated to *xposition and *yposition */
							if (score>FinalScore){
								FinalScore=score;
								*xposition= col;
								*yposition= row;
							}
					}
		  } 			
		}		

	 	return FinalScore; /* 0 is returned if there are no more valid moves on the board */
}


