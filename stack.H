//PROJECT: TheMaze
//Filename : stack.h
//Specification File : StackClass
//
//  
// 
//***************************************************************************
//  The public methods are: 
//    StackClass();  		: prepares stack for usage.	
//
//	  ~StackClass();    	: returns all dynamically allocated memory to heap	
//
//	  StackClass(const StackClass& orig);  : creates a deep copy of the object 	
//		
//    bool IsEmpty() const : returns true if stack has no elements. 
//
//    bool IsFull() const  : returns true if stack has no empty spaces.
//
//    void Push(ItemType newItem);	adds newItem to top of stack
//
//    void Pop();		Removes top item from stack.
//
//    ItemType Retrieve() const;  returns item at top of stack		
//		 DOES NOT REMOVE TOP ELEMENT!!!!  STACK IS UNCHANGED!!!
//	 
//	  void Clear();
//
//	  virtual void operator =(const StackClass& orig);
//
//**********************************************************************************

#include "ItemType.h"
#include "exceptions.h"



//forward declaration of struct

struct node;



//class declaration
class StackClass

{
  public:

    //constructors and destructors
			
	// PRE: None
	// POST: Sets PDMs to their initial state
	StackClass();  		// default constructor
	
	// PRE: An object must be instantiated
	// POST: Returns dynamically allocated memory back to heap
	~StackClass();		//destructor

	// PRE: applying operator passed
	// POST: creates deep copy of applying operator
	StackClass(const StackClass& orig); //copy constructor
	

	
   // ADT stack operations:


	// PRE: An object must be instantiated
	// POST: returns true if stack has no elements. 
	bool IsEmpty() const;      

	// PRE: An object must be instantiated
	// POST: returns true if stack has no empty spaces.
	bool IsFull() const;	  

	// PRE: An item to be pushed has been passed
	// POST: adds newItem to top of stack
	void Push(ItemType newItem);

	// PRE: An object must be instantiated
	// POST: Removes top item from stack.
	void Pop();			

	// PRE: An object must be instantiated
	// POST: returns item at top of stack	
	// EXCEPTIONS THROWN: EmptyStackRetrieve 
	// when attempting to retrieve from empty stack
	ItemType Retrieve() const;	
   
	// PRE: An object must be instantiated
	// POST: Clears the stack of all values
	void Clear();


//overloaded operators
	// PRE: Applying stack passed
	// POST: Creates a deep copy of the applying stack
	virtual void operator =(const StackClass& orig);
   
	

 private:  //pdm

   //stack declaration 
   node* stack;

    
protected:
	// PRE: An object must be instantiated
	// POST: New memory allocated to the stack for values
	// EXCEPTIONS THROWN: OutOfMemory when attempting to
	// allocate memory when program runs out of memory
   node* Allocate();


};  // end StackClass

