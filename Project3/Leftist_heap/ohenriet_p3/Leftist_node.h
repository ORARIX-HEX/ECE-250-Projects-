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
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *new_heap, Leftist_node *&ptr_to_this );
		void clear();
};
// some sample functions are given
/*
 * type Class_name::function_name( type param_1, type param_2 ) const
 *
 * Henrietta Ochuko Odiete  
 * 2015-03-10             
 *
 * private 
 *      Type element; -- returns the element at the root node 
 *		Leftist_node *left_tree; -- pointer to the left sub tree
 *		Leftist_node *right_tree; --pointer to the right sub tree
 *		int heap_null_path_length; -- null path length 
 *
 * public:
 *		Leftist_node( Type const & ); -- default constructo 
 *
 *		Type retrieve() const; -- returns the member variabble elemnent 
 *		bool empty() const; -- returns true if empty 
 *		Leftist_node *left() const; -- returns the address of the left tree
 *		Leftist_node *right() const; - returns the address of the right tree 
 *		int count( Type const & ) const; -- returns the number of elements equal to the instance 
 *		int null_path_length() const; -- retuns the member variable heap_null_path_length
 *
 *		void push( Leftist_node *new_heap, Leftist_node *&ptr_to_this );
 * 		void clear();
 *
 *
 *  
 *
 * 
 * 
 *
 *
 *
 *
 *  type param_2
 *   Another description and any
 *   restrictions on its value.
 *
 * Bugs:           // Segementation fault occurred on leftist node may be a pointer assignment problem 
 * Todo:           // 
 * References:     // if applicable (very useful)
 */

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

template<typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}
// You must implement everything
template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::left()const{
	 return left_tree;
}
// returns the member variable left_tree

template<typename Type>
Leftist_node<Type> *Leftist_node<Type>::right()const{
	 return right_tree;

}
// returns the member variable right_tree 


template<typename Type>
int Leftist_node<Type>::null_path_length() const{
	if(this==nullptr)
	{
  		return -1;
	}
	else
	{
	   return heap_null_path_length;
    }
    // returns the member variable heap_null_path_length 
}

template<typename Type>
int Leftist_node<Type>::count(Type const &obj ) const{
	if(empty())
	{
		return 0;
	}
	if(element==obj)
	{
		return 1+count(left_tree)+count(right_tree);
	}
	else
	{
		return 0+count(left_tree)+count(right_tree);
	}
/*
  return 0 if the node is empty 
  returns the the count of the argument from the left subtree and right subtree
*/


}

template<typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this)
{
	if(new_heap==nullptr)
	{ 
  		return;

	}
 	if(empty())
 	{
        
        ptr_to_this= new_heap;
    	return;
 	}
 	

    if ( retrieve() <= new_heap->retrieve() )
    { 

       	 right()-> push( new_heap, right_tree );

       	 ptr_to_this->heap_null_path_length =
       	      1 + std::min(  left_tree->null_path_length(),
       	      	            right_tree->null_path_length() );

        if(left()->null_path_length() < right()->null_path_length())
       	{
         	    std::swap(left_tree, right_tree);

    	}
	} else { 
        ptr_to_this = new_heap;
        new_heap->push( this, ptr_to_this );
    }
}
/*
  if element is nothing return out of the method 
  if empty set ptr_to_this to the new elemnt and call push
  if the value is larger push it on to the right tree and update the null path lenght 
  if the left tree has a smaaller null path length swap the two sub trees 
  otherwise set ptr_to_this to new_heap 
  ad call push on the new_heap
  returns the the count of the argument from the left subtree and right subtree
*/


template<typename Type>
void Leftist_node<Type>::clear(){
 	if (this==nullptr)
 	{
       	return;
 	}
 	else
    {
   		left()->clear();
   		right()->clear();
    	delete this;
    }

}
/*
  call clear on the left tree
  calls left on the right tree
  and deletes this  
*/


#endif