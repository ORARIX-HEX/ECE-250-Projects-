/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:   ohenriet @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2015
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

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
private:

    Double_node<Type> *list_head;
    Double_node<Type> *list_tail;
    int list_size;
    
public:
    Double_sentinel_list();
    Double_sentinel_list( Double_sentinel_list const & );
    ~Double_sentinel_list();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    Type front() const;
    Type back() const;
    
    Double_node<Type> *head() const;
    Double_node<Type> *tail() const;
    
    int count( Type const & ) const;
    
    // Mutators
    
    void swap( Double_sentinel_list & );
    Double_sentinel_list &operator=( Double_sentinel_list const & );
    
    void push_front( Type const & );
    void push_back( Type const & );
    
    Type pop_front();
    Type pop_back();
    
    int erase( Type const & );
    
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );

};
/*
 * Double_sentinel_list
 *
 * Henrietta Ochulo Odiete
 * 2015-02-03
 *
 * The class creates intializes head and tail sentinels using 
 * previous, next and list size from the double node class 
 * Deine Zauber binden wieder, was die Mode streng geteilt:
 * 
 *
 * Member Variables:  list_head list_tail 
 *  type variable        list_size returns the size of the list 
 *                            cannot be a negative value 
 *
 * Member Functions (Accessors):
 *  int size() const;  //returns number of items in list 
 *  bool empty() const; //returns true when list is empty 
 *  Type front() const; //gets the element stored at the fron of the list 
 *  Type back() const; //gets the element stored at the back of the list 
 *  Double_node<Type> //*head() const; returns the head pointer 
 *  Double_node<Type>  //*tail() const; returns the tail pointer 
 *  int count( Type const & ) const; //returns the number of nodes in the linked list storing a value equal to the argument 
 *  
 *  
 *   
 *
 * Member Functions (Mutators):
 * void swap( Double_sentinel_list & );
 * //swaps all the member variables of the list with those of the argument
 *  Double_sentinel_list &operator=( Double_sentinel_list & );
 *  //makes a copy of the argument and swaps the variables to a copy of the list 
 *  void push_front( Type const & ); //creates a new node and adds the node to the front of the list 
 *  void push_back( Type const & ); //adds new node to the back of the list 
 *  Type pop_front(); deletes first //node of the doubly linked list 
 *  Type pop_back(); //deletes last node of the doubly linked list 
 *  int erase( Type const & ); //deletes frist occurence of the node that equals to the argument and returns the value 
 *  
 *
 * Class Functions:            // static functions
 * Double_sentinel_list()
 * creates two instance of Double_node<Type> head and tail are set tp poin to one of the sentinels 
 *
 * ~Double _sentinel_list()
 * // deletes all nodes and the sentinels
 *
 * Double_sentinel_list<Type> const &list )
 * //creates a new list and copies all the entries in the previous list without changing the previous list 
 * 
 *
 * Bugs:           // if applicable
 * Todo:           // if applicable
 * References:     // if applicable (very useful)
 */
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( new Double_node<Type>(0,nullptr,nullptr)),
list_tail( new Double_node<Type>(0,nullptr,nullptr) ),
list_size( 0 ) {
    list_head->next_node =list_tail; 
    list_tail->previous_node =list_head;
}
/*
 *
 * Double_sentinel_list() // the constructor of the sentinel class 
 =creates list_head and list_taill sentinels 
 */   

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head(new Double_node<Type>(0,nullptr,nullptr)),
list_tail(new Double_node<Type>(0,nullptr,nullptr)),
list_size( 0 ) {
    if(list.empty()){
        return;
    }
    list_head->next_node =list_tail; 
    list_tail->previous_node =list_head;

    for(Double_node<Type> *ptr=list_head->next(); ptr!=list_tail; ptr=ptr->next()){ 
      Type temp= ptr->retrieve(); 
      push_back(temp); 
  }

}
 /*
 *
 *
 *Double_sentinel_list( Double_sentinel_list<Type> const &list ):
 * if(list.empty())  // returns out of the constructor when original list is empty 
 * head and tail sentinels are set to previous list sentinels
 *   for(Double_node<Type> *ptr=list_head->next(); ptr!=list_tail; ptr=ptr->next()){ //loops through the list to be copied 
 * ptr->retrieve();  // retrueves the node with each iteration of the listelped me with this 
 * push_back(temp); // add the node to the empty list pro
 */   
 
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    while(!empty())
    {
        pop_front();// deletes the first entry in the list 

    }
    delete list_head;
    delete list_tail; 
        
}
 /*
 *
 *
 * ~Double_sentinel_list()
 * while(!empty()){
 * pop_front(); // deletes the first entry in the list 
 *
 *  delete list_head;
 *   delete list_tail;
 *  // deallocates memory for head and tail  
 * add the node to the empty list
*/ 
 
template <typename Type>
int Double_sentinel_list<Type>::size() const {
    // returns the number of nodes in the doubly linked list 
    return list_size; 
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
     // returns true if list is empty 
    return(list_size==0);
}
 

template <typename Type>
Type Double_sentinel_list<Type>::front() const{
    if(empty()){
        throw underflow();
    }

    return list_head->next_node->retrieve();// retrieves the first value in the list 
}

 
 /*
 * if(empty()){throw underflow()} // executes an error when the list is empty 
 *return list_head->next_node->retrieve(); // retrieves the first value in the list 
 */

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if(empty()){
        throw underflow();
    }
    return list_tail->previous_node->retrieve(); 
}

/*
 * if(empty()){throw underflow()} // executes an error when the list is empty 
 *return list_tail->previous_node->retrieve(); // retrieves the last value in the list 
 */
template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
    //retrieves the head sentinel 
    return list_head; 
}


template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
    //retrieves the tail sentinel 
    return list_tail; 
    
}

 template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {

    int count=0;

    for(Double_node<Type> *ptr=list_head->next(); ptr!=list_tail; ptr=ptr->next())
    {
        if(ptr->retrieve()==obj)
        {
            ++count;
        }
    }
    return count; 
}
 /*
 * int count is intialized to the value of zero 
 *  for(Double_node<Type> *ptr=list_head->next(); ptr!=list_tail; ptr=ptr->next())
 * the for loop iterates through the list from the first node to the lat node 
 * ptr->retrieve()==obj // if the value of ptr is equal to the argument the counter is incremented 
 * finally count is returned when the loop terminates 
 */

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}


template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
    Double_sentinel_list<Type> copy( rhs );
    
    swap( copy );
    
    return *this;
}

 /* 
 * 
 * :operator=( Double_sentinel_list<Type> const &rhs ) {
 * swaps all the memeber variables of the list with those of the argument 
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

    Double_node<Type> *tmp =list_head->next(); 
    Double_node<Type> *current = new Double_node<Type>(obj,list_head,tmp); 
    list_head->next_node=current;
    tmp->previous_node=current; 
    ++list_size;
}

 /* 
 * 
 * :push_front( Type const &obj )  // this method adds to the front of the list 
 *
 * if 5 where to be appended to the front to the list 9->8->1->10-1>3
 * the function works as follows 
 *
 * Double_node<Type> *tmp =list_head->next(); //assign a tempoorary pointer to heads next node 
 * Double_node<Type> *current = new Double_node<Type>(obj,list_head,tmp);// creates new instance of object to be inserted at the front of the list 
 * list_head->next_node=current;// list_head is assgned to the new object
 * tmp->previous_node=current; // temporary previous pointer is assigned to the new element and increment the size 
 * ++list_size; // the size is incremented
 * the result will be  5->9->8->1->10-1>3
 
 *****************************************/

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node<Type> *tmp =list_tail->previous(); 
    Double_node<Type> *current =new Double_node<Type>(obj,tmp,list_tail);
    list_tail->previous_node=current;
    tmp->next_node=current;
    ++list_size;
}

 /* 
 * 
 * :push_back( Type const &obj )  // this method adds to the back of the list 
 *
 * if 5 where to be appended to the back list 9->8->1->10-1>3
 * the function works as follows 
 *
 * Double_node<Type> *tmp =list_tail->previous(); // assign a temporary pointer to tails previius node 
 * Double_node<Type> *current =new Double_node<Type>(obj,tmp,list_tail);// creates new instance of object to be inserted at the back of the list 
 *   list_tail->previous_node=current;// previous node of tail is assigned to the new object
 *  tmp->next_node=current;// temporary next pointer is assigned to the new object 
 *   ++list_size;
 * the result will be  9->8->1->10-1>3->5
 
 *****************************************/
template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
    if(empty())
    {  
        throw underflow();

    }
    Double_node<Type> *previous_front=list_head->next(); 
    Double_node<Type> *new_front=previous_front->next();  
    list_head->next_node=new_front; 
    new_front->previous_node=list_head; 
    --list_size; 
    return previous_front->retrieve(); 
    
}
/* 
 * 
 * ::pop_front() // this method removes the first entry of the list 
 * Double_node<Type> *previous_front=list_head->next(); // holds the value at the front of the list 
 * Double_node<Type> *new_front=previous_front->next(); //points to next value in the list 
 *   list_head->next_node=new_front; // assigns list_head  next pointer to the new front  
 *  new_front->previous_node=list_head; // assgnes the new fronts previous node to the the list_head 
 * --list_size; //decrements the size 
 * return previous_front->retrieve(); // returns the previous head 
 *****************************************/

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
    if(empty())
    {  
        throw underflow();

    }
    Double_node<Type> *old_back=list_tail->previous();  
    Double_node<Type> *new_back=old_back->previous(); 
    list_tail->previous_node=new_back; 
    new_back->next_node=list_tail;
    --list_size;
    return old_back->retrieve(); 
    
}

 
 /* 
 * ::pop_back() // this method removes the last entry of the list 
 * Double_node<Type> *old_back=list_tail->previous(); // holds the value at the back of the list 
 *   Double_node<Type> *new_back=old_back->previous(); //points to the previous value in the list 
 *  list_tail->previous_node=new_back; // assigns list_tail to the new back 
 *   new_back->next_node=list_tail;// assigns the new backs next_node to list_tail;
 *  --list_size; //decrements the size 
 *   return old_back->retrieve(); //retrieves old_back 
    
 *****************************************/

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    // enter your implementation here
   if(empty())
    {
        throw underflow();
    }
     
     Double_node <Type> *ptr=list_head->next(); 
     while(ptr!=list_tail) 
    {
        
        if(ptr->retrieve()==obj){ 
        ptr->next()->previous_node =ptr->previous(); 
        ptr->previous()->next_node = ptr->next();
        delete ptr; 
        --list_size; 
        return 1; 
       }
    }
    return 0; 
}
// You can modify this function however you want:  it will not be tested
/* erase( Type const &obj )// deletes the first occurence of an object in the list 
*   Double_node <Type> *ptr=list_head->next(); //creates a pointer assigned to the first value in the is 
*   the loop starts from ptr=head next 
*   if(ptr->retrieve()==obj){ // if pointer equals to the argument 
*   ptr->next()->previous_node =ptr->previous(); // the next node (after obj) previous pointer points to ptr previous
*   ptr->previous()->next_node = ptr->next(); // the previous node (before obj) next pointer points to ptr nest
*   delete ptr; // deletes  obj
*   --list_size; // decrements the size of the list 
*   return 1;
*  0 is returned if the object isn't found 
*/
template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";
    
    for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }
    
    out << "->0" << std::endl << "tail";
    
    for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }
    
    out << "->0";
    
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif