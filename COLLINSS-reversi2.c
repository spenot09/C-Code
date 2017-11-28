#include <stdio.h>
#include "reversi.h"

/*
 * Get_Human_Move()
 *
 * Requests a valid move from the user for given <player>'s turn,
 *     either PLAYER1 or PLAYER2
 * Sets the x,y coordinates for the valid move by filling the <x> & <y>
 *     pointers
 * Returns the score for the chosen move, i.e. the number of squares converted
 *     from the opponent's colour to the player's colour, plus one for the
 *     move itself.
 *
 * Remember that the user types values in the range 1...MAX_BOARD_SIZE, but
 * the program should subtract 1 so that the x/y coordinates are in the
 * range 0...MAX_BOARD_SIZE-1. C likes numbers to start from 0!
 */

int Get_Human_Move(int player, int * x, int * y) {

    /* the function returns -1 because that indicates to the calling function
     * that the program should terminate, which is the behaviour we want when
     * the function isn't implemented. When you write the function, replace
     * the return value with the score for the chosen move.
     */
    int error = 1, test, score = 1, col, row, enemy = 0;
    char c;
		/* checks which player's turn it is and sets the opposition accordingly, "enemy" */
    if (player == PLAYER1)
        enemy = PLAYER2;

    if (player == PLAYER2)
        enemy = PLAYER1;
		/* loops until a correct move is entered */
    while (error == 1) {
        fprintf(stderr, "Enter your valid move player %i, in an x y format or 'q' to terminate or 'p' to pass \n", player);
        test = fscanf(stdin, "%d %d", x, y);

        if (test == 2) {
            if (( * x) <= MAX_BOARD_SIZE && ( * x) >= 0 && ( * y) <= MAX_BOARD_SIZE && ( * y) >= 0) {
                ( * y) --; /* (*x) does not need to be decremented due to the format of my initialisation */

                col = * x;
                row = * y;
								/* checks to see if entered move is a free space and if surrounded by "enemy" tiles */
                if (board[col][row] == EMPTY_SPACE && (board[col - 1][row - 1] == enemy || board[col - 1][row] == enemy || board[col - 1][row + 1] == enemy || board[col][row + 1] == enemy || board[col][row - 1] == enemy || board[col + 1][row + 1] == enemy || board[col + 1][row] == enemy || board[col + 1][row - 1] == enemy))
                    error = 0;
                score = Get_Score(player, col, row);
                if (score == 0)
                    error = 1;
            }
        } else if (test != 2) {
            test = fscanf(stdin, "%c", & c);
            if (c == 'p') {
                return 0;
            }
            if (c == 'q')
                return -1;
        }

    }

    return score;
}

/*
 * Get_Score()
 *
 * Returns the score for the chosen move <x>, <y> by the given <player>,
 *     i.e. the number of squares converted from the opponent's colour to the
 *     player's colour, plus one for the move itself.
 *
 * Returns 0 if no squares are converted
 */
int Get_Score(int player, int x, int y) {
    /* fill with your code, and replace return value as appropriate */
    int score = 0, go, i, j, enemy, tempscore = 0;
    
		/* checks which player's turn it is and sets the opposition accordingly, "enemy" */
    if (player == PLAYER1)
        enemy = 2;
    if (player == PLAYER2)
        enemy = 1;
        
		/* each direction (all 8) is looped through and the total points are added up */ 
    if (board[(x) - 1][(y) - 1] == enemy) {
        for (i = (x) - 1, j = (y) - 1, go = 1; i >= 0 && j >= 0 && go == 1; i--, j--) {
            if (board[i][j] == enemy)
                tempscore++; /*temporary score holder incase the line is not terminated with player's own tile */
            if (board[i][j] == player) {
                go = 0;
                score += tempscore; /* if line is terminated and points are aggregated it is added to the running total: "score" */
            }
            if (board[i][j] == EMPTY_SPACE) /* line is not terminated and so contents of "tempscore" are lost */
                go = 0; /* "go" is an exit variable that can be used to exit for loop prematurely */
        }
        tempscore = 0;
    }
    if (board[x - 1][y] == enemy) {
        for (i = (x) - 1, j = (y), go = 1; i >= 0 && go == 1; i--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x - 1][y + 1] == enemy) {
        for (i = (x) - 1, j = (y) + 1, go = 1; i >= 0 && j <= MAX_BOARD_SIZE && go == 1; i--, j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x][y + 1] == enemy) {
        for (i = (x), j = (y) + 1, go = 1; j <= MAX_BOARD_SIZE && go == 1; j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x][y - 1] == enemy) {
        for (i = (x), j = (y) - 1, go = 1; j >= 0 && go == 1; j--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y + 1] == enemy) {
        for (i = (x) + 1, j = (y) + 1, go = 1; i <= MAX_BOARD_SIZE && j <= MAX_BOARD_SIZE && go == 1; i++, j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y] == enemy) {
        for (i = (x) + 1, j = (y), go = 1; i <= MAX_BOARD_SIZE && go == 1; i++) {

            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y - 1] == enemy) {
        for (i = (x) + 1, j = (y) - 1, go = 1; i <= MAX_BOARD_SIZE && j >= 0 && go == 1; i++, j--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (score != 0)
        score++;

    return score;

}

/*
 * Move()
 *
 * Updates the board with given <player>'s move at <x>,<y>
 *
 * Returns the score on a successful move, i.e. the number of squares converted
 *     from the opponent's colour to the player's colour, plus one for the
 *     move itself.
 *
 * Returns 0 on an invalid move
 */
int Move(int player, int x, int y) {
    /* fill with your code, and replace return value as appropriate */
    int score = 0, go, i, j, s, enemy, tempscore = 0;

    board[x][y] = player;/* sets the intial position of player to an occupied state */
    
    /* checks which player's turn it is and sets the opposition accordingly, "enemy" */
    if (player == PLAYER1)
        enemy = 2;
    if (player == PLAYER2)
        enemy = 1;
        
    /* each direction is looped through as in Get_Score but the value of the tiles are set accordingly also*/
    if (board[(x) - 1][(y) - 1] == enemy) {
        for (i = (x) - 1, j = (y) - 1, go = 1; i >= 0 && j >= 0 && go == 1; i--, j--) {
            if (board[i][j] == enemy)
                tempscore++; /*temporary score holder incase the line is not terminated with player's own tile */
            if (board[i][j] == player) {
                go = 0;
                score += tempscore; /* if line is terminated and points are aggregated it is added to the running total: "score" */
                for (s = tempscore; s > 0; s--) /* sets the relevant tiles to player's tiles */
                    board[i + s][j + s] = player;
            }
            if (board[i][j] == EMPTY_SPACE) /* line is not terminated and so tempscore is lost and loop exits */
                go = 0; /* "go" is an exit variable that can be used to exit for loop prematurely */
        }
        tempscore = 0; /* reset to zero for next direction */
    }
    if (board[x - 1][y] == enemy) {
        for (i = (x) - 1, j = (y), go = 1; i >= 0 && go == 1; i--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i + s][j] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x - 1][y + 1] == enemy) {
        for (i = (x) - 1, j = (y) + 1, go = 1; i >= 0 && j <= MAX_BOARD_SIZE && go == 1; i--, j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i + s][j - s] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x][y + 1] == enemy) {
        for (i = (x), j = (y) + 1, go = 1; j <= MAX_BOARD_SIZE && go == 1; j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i][j - s] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x][y - 1] == enemy) {
        for (i = (x), j = (y) - 1, go = 1; j >= 0 && go == 1; j--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i][j + s] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y + 1] == enemy) {
        for (i = (x) + 1, j = (y) + 1, go = 1; i <= MAX_BOARD_SIZE && j <= MAX_BOARD_SIZE && go == 1; i++, j++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i - s][j - s] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y] == enemy) {
        for (i = (x) + 1, j = (y), go = 1; i <= MAX_BOARD_SIZE && go == 1; i++) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i - s][j] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }
    if (board[x + 1][y - 1] == enemy) {
        for (i = (x) + 1, j = (y) - 1, go = 1; i <= MAX_BOARD_SIZE && j >= 0 && go == 1; i++, j--) {
            if (board[i][j] == enemy)
                tempscore++;
            if (board[i][j] == player) {
                go = 0;
                score += tempscore;
                for (s = tempscore; s > 0; s--)
                    board[i - s][j + s] = player;
            }
            if (board[i][j] == EMPTY_SPACE)
                go = 0;
        }
        tempscore = 0;
    }

    if (score != 0)
        score++; /*increments for the move itslef as well */
        
    /* sets the new overall scores for each player to be printed */
    if (player == PLAYER1) {
        player1_score += score;
        player2_score -= (score - 1);
    }
    if (player == PLAYER2) {
        player2_score += score;
        player1_score -= (score - 1);
    }

    return score;
}
