#ifndef LOCATION_H  // Compiler directive to allow
#define LOCATION_H  // redefinition of LocRec

// Project: 
// FILENAME: Location.h
// AUTHOR: Steven Gibson
// Date: 9/24/2014
// last Modified: 10/5/2014
// Purpose: Provides the specifications for a Location record. 

struct LocRec
{
	int row; // Game board cell row
	int col; // Game board cell column

}; // END LocRec

#endif // End compiler directive