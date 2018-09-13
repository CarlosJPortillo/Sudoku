#include "SudokuComponents.h"



void ReadSudokuGrid(char grid[][9], char grid2[][9], bool *arrayFull)
{

    FILE* filePointer;
    //file which user will open
    char file[20];

    printf("Enter file name you want to work with");
    scanf("%s", file);


    if(filePointer = fopen(file, "r"))
    {
    int i, j;
    char singlecharacter;
    char *charpointer;

        for(i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
              singlecharacter = fgetc(filePointer);
              charpointer = &grid[i][j];
              *charpointer = singlecharacter;
               charpointer = &grid2[i][j];
              *charpointer = singlecharacter;
            }
        }
        //close pointer to free up resources
        fclose(filePointer);
        *arrayFull = true;
    }
    else
    {
        printf("File does not exist \n");
        fclose(filePointer);
    }


}

void PrintSudoku(char grid[][9])
{
    printf("\n");
    int i, j;
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            //program can work with either 0's or x's in place of empty square read from file
            if(grid[i][j] == 'x' ||grid[i][j] == '0')
            {
                printf(" ");
            }
            else
            {
                printf("%c", grid[i][j]);
            }

            printf("|");

        }
        //print a long big line after each row
        printf("\n__________________ \n");
    }

}

bool Empty_Squares(char grid[][9])
{
    bool win = true;
    int i, j;
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)

        {
            //if there is an empty spot go there
            if(grid[i][j] == 'x' || grid[i][j] == '0')
            {
                win = false;
                return win;
            }

        }
    }
    return win;
}
void MoveToPosition(char grid[][9], int* currentPositionRow, int* currentPositionCol)
{
    bool valid = false;
    char buf[BUFSIZ];
    int xInput, yInput;



    while(valid == false)
    {
        do{

            printf(" Please enter a row position of 1- 9 only \n");
            scanf("%s", buf);
            xInput = atoi(buf);
            printf("Enter a column position of 1-9 only \n");
            scanf("%s", buf);
            yInput = atoi(buf);

        }while(xInput <= 0 || xInput >= 10 || yInput <= 0 || yInput >= 10);

        *currentPositionRow = xInput - 1;
        *currentPositionCol = yInput - 1;
        if(grid[*currentPositionRow][*currentPositionCol] == 'x' ||grid[*currentPositionRow][*currentPositionCol] == '0' )
        {
            valid = true;
        }
        else
        {
            printf("That position is already filled \n");
        }
    }



}

bool InputNumber(char grid [][9], int currentPositionRow, int currentPositionCol)
{
    char cInput;
    char* pCInput;
    bool valid;
    int inputNum = 0;
    printf("Enter a number 1-9 at position %d, %d ", currentPositionRow + 1, currentPositionCol + 1);
    scanf("%d", &inputNum);

    if(inputNum >=1 && inputNum <=9)
    {
        cInput = inputNum + '0';
        valid = IsSafe(grid, cInput, currentPositionRow, currentPositionCol);
    }
    else
    {
        printf("Number needs to be between 1 - 9 inclusive \n");
    }
    if(valid == true)
    {
        pCInput =  &grid[currentPositionRow][currentPositionCol];
        *pCInput = cInput;

    }
    else if(valid == false)
    {
        printf("That number is not safe \n");
    }
    return valid;
}
bool IsSafe(char grid[][9], char inputNum, int currentPositionRow, int currentPositionCol)
{
	bool safe = true;
	safe = RowSafety(grid, inputNum, currentPositionRow);
	if(safe == true)
    {
        safe =  ColumnSafety(grid, inputNum, currentPositionCol);
    }
    if(safe == true)
    {
        safe = BoxSafety(grid, inputNum, currentPositionRow,  currentPositionCol);
    }
	return safe;
}
bool RowSafety(char grid[][9], char inputNum, int currentPositionRow)
{
	bool safe = true;
	int i;
	for(i = 0; i < 9; i ++)
	{
		if(grid[currentPositionRow][i] == inputNum)
		{
			safe = false;
		}
	}

	return safe;

}
bool ColumnSafety(char grid[][9], char inputNum, int currentPositionCol)
{
	bool safe = true;
	int i;
	for(i = 0; i < 9; i ++)
	{
		if(grid[i][currentPositionCol] == inputNum)
		{
			safe = false;
		}


	}
	return safe;

}
bool BoxSafety(char grid[][9], char inputNum, int currentPositionRow, int currentPositionCol)
{
	struct Box box;
	int i, j;
	bool safe = true;

	FindBox(currentPositionRow, currentPositionCol, &box);


	for(i = box.startRow; i < box.startRow + 3; i++)
		{
			for(j = box.startCol; j < box.startCol + 3; j++)
			{
				if(grid[i][j] == inputNum)
				{
					safe = false;
				}

			}
		}
    return safe;

}

void FindBox(int currentPositionRow, int currentPositionCol, struct Box *box)
{

    if(currentPositionRow <3 && currentPositionCol < 3)
	{
		box->startRow = 0;
		box->startCol =  0;
	}
	else if(currentPositionRow < 3 && currentPositionCol <6 && currentPositionCol >2)
	{
		box->startRow = 0;
		box->startCol  = 3;
	}
	else if(currentPositionRow < 3 && currentPositionCol >5)
	{
		box->startRow = 0;
		box->startCol =  6;
	}
	else if(currentPositionRow < 6 && currentPositionRow >2 && currentPositionCol < 3)
	{
		box->startRow = 3;
		box->startCol =  0;
	}
	else if(currentPositionRow < 6 && currentPositionRow > 2 && currentPositionCol <6 && currentPositionCol >2)
	{
		box->startRow = 3;
		box->startCol =  3;
	}
	else if(currentPositionRow < 6 && currentPositionRow >2 && currentPositionCol >5)
	{
		box->startRow = 3;
		box->startCol =  6;
	}
	else if(currentPositionRow > 5 && currentPositionCol < 3)
	{
		box->startRow = 6;
		box->startCol =  0;
	}
	else if( currentPositionRow > 5 && currentPositionCol <6 && currentPositionCol >2)
	{
		box->startRow = 6;
		box->startCol =  3;
	}
	else if(currentPositionRow >5 && currentPositionCol >5)
	{
		box->startRow = 6;
		box->startCol =  6;
	}

}
void HelpfulHints(char grid[][9], int currentPositionRow, int currentPositionCol)
{
    char safeNums[10];
    //variable to keep track of how many safe numbers there are
    int sCount = 0;
    SafeNumbers(grid, currentPositionRow, currentPositionCol, safeNums, &sCount);
    if(sCount != 0)
    {
        int i;
        for(i = 0; i < sCount; i++)
        {
            printf("%c,", safeNums[i]);
        }
        // if a empty square has only 1 safe number, then that is a naked single
        if(sCount == 1)
        {
            printf(" is a naked single");
        }
        else
        {
        printf(" are safe numbers \n");
        LookForPossibleHiddenSingle(currentPositionRow, currentPositionCol, grid, sCount, safeNums);
        bool hiddenSingle = PrintHiddenSingle(safeNums, sCount);
        if(hiddenSingle == false)
        {
            sCount = 0;
            SafeNumbers(grid, currentPositionRow, currentPositionCol, safeNums, &sCount);
            LockedCandidateRow(safeNums, currentPositionRow, currentPositionCol, grid, sCount);
            PrintHiddenLockedCandidate(safeNums, sCount);

        }
        }
    }
    else
    {
        printf("There are no safe numbers at this position, I recommend you backtrack \n");
    }


}
void SafeNumbers(char grid[][9], int currentPositionRow, int currrentPositionCol, char safeNums[], int *sCount)
{
    bool safe;
	char cInput;
	char *pointerCinput;
	int i, j;
	j = 0;
	for(i = 1; i <= 9; i ++)
	{
	  cInput = i + '0';
      safe = IsSafe(grid, cInput, currentPositionRow, currrentPositionCol);
      if(safe == true)
      {

          pointerCinput = &safeNums[j];
          *pointerCinput = cInput;
          //increase count of safe numbers
          *sCount = *sCount + 1;
          j++;
	  }
	}

}

void PushMove(int xPos, int yPos, struct Square stackMoves[], int *top)
{
    struct Square square;
    square.xPosition = xPos;
    square.yPosition = yPos;
    stackMoves[*top] = square;
    *top = *top + 1;

}
void PopMove(int *top)
{
    *top = *top - 1;

}

void BackTrack(char grid[][9], int *totalMoves, struct Square stackMoves[], int *top)
{
    char buf[BUFSIZ];
    int moves;
    do {

        printf("How many moves do you want to backtrack, pick number equal less than total moves made only ");
        scanf("%s", buf);
        moves = atoi(buf);
    }while(moves > *totalMoves || moves == 0);

    while(moves > 0)
    {
        int x = stackMoves[*top - 1].xPosition;
        int y = stackMoves[*top - 1].yPosition;

        char *cPointer;
        cPointer = &grid[x][y];
        *cPointer = 'x';
        PopMove(top);
        //decrement the total moves made
        *totalMoves = totalMoves - 1;
        moves--;

    }
}
void LookForPossibleHiddenSingle(int currentPositionRow, int currentPositionCol, char grid[][9], int sCount, char safeNums[])
{
    int i, j, z;
    //will store the safe numbers a empty square on the same row of current position
    char safeNums2[10];
    int sCount2 = 0;
    //loop to go through every column in current positions row
    for(i = 0; i < 9; i++)
    {
        //do a check for an empty square at each column in that row except the current position
        if((grid[currentPositionRow][i] == 'x' || grid[currentPositionRow][i] == '0') &&(i != currentPositionCol))
        {
            //get that square's safe numbers
            SafeNumbers(grid, currentPositionRow, i, safeNums2, &sCount2);
            //iterates through every safe number in entered current position
            for(j = 0; j < sCount; j++)
            {
                for(z = 0; z < sCount2; z++)
                {
                    //checks if another square on the same row shares a safe number ruling out that number as not a hidden
                    //single changing its value to 0
                    if(safeNums2[z] == safeNums[j])
                    {
                        char *pCharac;
                        pCharac = &safeNums[j];
                        *pCharac = '0';
                    }
                }
            }
            sCount2 = 0;
        }

    }

}
bool PrintHiddenSingle(char safeNums[], int sCount)
{
    bool hiddenSingle = false;
    int i;
    for(i = 0; i < sCount; i++)
    {
        if(safeNums[i] != '0')
        {
            printf("%c is a hidden single \n", safeNums[i] );
            hiddenSingle = true;
        }
    }
    if(hiddenSingle == false)
    {
        printf("There is no hidden single for this position \n");
    }
    return hiddenSingle;

}
void LockedCandidateRow(char safeNums[], int currentPositionRow, int currentPositionCol, char grid[][9], int sCount)
{
	struct Box box;
	//find which box position lies in
	FindBox(currentPositionRow, currentPositionCol, &box);
	int i, j, a, z;
	char safeNums2[10];
	int sCount2 = 0;
    //outer loop for box rows
	for(i = box.startRow; i < box.startRow+3; i++)
	{
	    //inner loop for box columns
	    for(a = box.startCol; a < box.startCol+3; a++)
        {

	    // only checks empty squares that are not on the same row as entered position
            if((grid[i][a] == 'x' || grid[i][a] == '0') && (i != currentPositionRow))
            {


                SafeNumbers(grid, i, a, safeNums2, &sCount2);
            //iterates through every safe number in entered current position
                for(j = 0; j < sCount; j++)
                {
                    for(z = 0; z < sCount2; z++)
                    {
                        //compare a square's safe numbers with the safe numbers
                        if(safeNums2[z] == safeNums[j])
                        {
                        char *pCharac;
                        pCharac = &safeNums[j];
                        *pCharac = '0';
                        }
                    }
                }
                sCount2 = 0;
            }
        }

    }
}
void PrintHiddenLockedCandidate(char safeNums[], int sCount)
{
    bool lockedCandidate = false;
    int i;
    for(i = 0; i < sCount; i++)
    {
        if(safeNums[i] != '0')
        {
            printf("%c is a hidden candidate and belongs inside this box at this positions row \n", safeNums[i] );
            lockedCandidate = true;
        }
    }
    if(lockedCandidate == false)
    {
        printf("There is no hidden candidate in this box row \n");
    }



}





