//******************************************************************
// IMPLEMENTATION FILE (list.cpp)
// This file implements the GameBoard class member functions
// GameBoard representation: a Two-dimensional array
//******************************************************************
#include "gameboard.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
//Non-default constructor
GameBoardClass::GameBoardClass(/*IN/OUT*/ifstream& din) // Input file variable
{

	// Variable to store values from the input file
	LocRec tempLoc;

	// Reading in the board size values from the input file
	din >> boardSize.row >> boardSize.col;

	// Adding the border to the board size
	boardSize.row += BORDER;
	boardSize.col += BORDER;

	// Creating an empty 2D dynamic array
	gameBoard = new CellRec*[boardSize.row];

	for (int i = 0; i < boardSize.row; i++)
	{
		gameBoard[i] = new CellRec[boardSize.col];

	} // END for


	// Iterating through board, adding walls where necessary & initializing all non-walls to empty
	for(int i = 0; i < boardSize.row; i++)
	{

		for(int j = 0; j < boardSize.col; j++)
		{

			if(i == 0 || j == 0 || i == boardSize.row-1 || j == boardSize.col-1)
			{
				gameBoard[i][j].direction = INVALID;

			} // END if
			else
			{
				gameBoard[i][j].direction = EMPTY;

			} // END else

		} // END for

	} // END for


	// Priming read
	din >> tempLoc.row >> tempLoc.col;

	// Adding the walls specified by the input file to the board
	while(din)
	{
		gameBoard[tempLoc.row + 1][tempLoc.col + 1].direction = INVALID;
		din >> tempLoc.row >> tempLoc.col;

	} // END while

	// Adding the entrance and the exit of the board
	gameBoard[0][1].direction = 1;
	gameBoard[boardSize.row - 1][boardSize.col - 2].direction = VICTORY;

} // END NDC

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

CellRec GameBoardClass::Retrieve(/*IN*/LocRec tempLoc) // Location in the maze
{
	// Returning the value specified by tempLoc
	return gameBoard[tempLoc.row][tempLoc.col];

} // END Retrieve

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

void GameBoardClass::SetCellDirection(/*IN*/LocRec tempLoc, // Location in the maze
	                                  /*IN*/int direction)  // Direction of movement value
{
	// Setting the current direction of the cell
	gameBoard[tempLoc.row][tempLoc.col].direction = direction;

} // END SetCellCt

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

LocRec GameBoardClass::GetBoardSize()
{
	return boardSize;

} // END GetBoardSize
