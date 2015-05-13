#ifndef CELL_H  // Compiler directive to allow
#define CELL_H  // redefinition of CellRec

// Project: 
// FILENAME: Cell.h
// AUTHOR: Steven Gibson
// DATE: 10/30/2014
// LAST MODIFIED: 11/9/2014
// PURPOSE: Provides the specifications for a Cell record. 

enum DirectionEnum{INVALID, EMPTY, SOUTH, EAST, WEST, NORTH, VICTORY};

struct CellRec
{
	int direction;

}; // END CellRec

#endif // End compiler directive