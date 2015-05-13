//Project OrdListTest
//FileName : exceptions.h
//Author: Steven Gibson
//Modifications:  N/A
//Purpose : This file contains the implementation of exceptions
//          for an ordered list
//-Exception List----------------------------------------------------------------
//    OutOfMemory         - Thrown if the program runs out of memory
//    EmptyListDelete     - Thrown if delete is called on an empty list
//    DuplicateInsert     - Thrown if inserting a key already present in the list
//    EmptyListRetrieve   - Thrown if trying to retrieve an item from an empty list
//    MovePastEOL         - Thrown if trying to move currPos past the bounds of the list
//--------------------------------------------------------------------------------


class OutOfMemory
{ 
	public:
		OutOfMemory(){} // OutOfMemory constructor
};

//--------------------------------------------------------------------------------

class EmptyStackDelete
{ 
	public:
		EmptyStackDelete(){} // EmptyStackDelete constructor
};

//--------------------------------------------------------------------------------

class DuplicateInsert
{ 
	public:
		DuplicateInsert(){} // DuplicateInsert constructor
};

//--------------------------------------------------------------------------------

class EmptyStackRetrieve
{ 
	public:
		EmptyStackRetrieve(){} // EmptyyStackRetrieve constructor
};

//--------------------------------------------------------------------------------

class MovePastEOL
{ 
	public:
		MovePastEOL(){} // MovePastEOL constructor
};

//--------------------------------------------------------------------------------

