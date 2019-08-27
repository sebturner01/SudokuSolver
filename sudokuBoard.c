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
Cell **initSetBoard(char *clues); //intializes a board with the given set
Cell *getCell(int row, int col, Cell **board);
void setCellVal(Cell **board, int row, int col, int val);
static char *convertToWSStr(char *str);

//Legality functions
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
Cell** initBoard()
{
    Cell** board = calloc(BOARDSIZE, __SIZEOF_POINTER__);
    if(board == NULL){
        return NULL;
    }
    for(int i = 0; i < BOARDSIZE; i++){
        board[i] = calloc(BOARDSIZE, __SIZEOF_POINTER__);
        if(board[i] == NULL){
            return NULL;
        }
        for(int j = 0; j < BOARDSIZE; j++){
            Cell *cell = malloc(sizeof(Cell));
            if(cell == NULL){
                return NULL;
            }
            cell->clue = false;
            cell->value = 0;
            board[i][j] = *cell;
        }
    }
    return board;
}

/**
 * Initialzes a set sudoku board. This is read in as a string of integers of 
 * length 81. This function returns a pointer to the first Cell in the board.
 * 
 * Will return NULL if any of the memory required for the board could not be
 * allocated or if the `clues` argument is not of the proper length (81) or if
 * it contains any non-numerical
 */ 
Cell** initSetBoard(char *clues)
{
    int len = strlen(clues); 
    if(len != 81){
        fprintf(stderr, "Invalid clues string\n");
        return NULL;
    }

    //checking that all given values are numerical
    for(int i = 0; i < len; i++){
        char c = clues[i];
        if(!isdigit(c)){
            fprintf(stderr, "The given clue sequence contains the non-numeric char %c\n", c);
            return NULL;
        }
    }
    char *newClues = convertToWSStr(clues);
    Cell** board = initBoard();
    if(board == NULL){
        fprintf(stderr, "Unable to intialize board");
        exit(4);
    }
    int loc = 0;
    int cellVal;
    for(int row = 0; row < BOARDSIZE; row++){
        for(int col = 0; col < BOARDSIZE; col++){
            Cell *curCell = getCell(row, col, board);
            sscanf(&newClues[loc], "%d", &cellVal);
            if(cellVal > 0){  
                 curCell->clue = true;
                 curCell->value = cellVal;
            }
            loc += 2;
        }
    }
    return board;
}


/**
 * Returns the address of a cell given a specific row and column and the board
 * that that cell resides in. This function will return NULL in the following 
 * circumstances.
 * 
 * 1. Row or Col is < 0 or >= than BOARDSIZE
 * 2. Board is NULL 
 */
Cell *getCell(int row, int col, Cell** board)
{
    if(row < 0 || row >= BOARDSIZE ||
       col < 0 || col >= BOARDSIZE || 
       board == NULL){
           return NULL;
    }

    Cell *cell = &board[row][col];
    return cell;
}

/**
 * Sets the cell at the given [row][col] to the given value. This function
 * will do nothing if the given board is NULL, either the row or col argument
 * is not within the board or if the given value is not within 1 - 9.
 */ 
void setCellVal(Cell **board, int row, int col, int val)
{
    if(board == NULL ||
    row < 0 || row >= BOARDSIZE ||
    col < 0 || col >= BOARDSIZE ||
    val < 1 || val > 9){
        return;
    }

    Cell *cell = getCell(row, col, board);
    if(cell == NULL){
        return;
    }

    cell->value = val;
}


/**
 * Converts the clues input (used in initSetBoard) to a series of characters
 * seperated by whitespace for easier reading. This function will return NULL if
 * `clues` is NULL otherwise it will return the same string but with whitespace 
 * between each character.
 */ 
static char *convertToWSStr(char *str)
{
    if(str == NULL){
        return NULL;
    }

    int len = strlen(str);
    char *newStr = malloc(sizeof(char)*len*2+1); //Double the length of the  
                                                 //input string and then 
                                                 //re-add the null terminator 
    for(int loc = 0; loc < len; loc++){
        newStr[loc*2] = str[loc];
        newStr[loc*2+1] = ' ';
    }
    newStr[strlen(newStr)+1] = '\0';
    return newStr;
}

/**
 * Checks if a the cell at the given [row][col] position has a legal value given
 * the relvant row, column, and square it is in. 
 * 
 * This function will return false if the isLegalRow, isLegalCol, or the
 * isLegalSquare tests fail. In addition this fucntion will return false if 
 * the given [row][col] position is not within the board or if the given board 
 * is NULL.
 */ 
bool isLegalCell(Cell** board, int row, int col)
{
    if(board == NULL ||
       row < 0 || row >= BOARDSIZE ||
       col < 0 || col >= BOARDSIZE){
        return false;
    }

    if(!(isLegalCol(board, col) || 
         isLegalRow(board, row) ||
         isLegalSquare(board, row, col))){
        return false;
    }
    return true;
}

/**
 * Checks the given sudoku board for legality of position. If the position is 
 * not legal then this function will return false. This function will also 
 * return false in the case that the given board is NULL or if any of cells 
 * within it are NULL
 */
bool checkBoard(Cell **board)
{
    if(board == NULL){
        fprintf(stderr, "The given board is not initialized\n");
        return false;
    }

    for(int index = 0; index < BOARDSIZE; index++){
        if(!isLegalRow(board, index)){
            return false;
        }
        if(!isLegalCol(board, index)){
            return false;
        }
    }

    //Only need to check a total of 9 squares which can be referenced by their
    //upper left hand cells
    for(int row = 0; row < BOARDSIZE; row += 3){
        for(int col = 0; col < BOARDSIZE; col += 3){
            if(!isLegalSquare(board, row, col)){
                return false;
            }
        }
    }
    return true;

} 

/**
 * Checks if a given row is legal. That is that the row contains only unique 
 * numbers. If only unique numbers are found then this fucntion returns true.
 * 
 * This function will return false if the board is not initialized or 
 * if row is less than 0 or greater or equal to BOARDSIZE.
 */ 
bool isLegalRow(Cell **board, int row)
{
    if(board == NULL || row < 0 || row >= BOARDSIZE){
        return false;
    }

    for(int i = 0; i < BOARDSIZE; i++){
        int num = getCell(row, i, board)->value;
        if(num == 0){  //Never need to check uninitialized values
            continue;
        }

        //We want to check all other values in the row but never the original 
        //value. In addition we never need to "recheck" a given value pair. 

        for(int col = i + 1; col < BOARDSIZE; col++){
            int checkNum = getCell(row, col, board)->value;
            if(checkNum == 0){ //Never need to check unitialized values.
                continue;
            }
            if(num == checkNum){
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if a given column is legal. That is that each cell only contains 
 * unique values between 1 - 9. If that is the case then this funciton returns
 * true.
 * 
 * This function will return false if:
 * a. The board is not initialzed
 * b. col is < 0 or greater than or equal to BOARDSIZE.
 */ 
bool isLegalCol(Cell **board, int col)
{
    if(board == NULL || col < 0 || col >= BOARDSIZE){
        return NULL;
    }

    for(int i = 0; i < BOARDSIZE; i++){
        int num = getCell(i, col, board)->value;
        if(num == 0){  //Never need to check uninitialized values
            continue;
        }
         //We want to check all other values in the row but never the original 
         //value. In addition we never need to "recheck" a given value pair. 

        
        for(int row = i + 1; row < BOARDSIZE; row++){
            int checkNum = getCell(row, col, board)->value;
            if(checkNum == 0){ //Never need to check unitialized values.
                continue;
            }
            if(num == checkNum){
                return false;
            }
        }
    }
    return true;
}

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
bool isLegalSquare(Cell **board, int row, int col)
{
    if(board == NULL ||
       row < 0 || row >= BOARDSIZE ||
       col < 0 || col >= BOARDSIZE){
           return false;
    }
    int refRow = row - (row % 3); //Gives a row and col value that are easy to 
    int refCol = col - (col % 3); //work from. This references the top lefthand
                                  //cell in a given square

    int maxRow = refRow + 3;
    int maxCol = refCol + 3;

    for(int i = refRow; i < maxRow; i++){ 
        for(int j = refCol; j < maxCol; j++){
            int num = getCell(row, col, board)->value;
            if(num == 0){ //No need to check unitialized values
                continue;
            }

            for(int sRow = i; sRow < maxRow; sRow++){
                for(int sCol = j; sCol < maxCol; sCol++){
                    int checkNum = getCell(sRow, sCol, board)->value;
                    if(checkNum == 0){ //No need to check unitialzed values
                        continue;
                    }
                    if(num == checkNum){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}


/**
 * Prints a version of the sudoku board to the console. This function will not
 * change anything about the given board. If the given board is NULL this 
 * function will not print anything
 */ 
void printBoard(Cell **board)
{
    if(board == NULL){
        return;
    }

    //Printing some reference coordinates for columns
    printf("    ");
    for(int i = 0; i < BOARDSIZE; i++){
        printf(" %d ", i);
        if((i + 1) % 3 == 0){
            printf("  ");
        }
    }

    printf("\n");

    //First seperator line
    printf("   ");
    for(int i = 0; i < BOARDSIZE; i++){
        printf("___");
    }

    printf("_____\n");

    for(int row = 0; row < BOARDSIZE; row++){
        printf("%d|  ", row);
        for(int col = 0; col < BOARDSIZE; col++){
            int val = getCell(row, col, board)->value;
            if(val != 0){
                printf(" %d ", val);
            }
            else{
                printf("   ");
            }
            if((col + 1) % 3 == 0){
                printf("  ");
            }
        }
        printf("\n");
        if((row + 1) % 3 == 0){
            printf("\n");
        }
    }
}



/**
 * Deletes a given board from memory cell by cell. If the given board is NULL
 * this function will simply return and not throw an error.
 */ 
void deleteBoard(Cell **board)
{
    if(board == NULL){
        fprintf(stderr, "The given board is not initialized\n");
        return;
    }
    
    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; j++){
            Cell *cell = &board[i][j];
            if(cell != NULL){
                free(cell);
            }
        }
    }
    free(board);
}