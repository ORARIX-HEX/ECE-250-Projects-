/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  ohenriet@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter| 2015
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
 *    -
 *****************************************/

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include "Exception.h"
 /*
 * Dynamic_queue
 *
 * Henrietta Ochuko Odiete
 * 2015-03-02
 *
 *
 * Member Variables:
 *  type variable        A head index int ihead, 
 *                       A tail index int itail 
 *                       A pointer to an instance of Type, Type *array, to be used as an array,
 *                       A counter int entry_count,                          
 *                       The initial capacity of the array, int initial_capacity,
 *                       The current capacity of the array, int array_capacity 
 *  
 * Class Variables:             intial_capacity       <- comments about comments :-)
 *  type variable       
 *                             //The initial capacity of the array, int initial_capacity,
 *
 * Class Constants:            // static const variables
 *  type variable        
 *
 * Member Functions (Accessors):
 *  
 *      Type head() const; -- returns the front of the queue
 *	    int size() const; -- returns the entry coun of the queue
 *	    bool empty() const; -- returns true if the queue is empty 
 *		int capacity() const; -- returns the size of the array 
 *  
 *
 * Member Functions (Mutators):
 * 
 *		
 *		Dynamic_queue &operator=( Dynamic_queue );
 *		void enqueue( Type const & );-- adds an object to the tail of the queue
 *		Type dequeue();-- removes the object at the end of the queue
 *		void clear();-- rests all the values in the array 
 *
 * Class Functions:            // static functions
 *   Dynamic_queue( int n = 10 ) -- assigns the member variables of the dynamic
 *  ~Dynamic_queue()-- deallocates memory for the dynaic_queue
 *   Dynamic_queue( Dynamic_queue const & )-- copies the entire queue
 *
 * Bugs:           // memory deallocation not equal to 0 and capacity 
 * Todo:           // if applicable
 * References:     // if applicable (very useful)
 */

template <typename Type>
class Dynamic_queue {
	private:
		int initial_capacity;
		int array_capacity;
		Type *array;
		int ihead;
		int itail;
		int entry_count;
		int current_position;
		// other integer member variables, as necessary

	public:
		Dynamic_queue( int = 10 );
		Dynamic_queue( Dynamic_queue const & );
		~Dynamic_queue();

		Type head() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Dynamic_queue & );
		Dynamic_queue &operator=( Dynamic_queue );
		void enqueue( Type const & );
		Type dequeue();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Dynamic_queue<T> const & );
};
/*
 * Dynamic_queue<Type>::Dynamic_queue( int n )
 * class constructor 
 * sets the inital capacity of the queue.
 *
 *
 * no returns;
 *  
 */
template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( int n ):
initial_capacity( std::max( n, 1 ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ),
ihead( 0 ),
itail( initial_capacity - 1 ),
entry_count( 0 ) {
	// Enter your implementation here.
	if(n<=0)
	{
		initial_capacity=1;
	}
	else 
	{
	 initial_capacity=n;
	}
/*
 * Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue )
 *
 * copy constructor of the class
 *
 * loops through the entire array and copies all its values 
 *
 * no returns;
 *  
 */
}

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue ):
initial_capacity( queue.initial_capacity ),
array_capacity( queue.array_capacity ),
array( new Type[array_capacity] ),
ihead( queue.ihead ),
itail( queue.itail ),
entry_count( queue.entry_count ) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure;
	// however, you must still copy the stored objects.
for (int i=0; i<capacity(); ++i){
	enqueue(array[i]);
}
}
/*
 * Dynamic_queue<Type>::~Dynamic_queue()
 *
 * class destructor 
 *
 * deallocates memory of the array 
 *
 * no returns 
 *  
 */
template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
    delete [] array;

}

template <typename Type>
int Dynamic_queue<Type>::size() const {
	
	return entry_count;
// retuns the number of entries in the array 
}

template <typename Type>
int Dynamic_queue<Type>::capacity() const {
	
	return array_capacity;
	// returns the size of the array 
}

template <typename Type>
bool Dynamic_queue<Type>::empty() const {
	
	return entry_count==0;
	// returns tru if array is empty 
}

template <typename Type>
Type Dynamic_queue<Type>::head() const {
	// an exception is thrown if array is empty 
	if (empty())
	{
		throw underflow();
	}

	return array[ihead];
	// returns the element at the head of the array 
}

template <typename Type>
void Dynamic_queue<Type>::swap( Dynamic_queue<Type> &queue ) {
	std::swap( initial_capacity, queue.initial_capacity );
	std::swap( array_capacity, queue.array_capacity );
	std::swap( array, queue.array );
	std::swap( ihead, queue.ihead );
	std::swap( itail, queue.itail );
	std::swap( entry_count, queue.entry_count );
}

template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=( Dynamic_queue<Type> rhs ) {
	swap( rhs );
	
	return *this;
}
/*
 * void Dynamic_queue<Type>::enqueue( Type const &obj )
 *
 * adds a new elemnt to the index itail
 *
 * if entry_count and capacity are the same the array is doubled
 * passes a paprameter
 * no returns 
 * 
 */
template <typename Type>
void Dynamic_queue<Type>::enqueue( Type const &obj ) {
	// doubles the capacity if size and capacity are equal 
	 if(size()==capacity())
	{
	 	// creates a new array that has double the capacity of the previuos 
	 	Type *new_array= new Type[array_capacity*2];
	 	array_capacity=array_capacity*2;

         if(itail<ihead)
	    {
	   	int count=0;
	   	 for(int i=itail; i<=capacity(); ++i )
	   	 {
            new_array[count]=array[i];
            ++count;
	   	 }
	   	delete [] array;
	    array=new_array;
        itail=entry_count;

	    }
	    
        // delete old array 
       // array=new_array;
        else 
       {
        int count=0;
        for(int i=ihead; i<=itail; ++i)
        {
          new_array[count]=array[i];
          ++count;
        }
        delete [] array;
        array=new_array;
        itail=entry_count;
    }
	 	
    }

       /* increment itail which is then implemeted as a circular array 
        itail pointer is set to 0 is itail is at capacity() */
	   ++itail;
	  
	   if(itail==capacity())
	   {
	   	itail=0;
	   }
	   // sets array[itail] to equal the object 
	   //entry count is incremented 
	   array[itail]=obj;
	   ++entry_count;

}

/*
 * Type Dynamic_queue<Type>::dequeue()
 *
 * equivalent of pop in linked_stacl
 * pops the element initally added to the list
 * FIFO
 * checks if array is empty and throws underflow exception
 * if entry_count is quarter capacity and halves the array if so
 * passes a paprameter
 * returns the element popped or dequeued
 * 
 * conditions if empty throws underflow 
 *  has tree cases 
 */
template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
	
	if (empty())
	{
		throw underflow();
	}  
	// create a temporary variable to store previous head
	Type previous_head=array[ihead];
	++ihead; 
	// decrement entry count
    --entry_count;

	// if the head is at capacity 
	if (ihead==capacity())
	{
		ihead=0;
		//sets ihead to zero does circular array implementation 
	}
	if (size()==0.25*capacity() && capacity()> initial_capacity)
	{
		
		Type *new_array=new Type[capacity()/2];
		array_capacity=array_capacity*0.5;
		int count=0;
		//loops though old array and copies all its values 
        for (int i=0; i<capacity(); ++i)
        {
        	new_array[count]=array[i];
        	++count;
        }
        delete [] array;
        array=new_array;
        ihead=0;
        itail=entry_count;
	}
	
	return previous_head;
}

template <typename Type>
void Dynamic_queue<Type>::clear() {
	
	for (int i=0; i<size(); ++i)
	{
		array[i]=0;
	}
	ihead=0;
	itail=0;
	array_capacity= initial_capacity;

}
/*
 * Dynamic_queue<Type>::clear()
 *
 * reset all the entries in the queue
 * sets ihead and itil to the start of the array 
 * array capacity is set to the intial capacity  
 * no returns on this method 
 */
// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Dynamic_queue<Type> const &queue ) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";
   out<< "ihead->";
   for(int i=0; i<=queue.entry_count; ++i)
   {
   	out<< queue.array[i]<<"->";
   }
   out<< "itail";
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
