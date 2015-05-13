// PROJECT: TheMaze
// IMPLEMENTATION FILE : stack.cpp
// This file contains the implementation of a dynamically allocated stack.
#include "stack.H"

 
//***************************************************************************
//*																			*
//*				declare struct from forward declaration						*
//*																			*
//***************************************************************************
struct node
{
	ItemType data; // value to store data in a pointer
	 node* next;   // Node to enable list to be linked
};



//***************************************************************************
//*																			*
//*				constructors, destructor, and copy constructor				*
//*																			*
//***************************************************************************

//constructor
StackClass::StackClass()
{
	stack = NULL; // Defaulting the external pointer to NULL;



}  // end default constructor




//copy constructor
StackClass::StackClass(const StackClass& orig) 
{
	
	stack = NULL; // Defaulting the external pointer to NULL;

	operator=(orig); // Performing a deep copy of the applying operator



} // end copy constructor



//destructor

StackClass::~StackClass() 
{
	// Clearing the list and returning memory to heap
	Clear(); 

}//end destructor


//***************************************************************************
//*																			*
//*				observer predicators										*
//*																			*
//***************************************************************************
bool StackClass::IsEmpty() const
{
	// true if stack has nothing in it
  return(stack == NULL);

}  // end IsEmpty



bool StackClass::IsFull() const
{
	// stack is never full, always false
	return(false);

} // end IsFull


//***************************************************************************
//*																			*
//*				observer accesor											*
//*																			*
//***************************************************************************


ItemType StackClass::Retrieve() const
{
	if(!IsEmpty())
	{
		// If the stack is not empty, return data at the top of the stack
		return stack -> data;

	} // END if
	else
	{
		// If the stack is empty, throw return on empty stack exception
		throw(EmptyStackRetrieve());

	} // END else


}  // end Retrieve




//***************************************************************************
//*																			*
//*							Mutators										*
//*																			*
//***************************************************************************



void StackClass::Push(/*in*/ItemType newItem)
								
{				

	if(IsEmpty())
	{
		// If the stack is empty, add a new value to the top of the stack
		stack = Allocate();

	} // END if
	else
	{
		// temporary pointer to top of stack
		node* temp = stack;

		// stack points to a new value
		stack = Allocate();
		
		// stack's new value points to temp, which
		// reconnects the list
		stack -> next = temp;

	} // END else

	stack -> data = newItem;

}// end Push




void StackClass::Pop()
{
		if(!IsEmpty())
		{
			// If the list is not empty...

			// Temporary pointer points to the head
			node* temp = stack;

			// Head points to next value in stack
			stack = stack -> next;

			// temp is deleted, deleting the top value from stack
			delete temp;

		} // END if

}  // end Pop





void StackClass::Clear() 
{
	// Clearing the list and returning memory to heap
	while(!IsEmpty())
	{
		// If the list is not empty, pop the current value
		// at the top of the stack off
		Pop();

	} // END while

} // END Clear





void StackClass::operator =(const StackClass& orig)
{
	Clear(); // Clearing the list being applied to

	// Temporary stack variable
	StackClass tempStack;

	// Temporary pointer to applying stack
	node* temp = orig.stack;

	// While temp does not point to NULL, push all values
	// from the applying stack into the temporary stack
	while (temp != NULL)
	{
		
		tempStack.Push(temp->data);

		temp = temp->next;

	} // END while






	temp = tempStack.stack;

	stack = Allocate();

	// This stack is in reverse order,
	// pop all values from tempStack & push into
	// stack being applied to to copy values
	while (!tempStack.IsEmpty())
	{
		Push(tempStack.Retrieve());
		
		tempStack.Pop();


	} // END while


} // END operator=



//protected method
node* StackClass::Allocate()
{

	try
	{
		// If the stack is not out of memory...


		node* temp = new node; // Create a temporary new node
		temp ->next = NULL; 

		// temp will be added to the top of the stack
		return temp;
	}
	catch(bad_alloc)
	{
		// If the stack is out of memory, throw out of memory exception
		throw(OutOfMemory());
	}

}







