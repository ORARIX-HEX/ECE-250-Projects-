/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  ohenriet @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 * Tasnim Alam (t7alam@uwaterloo.ca) student number 20480972 help in debugging 
 *   double_sentinel_list and double_node class was borrowed from Ko Liu (koliu @uwaterloo.ca)
 * Varun Batta Student ID 20454511 vbatta@uwaterloo.ca helped with debugging copy constructor 
 *****************************************/

/**********************************************************
 * YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
 * Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
 *   1.  Change which header file is is included.
 *   2.  Change the type of the member variable 'list'.
 *   3.  Update the ostream<< operator so that it prints
 *       out the entries in your implementation.
 * 
 **********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
#include "Exception.h"
#include <iostream>
/*
 * Class_name
 *
 * Henrietta Odchuko Odiete 
 * 2015-03-02
 *
 *
 * Member Variables:            The class has three memeber variables 
 *  type variable              Double_sentinel_list<Type *> list; -- the stack is implemented with a doubly linked list from project 1
 *							   int itop;- points to the top of the stack 
 *							   int stack_size; - is the number of arguments in the stack 
 *                             
 *                             Any restrictions on its value.
 *
 *
 *
 * Class Constants:            // static const variables
 *  type variable        What this constant does.
 *
 * Member Functions (Accessors):
 *      bool empty() const; -- reurns true if the stack is empty 
 *		int size() const; -- returns the entry count of the stack
 *		int list_size() const; -- returns list size 
 *  
 *
 * Member Functions (Mutators):
 *  
 *void swap( Linked_stack & );
 *		Linked_stack &operator=( Linked_stack )
 *		void push( Type const &obj ); -- adds argument to the top of the stack 
 *		Type pop(); -- pops the element at the top of the stack and 
 *
 *
 * Bugs:           //  segmentation faults may be a compiler issue 
 * Todo:           //  possible a bug found in push function required a clean up 
 * References:     // if applicable (very useful)
 */
template <typename Type>
class Linked_stack {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_sentinel_list<Type *> list;
		int itop;
		int stack_size;

	public:
		Linked_stack();
		Linked_stack( Linked_stack const & );
		~Linked_stack();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type top() const;

		void swap( Linked_stack & );
		Linked_stack &operator=( Linked_stack );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_stack<T> const & );
};

template <typename Type>
Linked_stack<Type>::Linked_stack():
stack_size( 0 ) {
	// Empty constructor
	

}

template <typename Type>
Linked_stack<Type>::Linked_stack( Linked_stack const &stack ):
stack_size( 0) 

{
	// returns out of the function if stack is empty 
	if(stack.empty())
	{
		return;
	}
	// loops from the last node in the stack to the head sentinel 
	Double_node <Type *> *ptr=stack.list.tail();
	while(ptr!=stack.list.head()->next())
	 {
		ptr = ptr->previous();
	 for( int i=0; i<ARRAY_CAPACITY; ++i )
	 {
        push(ptr->retrieve()[i]);

	 } 
	 }
	 stack_size=stack.size();
	 itop= stack.itop;

}

template <typename Type>
Linked_stack<Type>::~Linked_stack() {
	while(!empty())
	{
		pop();
	}

	itop=0;
	stack_size=0;
}

template <typename Type>
bool Linked_stack<Type>::empty() const {
	// returns stack size 
	return stack_size==0;
	
}

template <typename Type>
int Linked_stack<Type>::size() const {
	// returns the number of arguments in the stack 
	return stack_size;
	
}

// Do not change this implementation

template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
}

template <typename Type>
Type Linked_stack<Type>::top() const {
	// enter your implementation here
	if(list.empty())
	{
		throw underflow();
	}
	return list.front()[itop];

}

template <typename Type>
void Linked_stack<Type>::swap( Linked_stack<Type> &stack ) {
	std::swap( list, stack.list );
	std::swap( stack_size, stack.stack_size );
	std::swap( itop, stack.itop );
}

template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=( Linked_stack<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
void Linked_stack<Type>::push( Type const &obj ) {
	// enter your implementation here
	if(list.empty()|| itop==ARRAY_CAPACITY-1)
	{ 
		
		if(list.empty())
		{
			stack_size = 1;
		}
		else
		{
			++stack_size;
		}

		Type *new_array = new Type [ARRAY_CAPACITY];
		list.push_front(new_array);
		itop=0;
		new_array[0]=obj;
		
	}
   else
   {
    ++itop;
   	list.front()[itop]=obj;  
   	++stack_size;
    
   }
   return;
}

template <typename Type>
Type Linked_stack<Type>::pop() {
	// enter your implementation here
	if (list.empty()){
		throw underflow();
	}
	Type old_itop= list.front()[itop];// top of the stack is at the back 

	--itop;
	--stack_size;

	
	if (itop<0 ){ 
      Type *popped_array=list.front();
       //list.front();
       itop= ARRAY_CAPACITY-1;
       list.pop_front();
       delete [] popped_array;

      }
		else if(stack_size==0)
		{
	      itop=-1;
	      Type *popped_array=list.front();
          list.pop_front();
          delete [] popped_array;
        }
        else
        {
        	list.front()[itop+1]=0; 
        }
	

	return old_itop;
	
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_stack<T> const &stack ) {
	if ( stack.list.size() == 0 ) {
		out << "->0";
	} else if ( stack.list.size() == 1 ) {
		out << "->[ ";

		for ( int i = 0; i <= stack.itop; ++i ) {
			out << stack.list.front()[i] << " ";
		}

		out << "]->0";
	} else {
		out << "->";

		for ( Double_node<T *> *ptr = stack.list.head()->next(); ptr != stack.list.tail(); ptr = ptr->next() ) {
			out << "[ ";

			if ( ptr == stack.list.head()->next() ) {
				for ( int i = 0; i <= stack.itop; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else {
				for ( int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
