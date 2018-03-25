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
 *  Tasnim Alam  t7alam@uwaterloo.ca -- helped with debugging copy constructor 
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <stack>
#include <queue>
//tar -cvzf ohenriet_p3.tar.gz Leftist_heap.h Leftist_node.h

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		Leftist_heap( Leftist_heap const & );
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		Leftist_heap &operator=( Leftist_heap );

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given
/*
 * type Class_name::function_name( type param_1, type param_2 ) const
 *
 * Henrietta Ochuko Odiete  
 * 2015-03-10             
 *
 * public 
 *   Leftist_heap();
 *	 Leftist_heap( Leftist_heap const & ); -- implemented a depth first traversal that copies 
 *   the entire heap using std::queue 
 *	 ~Leftist_heap();-- calls clear on the heap which deletes the heap 
 *
 *   bool empty() const; --return a boolean value if the trees is empty 
 *	 int size() const; -- returns the member variable heap_size
 *	 int null_path_length() const; -- returns the null path length
 *	 Type top() const; -- returns the element att the top of the heap
 *	 int count( Type const & ) const; 
 * 
 *  void push( Type const & );-- add a new elemt to the node and 
 *	Type pop(); -- pops the smallest element in the list and merges the two forrest
 *  using push 
 *	void clear();
 * 
 * private:
 * Leftist_node<Type> *root_node;- pointer to the root node 
 * int heap_size;
 * 
 *
 * Preconditions:
 *  The pop function throws underflow if the leftist heap is empty 
 *  top() returns -1 if the heap is empty 
 *  
 *
 * Postconditions:
 * 
 *
 *
 * Parameters:
 *  type param_1
 * Leftist_node<Type> *root_node; -- pointer to the small element in the leftist_heap
 * int heap_size; -- stores the number of elements in the leftist_heap
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
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

template <typename Type>
Leftist_heap<Type>::Leftist_heap( Leftist_heap const &heap ):
root_node( nullptr ),
heap_size( 0 ) {

	if(heap.empty())
    {
      return;
      //returns out of the copy constructor is empty 
    }
     std::queue<Leftist_node<Type> *> breadth_first;
   
     breadth_first.push(heap.root_node);
    
    while(!breadth_first.empty())
    {
      push(breadth_first.front()->retrieve());

      if(breadth_first.front()->left()!=nullptr)
      {
        breadth_first.push(breadth_first.front()->left());
      }
      if (breadth_first.front()->right()!=nullptr)
      {

       breadth_first.push(breadth_first.front()->right());

      }

       breadth_first.pop();

  }
  // using the standard template library queues
  // add the root node to the new heap
  // copies all elements in the heap using a breath first traversal 
  // the parent of is then popped after its children are added to the queue
  // copies left and right sub trees children and calls pop on them 
	
}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=( Leftist_heap<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
bool Leftist_heap<Type>::empty()const {
	return (size()==0);
}
//returns true if the heap size is equal 0
// used to implement pop and other member functions 
template <typename Type>
int Leftist_heap<Type>::size() const{
	
	return heap_size;
}
// returns the size of the heap 

template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	
	if(empty())
	{
		return -1;
	}

	else
	{
		return root_node->null_path_length();
	}
	
	/* returns -1 if the heap is empty 
	 otherwise returns the member variable 
	*/
}

template<typename Type>
Type Leftist_heap<Type>::top() const{
	if(empty())
	{
		throw underflow();
	}

	else
	{
		return root_node->retrieve();
	}
}
// returns the element stored at the top of the heap 
template<typename Type>
int Leftist_heap<Type>::count( Type const &obj ) const
{
	return count(obj);
  
}
// recursively call count which is implemented in leftist_node class

template<typename Type>
void Leftist_heap<Type>::push(Type const &obj )
{
    if(empty())
    {
    	root_node= new Leftist_node<Type>(obj);
    	++heap_size;
    	return;
    } 

	   Leftist_node<Type> *new_object= new Leftist_node<Type>(obj);
	   root_node->push(new_object,root_node);
	   ++heap_size;
}
/*
if empty create a new variable to hold the obj to be inserted into the heap 
else creates new varialbe and calls push on the root node and the variable
increment the heap size
*/
template<typename Type>
Type Leftist_heap<Type>::pop()
{
	if(empty())
    {
   	   throw underflow();
    }  

                                                                                                                 
    Type return_popped_node = root_node->retrieve(); 
    Leftist_node <Type> *old_root= root_node;  

    root_node= root_node->left();

    Leftist_node <Type> *right_subtree=  old_root->right();
    delete old_root;
    --heap_size;

    root_node->push( right_subtree, root_node );
    return return_popped_node;
  

}
/*
  throw an excption if the heap is empty 
  deletes the smallest entry in the heap (the root node)
  and calls push on the two forrest 
  returns the delete node 
  the heap size is decremented 
*/

template<typename Type>
void Leftist_heap<Type>::clear()
{
	if ( empty() )
	{
		return;
	}
	else
    {
    	root_node->clear();
    	root_node=nullptr;
    	heap_size=0;
    }

 	

}
// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
// 
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?
 template <typename Type>

std::ostream &operator<<( std::ostream &out, const Leftist_heap<Type> &heap ) {
	out << "Size:     " << heap.heap_size << std::endl;

	if ( !heap.empty() ) {

		std::stack<Leftist_node<Type> *> traversal;

		std::stack<int> indentation;

		traversal.push( heap.root_node );
		indentation.push( 0 );

		while ( !traversal.empty() ) {
			Leftist_node<Type> *node = traversal.top();
			int indent = indentation.top();

			traversal.pop();
			indentation.pop();

			out.width( indent );
			out.fill( ' ' );
			out << "";

			if ( node == 0 ) {
				out << "-" << std::endl;
			} else {
				out << node->retrieve() << std::endl;

				if ( node->left() != 0 || node->right() != 0 ) {
					traversal.push( node->right());
					indentation.push( indent + 1 );

					traversal.push( node->left());
					indentation.push( indent + 1 );
				}
			}
		}
	}



	return out;
}

#endif
