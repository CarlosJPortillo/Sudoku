#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SudokuStructs.h"




// reads in a sudoku grid
void ReadSudokuGrid(char grid[][9], char grid2[][9], bool *arrayFull);
//prints the sudoku grid
void PrintSudoku(char grid[][9]);
//checks if Sudoku grid is completed,
bool Empty_Squares(char grid[][9]);
//lets the user choose which position in the grid they want to go to
void MoveToPosition(char grid[][9], int *currentPositionRow, int *currentPositionCol);
//checks if a input number is safe at a certain position
bool IsSafe(char grid[][9], char inputNum, int currentPositionRow, int currentPositionCol);
//checks to see if input number is not aleady existent in same row
bool RowSafety(char grid[][9], char inputNum, int currentPositionRow);
//checks to see if input number is not already existent in same column
bool ColumnSafety(char grid[][9], char inputNum, int currentPositionCol);
//checks to see if input number is not already existent in same box
bool BoxSafety(char grid[][9], char inputNum, int currentPositionRow, int currentPositionCol);
//lets user input number into a position
bool InputNumber(char grid [][9], int currentPositionRow, int currentPositionCol);
//Uses helper functions to help suggest hints to the player if they are any available
void HelpfulHints(char grid[][9], int currentPositionRow, int currentPositionCol);
//lets the user know what safe numbers there are at a certain position
void SafeNumbers(char grid[][9], int currentPositionRow, int currentPositionCol, char safeNums[], int *sCount);
//finds which box current position lies in
void FindBox(int currentPositionRow, int currentPositionCol, struct Box *box);
//pushes a move made into stack
void PushMove(int xPos, int yPos, struct Square stackMoves[], int *top);
//pops a move made from stack
void PopMove(int *top);
//Allows user to backtrack should he or she desire to
void BackTrack(char grid[][9], int *totalMoves, struct Square stackMoves[], int *top);
//Looks to see if there is a possible hidden single at a position
void LookForPossibleHiddenSingle(int currentRowPosition, int currentColPosition, char grid[][9], int sCount, char safeNums[]);
//Prints the hidden single at a position otherwise prints letting user know there is no hidden single there
bool PrintHiddenSingle(char safeNums[], int sCount);
//if there is no hidden single found then check for the next best thing and a do a check for a locked row candidate
//for entered positions row inside a box
void LockedCandidateRow(char safeNums[], int currrentRowPosition, int currentColPosition, char grid[][9], int sCount);
//prints hidden locked candidate if available else saying there isn't one at current positions row in box
void PrintHiddenLockedCandidate(char safeNums[], int sCount);

