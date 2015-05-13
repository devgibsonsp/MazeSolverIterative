//Author: Steven
//Date: 9/24/2012
//Last Modified: 11/8/2014
//Purpose: Create a 2D dynamic array to be used as a gameboard
//Error Handling: None
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Summary of Methods
//  **NOTE parameters are documented below
//
// 	GameBoardClass      - Non default constructor, initializes game board to
//                        specifications detailed in an input file
//
//  Retrieve            - Retrieves a cell from the board given a location
//
// 	void SetCellCt      - Sets the number in the cell given a location & direction
//
//  LocRec GetBoardSize - Returns the size of the board
//
// *See method pre/post for more details
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Cell.h"	  // for cell records
#include "location.h" // For location records
#include <fstream>    // For file i/o

#include <Windows.h>

// Constant declarations
const int MAX_ROWS = 5;    // Max rows for default constructor
const int MAX_COLS = 5;    // Max columns for default constructor
const int BORDER = 2;      // Adds border around gameBoard



// typedef statements
typedef CellRec** GameBoardPtr;

using namespace std;


class GameBoardClass
{

  public:
	// CONSTRUCTOR
	GameBoardClass(ifstream& din);
	//Pre: List has been instantiated & an input file variable has been passed
	//Post: Initializes a game board with file specified values

	CellRec Retrieve(LocRec tempLoc);
	//Pre: A location record has been passed
	//Post: Retrieves a cell from the board given a location

	void SetCellDirection(LocRec tempLoc, int direction);
	//Pre: A location record & direction value have been passed
	//Post: Sets the number in the cell given a location & direction
	
	/**/
	LocRec GetBoardSize();
	//Pre:
	//Post:

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// METHODS


  private:
	GameBoardPtr gameBoard;    		//stores the items in the list
	LocRec boardSize;               // Size of board

}; // END Gameboard
