// ____________________________________________________________________________________________________________________
//| AUTHOR: Steven Gibson                                                                                              |
//| PROJECT NAME: TheMaze                                                                                              |
//| FILENAME: testClient.cpp                                                                                           |
//| DATE: 10/30/2014                                                                                                   |
//| LAST MODIFIED: 11/9/2014                                                                                           |
//| STATEMENT OF PURPOSE: This program reads in values from a file to create a maze. The program then processes        |
//|                       all possible solutions to the maze and outputs them to a nicely formatted output file.       |
//|                                                                                                                    |
//| INPUT: The program prompts the user for an input file name. This input file is read into the program. The first    |
//|        value in the input file is read in as the size of the board, the rest of the values correspond to X Y       |
//|        coordinates on a grid, used to determine where the walls of the maze will be.                               |
//|                                                                                                                    |
//| PROCESSING: Program attempts to open an input file specified by the user. If the file opens, the avlues in the     |
//|             file are processed to created the maze walls in the game board. After the game board has been created, |
//|             the program simulates the movement of a player through the maze. Each time a player moves, the         |
//|             direction of movement is recorded and placed at the top of a stack. Players move through the maze in a |
//|             particular direction until they are blocked, in which case they then choose a new direction to travel. |
//|             Players never travel in the same location they have already been. If a player cannot move, the player  |
//|             moves backwards until it can, each time a player moves backwards, the value corresponding with the last|
//|             move is popped off the stack. If the player moves back to the starting position, the game terminates.  |
//|             Every time the player reaches the end of the maze, the solution to the maze that the player has found  |
//|             is output to the specified output file. If there are no solutions to the maze, a message highlighting  |
//|             that will be output instead. Upon completion of the solution finding, the input and output files are   |
//|             closed and the program terminates.                                                                     |
//|                                                                                                                    |
//| OUTPUT: Program outputs solutions to the maze to the specified output file. Each solution lists the directions     |
//|         taken to solve the maze given a particular path and a map of the solution. If the user chooses, a map of   |
//|         the solution will also be output to the screen.                                                            |
//|                                                                                                                    |
//| ASSUMPTIONS:                                                                                                       |
//|   1. Files to be used will be present in the solution folder                                                       |
//|   2. Players will always enter at the top left corner of the maze.                                                 |
//|   3. Players will always exit at the bottom right corner of the maze with a southward movement.                    |
//|   4. Size of board must be at least a 0 by 0.                                                                      |
//|                                                                                                                    |
//| EXCEPTION/ERROR HANDLING:                                                                                          |
//|   1. Error message output if user attempts to open a file that does not exist.                                     |
//|   2. Error message output if user attempts to open a file with an invalid format (The filename must contain only   |
//|      letters and a period and 3 letters after the period).                                                         |
//|                                                                                                                    |
//| METHOD/FUNCTION SUMMARY:                                                                                           |
//|  **NOTE parameters are documented below                                                                            |
//|                                                                                                                    |
//|     void MoveForward         -Current position will be moved forward based on direction and the direction will be  |
//|                               added to the to of the stack.                                                        |
//|                                                                                                                    |
//|     void MoveBackward        - Current position is moved back one and a value is popped off the stack.             |
//|                                                                                                                    |
//|     void Print               - A list of movements through the maze and a picture of the solution output to file.  |
//|                                                                                                                    |
//|     void MovePosition        - Current location has been changed based on direction of movement.                   |
//|                                                                                                                    |
//|     void PrintBoardConsole   - Current state of the board is output to console.                                    |
//|                                                                                                                    |
//|     void PrintBoardFile      - Current state of the board is output to console.                                    |
//|                                                                                                                    |
//|     LocRec SetLoc            - Sets location to specified values.                                                  |
//|                                                                                                                    |
//|     bool ValidateMove        - Returns true if the direction of movement is valid.                                 |
//|                                                                                                                    |
//|     bool ValidFile           - A bool will be returned, true if the file name is valid.                            |
//|                                                                                                                    |
//|     bool MenuSelect          - If true, function returns screenOut, indicating the user wants output to screen.    |
//|                                                                                                                    |
//|     void OutputGraphic       - Flashing completion message is output to the console window.                        |
//|                                                                                                                    |
//|     void MenuMessage         - Outputs all preset maze file names to the console window.                           |
//|                                                                                                                    |
//| *See function pre/post for more information                                                                        |
//|____________________________________________________________________________________________________________________|






//------Libraries-----------------------------------
#include "gameboard.h" // For GameBoardClass objects
#include "stack.H"     // For StackClass objects
#include <windows.h>   // For text color attributes
#include <iostream>    // For basic i/o
#include <iomanip>     // For console manipulation
#include <string>      // For string datatype
#include <cctype>      // For use of toupper

using namespace std;




// Possible color values               *Three lines to prevent page wrap
enum ColorEnum{ BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	            DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
				LIGHTMAGENTA, YELLOW, WHITE };

//------Function prototypes--------------------------------------------------------------------
void MoveForward(/*IN/OUT*/StackClass& tempStack,     // Address of the current stack holding all movements in maze
	             /*IN/OUT*/GameBoardClass& tempBoard, // Address of gameBoard object initialized to current maze
				 /*IN/OUT*/int& direction,            // Address of direction of movement
				 /*IN/OUT*/LocRec& currLoc,           // Address of current location in the maze 
				 /*IN/OUT*/int& solutionCt,           // Address of Amount of solutions for maze
				 /*IN/OUT*/ofstream& dout,            // Address of Output file variable
				 /*IN*/int numMoves,                  // Total number of moves performed for a solution
				 /*IN/OUT*/bool& noSolutions);        // Address of boolean flag, true if no solutions



void MoveBackward(/*IN/OUT*/StackClass& tempStack,     // Address of the current stack holding all movements in maze
	              /*IN/OUT*/GameBoardClass& tempBoard, // Address of gameBoard object initialized to current maze
				  /*IN/OUT*/int& direction,            // Address of direction of movement
				  /*IN/OUT*/LocRec& currLoc);          // Address of current location in the maze 



void Print(/*IN*/int numMoves,                         // Total number of moves performed for a solution
	       /*IN*/StackClass tempStack,                 // The current stack holding all movements in maze
		   /*IN/OUT*/ofstream& dout,                   // Address of Output file variable
		   /*IN/OUT*/int& solutionCt);                 // Address of Amount of solutions for maze



void MovePosition(/*IN/OUT*/LocRec& currLoc,           // Address of current location in the maze
	              /*IN*/int direction);                // Direction of movement


void PrintBoardConsole(/*IN*/GameBoardClass tempBoard);// GameBoard object initialized to current maze


void PrintBoardFile(/*IN*/GameBoardClass tempBoard,    // GameBoard object initialized to current maze
	                /*IN/OUT*/ofstream& dout);         // Address of output file variable


LocRec SetLoc(/*IN*/int num1,                          // Row coordinate
	          /*IN*/int num2);                         // Column coordinate



bool ValidateMove(/*IN*/LocRec currLoc,                // Current location in the maze
	              /*IN*/GameBoardClass tempBoard,      // GameBoard object initialized to current maze
				  /*IN*/int direction);                // Direction of potential movement



bool ValidFile(/*IN*/string inFileName);               // Input file name



bool MenuSelect(/*IN*/char menuOption);                // Menu option



void OutputGraphic();



void MenuMessage();



//---------------------------------------------------------------------------------------------





//------Constant declarations------------------------------------------------------------------

const string OUTPUT_OPTION = "Output to the screen? (Greatly reduces computation speed) \n [Y]es \n [N]o \n"; // Options prompt msg


const string NO_PATHS = "There are no valid paths through this maze...";   // Completion with no solutions message

const string INPUT_MSG = "Please enter the input file name\nPresets:";     // Input prompt message

const string INVALID_FILE_ERR = "Invalid file name format!";               // Input file invalid format error message

const string COMPLETE_MSG = "Path finding complete!";                      // Maze completion message


const string SOLUTIONS_MSG = " Solution(s) found!";  // Label for number of solutions found

const string OUT_FILE_NAME = "Solutions.out";        // Name of the output file

const string FNF_ERR = "File not found!";            // Input file not found error message

const int LWR_ASCII_LETT_RANGE = 65;                 // Lower range for ASCII characters which are uppercase letters

const int UPP_ASCII_LETT_RANGE = 90;                 // Upper range for ASCII characters which are uppercase letters

const int FILE_TYPE_MAX_LETTERS = 3;                 // Maximum amount of letters that can occur in the file type (ex .dat has 3)

const string SOLUTION_LBL = "Solution #";             // Label for solution output

const string PRESET_ONE = "Maze.dat";                // Preset maze 1

const string PRESET_TWO = "GiantMaze.dat";           // Preset maze 2

const string PRESET_THREE = "NoExit.dat";            // Preset maze 3
 
const string PRESET_FOUR = "TwoRooms.dat";           // Preset maze 4

const string PRESET_FIVE = "Loopy.dat";              // Preset maze 5


const string CLEAR_COMMAND = "cls";   // Command to clear console window

const string QUAD_END = "\n\n\n\n";   // Quandruple character end lines

const string DOUBLE_END = "\n\n";     // Double character end lines

const int FLASH_DELAY = 250;          // Delay on flash

const int NUM_FLASHES = 10;           // Flash count when graphic completion message output

const int ASCII_PERIOD = 46;          // ASCII value for a period

const char YES_OPTION = 'Y';          // Yes identifier

const char NO_OPTION = 'N';           // No identifier

const string OUT_SOUTH = ". South";   // South formatted output

const string OUT_NORTH = ". North";   // North formatted output

const string OUT_EAST = ". East";     // East formatted output

const string OUT_WEST = ". West";     // West formatted output


const char WALL = '|';               // Character to represent a wall

const char SPACE = ' ';              // Character space

const char DOWN_POINT = 'v';         // Character to represent a downward movement

const char RIGHT_POINT = '>';        // Character to represent a right movement

const char LEFT_POINT = '<';         // Character to represent a left movement

const char UP_POINT = '^';           // Character to represent a upward movement

const char EXIT = 'E';               // Character to represent the exit


//---------------------------------------------------------------------------------------------










void main()
{

	

	//---Local variable declarations------------------
	ifstream din;              // Input file variable
	ofstream dout;             // Output file variable
	StackClass directionStack; // Stack to record the directions of player through maze
	LocRec currLoc;            // location record to store current location

	string inFileName;         // User defined file name

	bool noSolutions = true;   // True if no solutions are found in the maze
	bool screenOut = false;    // True if maze is output to screen
	bool isValid = false;      // True if valid move is being performed
	bool popping = false;      // True when stack is popping
	bool endSim = false;       // True when end of simulation is reached
	
	int solutionCt = 0;        // Counts the amount of solutions to the 
	int direction = 0;         // Current direction of movement
	int numMoves = 0;          // Number of moves per solution


	char menuOption = SPACE; // User menu option
	//------------------------------------------------



	// Printing menu to screen
	MenuMessage();

	// Reading in the input file name
	cin >> inFileName;

	// Clearing the screen
	system(CLEAR_COMMAND.c_str());


	// Attempting to open the input file
	din.open(inFileName.c_str());



	if(ValidFile(inFileName) && din)
	{
		// Opening output file
		dout.open(OUT_FILE_NAME.c_str());

		// Determining whether to output to screen
		screenOut = MenuSelect(menuOption);

		// Initializing a gameBoard object
		GameBoardClass gameBoard = GameBoardClass(din);


		// Starting Position
		currLoc = SetLoc(0, 1);

		/* Places the player right outside the board so that they may move in to the initial starting location */


		while (!endSim) // While the simulation is still running
		{



			// Resetting isValid to false
			isValid = false;



			if(!popping)
			{


				// If not popping, direction gets current position direction++
				direction = gameBoard.Retrieve(currLoc).direction + 1;



			} // END if
			else
			{


				// Increment direction
				direction++;



				// Reset popping to false after pop
				popping = false;


			} // END else



			
			while(!isValid)
			{



				// If not a valid direction
				if(direction > NORTH)
				{


					// Move backward (pop)
					MoveBackward(directionStack, gameBoard, direction, currLoc);


					// Decrementing number of moves to reflect pop
					numMoves--;


					// isValid set to true to reflect a valid move
					isValid = true;



					// Popping set to true to reflect moving backwards in maze
					popping = true;




				} // END if
				else if (ValidateMove(currLoc, gameBoard, direction) && currLoc.row >= INVALID)
				{


					// isValid set to true to reflect a valid move
					isValid = true;

					// Incrementing number of moves to reflect push
					numMoves++;



					// Moving forward (push)
					MoveForward(directionStack, gameBoard, direction, currLoc, solutionCt, dout, numMoves, noSolutions);



				} // END else if
				else if (currLoc.row == 0 && currLoc.col == 1)
				{


					// If where you started, end the simulation
					endSim = true;



					// isValid set to true to reflect a valid move
					isValid = true;



				} // END else if
				else
				{
					// Incrementing direction to try a new direction of movement
					direction++;


				} // END else


			} // END while


			// If screen output has been selected...
			if(screenOut)
			{

				// Printing solution to console window
				//gameBoard.PrintSolution();
				PrintBoardConsole(gameBoard);

				Sleep(40);
				// Clearing screen
				system(CLEAR_COMMAND.c_str());


			} // END if

		} // END while

		if(noSolutions)
		{

			// If no solutions, output no solutions message
			dout << NO_PATHS << endl;



		} // END if
		
		if(screenOut)
		{

			// OUTPUT flashing complete message
			OutputGraphic();



		} // END if
		else
		{

			// Output complete message
			cout << COMPLETE_MSG << endl;



		} // END else


		cout << solutionCt << SOLUTIONS_MSG << endl;

		// Closing the input & output files
		dout.close();
		din.close();



	} // END if
	else if(!din)
	{

		// File not found error
		cout << FNF_ERR << endl;



	} // END else if
	else
	{

		// Invalid file format
		cout << INVALID_FILE_ERR << endl;



	} // END else


} // END main






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: the current location and two integers passed to function.                            |
//|  POST: Sets location to specified values.                                                  |
//|____________________________________________________________________________________________|
LocRec SetLoc(/*IN*/int num1,            // Row coordinate
	          /*IN*/int num2)            // Column coordinate
{
	LocRec tempLoc;

	tempLoc.row = num1;
	tempLoc.col = num2;

	return tempLoc;

} // END SetLoc






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: A game board, direction of movement, & the current location have been passed.        |
//|  POST: Returns true if the direction of movement is valid.                                 |
//|____________________________________________________________________________________________|
bool ValidateMove(/*IN*/LocRec currLoc,           // Current location in the maze
	              /*IN*/GameBoardClass tempBoard, // GameBoard object initialized to current maze
				  /*IN*/int direction)            // Direction of potential movement
{
	// Local variable declarations
	bool isValid = false;
	int tempCt;

	switch (direction)
	{
		case NORTH: 
			currLoc.row -= 1;
			tempCt = tempBoard.Retrieve(currLoc).direction; break;
		case SOUTH:
			currLoc.row += 1;
			tempCt = tempBoard.Retrieve(currLoc).direction; break;
		case EAST:
			currLoc.col += 1;
			tempCt = tempBoard.Retrieve(currLoc).direction; break;
		case WEST:
			currLoc.col -= 1;
			tempCt = tempBoard.Retrieve(currLoc).direction; break;
	}

	// If the direction of movement is either to an empty space or a victory space, then it is valid
	if (tempCt == EMPTY || tempCt == VICTORY)
	{
		isValid = true;
	}

	return isValid;
}






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: A location record storing the current position's address & the direction to move     |
//|       have been passed to the function.                                                    |
//|  POST: Current location has been changed based on direction of movement.                   |
//|____________________________________________________________________________________________|
void MovePosition(/*IN/OUT*/LocRec& currLoc, // Address of current location in the maze
	              /*IN*/int direction)       // Direction of movement
{
	// Given a current position & a direction of movement, increment the current location in that direction

	switch (direction)
	{
		case NORTH: currLoc.row -= 1; break;
		case SOUTH: currLoc.row += 1; break;
		case EAST: currLoc.col += 1; break;
		case WEST: currLoc.col -= 1; break;

	} // END switch

} // END MovePosition






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: The number of moves that have occurred, the number of solutions that have been found |
//|       & a StackClass object have been passed to the function.                              |
//|  POST: A list of movements through the maze and a picture of the solution output to file.  | 
//|____________________________________________________________________________________________|
void Print(/*IN*/int numMoves,         // Total number of moves performed for a solution
	       /*IN*/StackClass tempStack, // The current stack holding all movements in maze
		   /*IN/OUT*/ofstream& dout,   // Address of Output file variable
		   /*IN/OUT*/int& solutionCt)  // Address of Amount of solutions for maze
{
	// Local variable declarations
	int ct = 1;           // Initializing a counting variable
	StackClass flipStack; // Temporary stack to flip values
	ItemType tempItem;    // Temporary item to store values from stack

	dout << SOLUTION_LBL << solutionCt << endl;

	for (int i = 0; i < numMoves; i++)
	{
		// Retrieving the item from the stack
		tempItem = tempStack.Retrieve();

		// Pushing the item from the original stack to the new stack to flip the values
		flipStack.Push(tempItem);
		
		// Popping value off of the temporary stack
		tempStack.Pop();

	} // END for
 
	// Popping all values off of the new stack and outputting them
	for (int i = 0; i < numMoves; i++)
	{
		tempItem = flipStack.Retrieve();

		flipStack.Pop();

		switch (tempItem.key)
		{
			case SOUTH:	dout << ct << OUT_SOUTH << endl; break;
			case NORTH:	dout << ct << OUT_NORTH << endl; break;
			case EAST:	dout << ct << OUT_EAST << endl; break;
			case WEST:	dout << ct << OUT_WEST << endl; break;

		} // END switch

		ct++;

	} // END for

} // END print






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: a StackClass & GameBoardClass object has been initialized and their addresses passed |
//|       to the function. Current location, current direction of movement, solution count     |
//|       addresses have been passed.                                                          |
//|  POST: Current position will be moved forward based on direction and the direction will be |
//|        added to the to of the stack.                                                       |
//|____________________________________________________________________________________________|
void MoveForward(/*IN/OUT*/StackClass& tempStack,     // Address of the current stack holding all movements in maze
	             /*IN/OUT*/GameBoardClass& tempBoard, // Address of gameBoard object initialized to current maze
				 /*IN/OUT*/int& direction,            // Address of direction of movement
				 /*IN/OUT*/LocRec& currLoc,           // Address of current location in the maze 
				 /*IN/OUT*/int& solutionCt,           // Address of Amount of solutions for maze
				 /*IN/OUT*/ofstream& dout,            // Address of Output file variable
				 /*IN*/int numMoves,                  // Total number of moves performed for a solution
				 /*IN/OUT*/bool& noSolutions)         // Address of boolean flag, true if no solutions
{
	ItemType tempItem;

	// Setting the cell direction
	tempBoard.SetCellDirection(currLoc, direction);

	// Moving to the new position
	MovePosition(currLoc, direction);

	tempItem.key = direction;

	// Pushing the new direction to the stack
	tempStack.Push(tempItem);

	// If the current location is on the victory square, solution has been found
	if (tempBoard.Retrieve(currLoc).direction == VICTORY)
	{
		// Incrementing solution count
		solutionCt++;

		// Printing the solution
		Print(numMoves, tempStack, dout, solutionCt);
		//tempBoard.OutputSolution(dout);
		PrintBoardFile(tempBoard,dout);
		dout << DOUBLE_END;

		// Flagging noSolutions as false to indicate a solution has been found
		noSolutions = false;

	} // END if

} // END MoveForward






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: a StackClass & GameBoardClass object has been initialized and their addresses passed |
//|       to the function. Current location & current direction of movement addresses passed   |
//|       to the function.                                                                     |
//|  POST: Current position is moved back one and a value is popped off the stack.             |
//|____________________________________________________________________________________________|
void MoveBackward(/*IN/OUT*/StackClass& tempStack,      // Address of the current stack holding all movements in maze
	              /*IN/OUT*/GameBoardClass& tempBoard,  // Address of gameBoard object initialized to current maze
				  /*IN/OUT*/int& direction,             // Address of direction of movement
				  /*IN/OUT*/LocRec& currLoc)            // Address of current location in the maze 
{
	// Grabbing the item from the top of the stack
	ItemType tempItem = tempStack.Retrieve();

	// Popping the value off of the top of the stack
	tempStack.Pop();

	// Setting direction to the old direction indicated by the stack
	direction = tempItem.key;

	// Based on the previous direction of travel, go the opposite way!
	switch(direction)
	{
		case NORTH: MovePosition(currLoc, SOUTH); break;
		case SOUTH: MovePosition(currLoc, NORTH); break;
		case EAST: MovePosition(currLoc, WEST); break;
		case WEST: MovePosition(currLoc, EAST); break;

	} // END switch


	// Setting the current location to empty as currLoc moves backwards
	tempBoard.SetCellDirection(currLoc, EMPTY);


} // END MoveBackward






//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: A file name has been passed to the function.                                         |
//|  POST: A bool will be returned, true if the file name is valid.                            |
//|____________________________________________________________________________________________|
bool ValidFile(/*IN*/string inFileName) // Input file name
{
	// Local variable declarations
	int CharCt = 0;                        // Counter to keep track of current position while checking string
	int periodCt = -1;                      // Counter to keep track of how many characters have been passed since finding a period
	int nameSize = inFileName.size();      // Storing the size of the input file name
	bool foundPeriod = false;              // Boolean flag true if period is found

	// Iterating through string and making all characters upper case
	for (int i = 0; i < nameSize; i++)
	{
		inFileName[i] = toupper(inFileName[i]);

	} // END for

	// While the character count is less than the name size
	while(CharCt < nameSize)
	{
		
		if(inFileName[CharCt] == ASCII_PERIOD)
		{
			// If a period is found, flag true
			foundPeriod = true;

		} // END if
		else if ((inFileName[CharCt] > UPP_ASCII_LETT_RANGE) || (inFileName[CharCt] < LWR_ASCII_LETT_RANGE))
		{
			// If the range of the characters is incorrect and a period is not found, return false
			return false;

		} // END else if
		

		if(foundPeriod)
		{
			// Incrementing periodCt every iteration after a period is found
			periodCt++;

		} // END if

		// Incrementing character count
		CharCt++;

	} // END while

	// If the amount of characters after period is equal to the amount required, return true
	if(periodCt == FILE_TYPE_MAX_LETTERS)
	{
		return true;

	} // END if
	else
	{
		return false;

	} // END else

} // END validFile







//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: None.                                                                                |
//|  POST: Outputs all preset maze file names to the console window.                           |
//|____________________________________________________________________________________________|
void MenuMessage()
{
	cout << INPUT_MSG << endl
		<< SPACE << PRESET_ONE << endl
		<< SPACE << PRESET_TWO << endl
		<< SPACE << PRESET_THREE << endl
		<< SPACE << PRESET_FOUR << endl
		<< SPACE << PRESET_FIVE << endl;

} // END MenuMessage







//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: A character to be used as the menu option has been passed to the function.           |
//|  POST: If true, function returns screenOut, indicating the user wants output to screen.    |
//|____________________________________________________________________________________________|
bool MenuSelect(/*IN*/char menuOption) // Menu option
{
	bool screenOut = false; // Boolean flag, true if user desires screen output

	// Loop until a valid option has been selected
	do
	{

		// Output options (display to screen or not)
		cout << OUTPUT_OPTION;

		// Reading in menu option from the user
		cin >> menuOption;

		// Synchronize the input stream with whatever has been entered
		cin.sync();

		// Changing the menu option to upper case
		menuOption = toupper(menuOption);

		if (menuOption == YES_OPTION)
		{
			// If the user wants output...
			screenOut = true;

		} // END if

		// Clearing the screen
		system(CLEAR_COMMAND.c_str());

	} while (menuOption != YES_OPTION && menuOption != NO_OPTION);


	return screenOut;


} // END MenuSelect







//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: None.                                                                                |
//|  POST: Flashing completion message is output to the console window.                        |
//|____________________________________________________________________________________________|
void OutputGraphic()
{
	int color = YELLOW; // Initializing the color to yellow

	// Looping simulates flashing colors to the console window
	for (int i = 0; i < NUM_FLASHES; i++)
	{

		// Setting console text to initial color
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

		// Output centered completion message
		cout << QUAD_END << QUAD_END << setw(48) << COMPLETE_MSG << endl;
		
		Sleep(FLASH_DELAY); // Causing a delay in the console window

		system(CLEAR_COMMAND.c_str()); // Clearing the screen

		
		/* If color is black, switch to yellow,
		   if color is yellow, switch to black
		   to simulate flashing */
		   
		if (color == BLACK)
		{
			color = YELLOW;

		} // END if
		else
		{
			color = BLACK;

		} // END else

	} // END for

	// Setting the console window to white upon completion
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

} // END OutputGraphic







//---------------------------------------------------------------------------------------------






// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: a game board has been passed to the function.                                        |
//|  POST: Current state of the board is output to console.                                    |
//|____________________________________________________________________________________________|
void PrintBoardConsole(/*IN*/GameBoardClass tempBoard) // GameBoard object initialized to current maze
{
	// Local variable declarations
	LocRec boardSize = tempBoard.GetBoardSize(); // Getting the size of the game board
	LocRec tempLoc;        // location record to store values from the board
	int direction;         // stores current direction of movement
	int colorValue = BLUE; // Defaulting color value to blue

	// Setting console color to blue
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), colorValue );

	// Looping through board & outputting to screen
	for(int i = 0; i < boardSize.row; i++)
	{
		cout << setw(28) << SPACE;
		for(int j = 0; j < boardSize.col; j++)
		{
			tempLoc = SetLoc(i,j);
			direction = tempBoard.Retrieve(tempLoc).direction;

			// Changing direction pointer depending on direction of movement
			switch(direction)
			{
				case INVALID: 
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), WHITE );
					cout << WALL; break;
				case EAST:    cout << RIGHT_POINT; break;
				case WEST:    cout << LEFT_POINT; break;
				case SOUTH:   cout << DOWN_POINT; break;
				case NORTH:   cout << UP_POINT; break;
				case EMPTY:   cout << SPACE; break;
				case VICTORY: 
					SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), YELLOW );
					cout << EXIT; break;

			} // END switch


			// Incrementing color value
			colorValue++;

			if(colorValue == WHITE)
			{
				// Resetting color value to blue
				colorValue = BLUE;

			} // END if
			
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), colorValue );

		} // END for

		cout << SPACE << endl;

	} // END for

} // END PrintBoardConsole

//---------------------------------------------------------------------------------------------





// ____________________________________________________________________________________________
//|                                                                                            |
//|  PRE: a game board has been passed to the function.                                        |
//|  POST: Current state of the board is output to console.                                    |
//|____________________________________________________________________________________________|
void PrintBoardFile(/*IN*/GameBoardClass tempBoard, // GameBoard object initialized to current maze
	                /*IN/OUT*/ofstream& dout)       // Address of output file variable
{
	// Local variable declarations
	LocRec boardSize = tempBoard.GetBoardSize(); // Getting the size of the game board
	LocRec tempLoc;  // location record to store values from the board
	int direction;   // Defaulting color value to blue

	// Looping through board & outputting to file
	for(int i = 0; i < boardSize.row; i++)
	{
		for(int j = 0; j < boardSize.col; j++)
		{
			tempLoc = SetLoc(i,j);
			direction = tempBoard.Retrieve(tempLoc).direction;

			// Changing direction pointer depending on direction of movement
			switch(direction)
			{
				case EAST:    dout << RIGHT_POINT; break;
				case WEST:    dout << LEFT_POINT; break;
				case SOUTH:   dout << DOWN_POINT; break;
				case NORTH:   dout << UP_POINT; break;
				case EMPTY:   dout << SPACE; break;
				case VICTORY: dout << EXIT; break;
				case INVALID: dout << WALL; break;

			} // END switch

		} // END for

		dout << SPACE << endl;

	} // END for

} // END PrintBoardFile
