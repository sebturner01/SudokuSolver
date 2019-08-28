/**
 * This tests the sudokuBoard module and also allows for user input so that they
 * can play a game of sudoku.
 */ 
#include "./sudokuBoard.h"

//function prototypes 
void checkInputs(const int argc, const char *argv[]);
void makeMove(int row, int col, int val);


int main(const int argc, const char *argv[])
{
    checkInputs(argc, argv);
    char *clue = malloc(strlen(argv[1]) + 1);
    strcpy(clue, argv[1]);
    Cell **board = initSetBoard(clue);
    bool stillPlaying = true;
    int row, col, val;
    while(stillPlaying){
        system("clear");
        printBoard(board);
        printf("Please enter a move: [row] [col] [val]\n");
        scanf("%d %d %d", &row, &col, &val);
        setCellVal(board, row, col, val);
        if(checkBoard(board) && isCompleteBoard(board)){
            stillPlaying = false;
        }
    }   
    
    bool legal = checkBoard(board);
    printf("%d\n", legal);
    //free(clue);
    return 0;

} 

/**
 * Checks the inputs for the proper form will exit with appropriate exit code 
 * and message if otherwise. The inputs should be as follows.
 * 
 * Usage: ./boardTest sudokuString
 * 
 * The appropriate string is 81 characters long consisting of only numbers
 * 
 * Exit statuses are as follows
 * 1 - Improper amount of arguments 
 * 2 - The length of the input string is incorrect
 * 3 - The input string contains non-
 */ 
void checkInputs(const int argc, const char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: %s [clue string]\n", argv[0]);
        exit(1);
    }

    //Checking clue string length
    const char *clueStr = argv[1];
    int len = strlen(clueStr);
    if(len != 81){
        fprintf(stderr, "Inputs string is not 81 chars (found %d instead)\n", len);
        exit(2);
    }

    //checking that all given values are numerical
    for(int i = 0; i < len; i++){
        char c = clueStr[i];
        if(!isdigit(c)){
            fprintf(stderr, "The given clue sequence contains the non-numeric char %c\n", c);
            exit(3);
        }
    }
}