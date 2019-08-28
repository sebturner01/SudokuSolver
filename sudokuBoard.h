/**
 * Author:  Sebastian Turner 
 * Date: 08/26/19
 * 
 * Implements a sudoku board as a 9x9 grouping of 'Cell' types. Each cell type
 * consists of the current value within that cell (0 if not initalized) and
 * whether or not that value is original (was given as a clue).
 * 
 * To initialze a board that represents a given sudoku construction/puzzle. 
 * A string of length 81 (excluding terminator) that row by row represents the
 * given puzzle is to be used as the argument for initSetBoard.
 * 
 * This module also implements functions for checking the legality of a given 
 * sudoku position (set of values for the board). This legality is as defined 
 * in README.md.
 * 
 * Access to this 2d array of cells is done in the way a matrix is 
 * traditionally examined in linear algebra. That is all declarations are in
 * [row][col] format.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BOARDSIZE 9 //sudoku boards are square so only one value is needed 

typedef struct cell{
    int value; //The current value in the cell
    bool clue; //Whether or not the given value was given as a clue
}Cell;

/********* function prototypes *********/ 

//Initialization, setters, and getters
Cell **initBoard();    //initialzes an empty board
Cell **initSetBoard(char *clues); //intializes a board from a given clue set
Cell *getCell(int row, int col, Cell **board);
void setCellVal(Cell **board, int row, int col, int val);

//Legality functions
bool isCompleteBoard(Cell **board);
bool checkBoard(Cell **board); 
bool isLegalCell(Cell **board, int row, int col);
bool isLegalRow(Cell **board, int row);
bool isLegalCol(Cell **board, int col);
bool isLegalSquare(Cell **board, int row, int col);

//General functions
void printBoard();
void deleteBoard();

/**
 * Creates a 9*9 sudoku board out Cell structs. As there is no independent 
 * sudoku board struct this function will return a pointer to the first value 
 * of the board. 
 * 
 * This function will return NULL if any of the memory requested could not be 
 * allocated
 */ 
Cell** initBoard();

/**
 * Initialzes a set sudoku board. This is read in as a string of integers of 
 * length 81. This function returns a pointer to the first Cell in the board.
 * 
 * Will return NULL if any of the memory required for the board could not be
 * allocated or if the `clues` argument is not of the proper length (81) or if
 * it contains any non-numerical
 */ 
Cell** initSetBoard(char *clues);

/**
 * Returns the address of a cell given a specific row and column and the board
 * that that cell resides in. This function will return NULL in the following 
 * circumstances.
 * 
 * 1. Row or Col is < 0 or >= than BOARDSIZE
 * 2. Board is NULL 
 */
Cell *getCell(int row, int col, Cell** board);


/**
 * Sets the cell at the given [row][col] to the given value. This function
 * will do nothing if the given board is NULL, either the row or col argument
 * is not within the board or if the given value is not within 1 - 9.
 */ 
void setCellVal(Cell **board, int row, int col, int val);

/**
 * Checks if a the cell at the given [row][col] position has a legal value given
 * the relvant row, column, and square it is in. 
 * 
 * This function will return false if the isLegalRow, isLegalCol, or the
 * isLegalSquare tests fail. In addition this fucntion will return false if 
 * the given [row][col] position is not within the board or if the given board 
 * is NULL.
 */ 
bool isLegalCell(Cell** board, int row, int col);


/**
 * Checks the given sudoku board for legality of position. If the position is 
 * not legal then this function will return false. This function will also 
 * return false in the case that the given board is NULL or if any of cells 
 * within it are NULL
 */
bool checkBoard(Cell **board);

/**
 * Checks if a given row is legal. That is that the row contains only unique 
 * numbers. If only unique numbers are found then this fucntion returns true.
 * 
 * This function will return false if the board is not initialized or 
 * if row is less than 0 or greater or equal to BOARDSIZE.
 */ 
bool isLegalRow(Cell **board, int row);

/**
 * Checks if a given column is legal. That is that each cell only contains 
 * unique values between 1 - 9. If that is the case then this funciton returns
 * true.
 * 
 * This function will return false if:
 * a. The board is not initialzed
 * b. col is < 0 or greater than or equal to BOARDSIZE.
 */ 
bool isLegalCol(Cell **board, int col);

/**
 * Checks if a given square is legal in the sudoku position. A square may be 
 * referenced by any Cell in it's 3x3 area. 
 * 
 * This function returns false if any duplicate values are found within the 
 * referenced square or if the given board is NULL, or the x,y position given 
 * is not within the sudoku board. 
 * 
 * Otherwise this function will return true.
 */ 
bool isLegalSquare(Cell **board, int row, int col);


/**
 * Prints a version of the sudoku board to the console. This function will not
 * change anything about the given board. If the given board is NULL this 
 * function will not print anything
 */ 
void printBoard(Cell **board);

/**
 * Deletes a given board from memory cell by cell. If the given board is NULL
 * this function will simply return and not throw an error.
 */ 
void deleteBoard(Cell **board);