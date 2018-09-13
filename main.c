

#include "SudokuComponents.h"

int main()
{
    //sets initial top of stack to 0;
    int top = 0;

    // checks if array is populated with values
    bool arrayFull = false;
    //keeps track of an entered positions row
    int currentPositionRow = 0;
    //keeps track of an entered positions column
    int currentPositionCol = 0;
    //keeps track of total moves made during game
    int totalMoves = 0;
    bool playagain = true;
    char sudokuGrid[9][9];
    char sudokuOriginal[9][9];
    char selection;
    char con;
    //stores all the moves a player makes
    struct Square stackMoves[81];
    bool win = false;
    bool validInput = false;
    while(playagain == true)
    {


        while(win == false)
       {
         printf("1: Enter a Sudoku Grid \n");
         printf("2: Show hints \n");
         printf("3: Enter number in square \n");
         printf("4: Print current Sudoku \n");
         printf("5: Backtrack \n");
         printf("6: Exit \n");

         scanf("%s", &selection);

         switch(selection)
            {
            case '1':
                ReadSudokuGrid(*sudokuGrid, sudokuOriginal, &arrayFull);
                break;

            case '2':
                if(arrayFull == true)
                {
                    MoveToPosition(sudokuGrid, &currentPositionRow, &currentPositionCol);
                    HelpfulHints(sudokuGrid, currentPositionRow, currentPositionCol);

                }
                else{
                    printf("You don't have a Sudoku file to work with! \n");
                }
                break;
            case '3':
                if(arrayFull != false)
                {

                    if(win == false)
                    {
                    MoveToPosition(sudokuGrid, &currentPositionRow, &currentPositionCol );
                    validInput = InputNumber(sudokuGrid, currentPositionRow, currentPositionCol);
                    if(validInput == true)
                    {
                        //save a move and push it into a stack
                        PushMove(currentPositionRow, currentPositionCol, stackMoves, &top);
                        totalMoves++;

                    }
                    }
                    //checks after a move is made if there are still remaining empty squares on grid to see if game should
                    //continue
                    win = Empty_Squares(sudokuGrid);
                }
                else
                {
                    printf("You don't have a Sudoku file to work with! \n");
                }
                break;
            case '4':
                if(arrayFull != false)
                {
                    PrintSudoku(sudokuGrid);
                }
                else
                {
                    printf("You don't have a Sudoku file to work with! \n");
                }
                break;
            case '5':
                if(arrayFull !=false && totalMoves != 0)
                {
                    BackTrack(sudokuGrid, &totalMoves, stackMoves, &top);
                }
                else if(arrayFull == true && totalMoves == 0)
                {
                    printf("You haven't made any moves \n");
                }
                else
                {
                    printf("You don't have a Sudoku file to work with! \n");
                }
                break;
            case '6':
                win = true;
                break;
            default:
                printf("Invalid Input!!! \n");

         }

        }
        //checks if user did not push exit
        if(selection != '6')
        {
        printf("Congratulations, You WIN!!!!!!! \n");

            if(win == true)
            {
                printf("Do you want to play again, press Y if yes \n");
                scanf("%s", &con);
                if(con == 'Y' || con == 'y')
                {
                    win = false;
                }
                else
                {
                    playagain = false;
                }
            }
        }
        else
        {
            playagain = false;
        }

    }
}

