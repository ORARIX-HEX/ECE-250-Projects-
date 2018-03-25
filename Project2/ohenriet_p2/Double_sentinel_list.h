/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  koliu @uwaterloo.ca
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

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
class Double_sentinel_list
{
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

// constructor
    template <typename Type>
    Double_sentinel_list<Type>::Double_sentinel_list():
    list_head( nullptr ),
    list_tail( nullptr ),
    list_size( 0 )
    {
        Double_node<Type> *InitNode1 = new Double_node< Type >();     // init S nodes
        Double_node<Type> *InitNode2 = new Double_node< Type >();     //

        InitNode1->next_node = InitNode2;                           //connect the 2 S nodes
        InitNode2->previous_node = InitNode1;                       //

        list_head = InitNode1;                                      //set head ^ tail as the S nodes
        list_tail = InitNode2;                                      //

        list_size = 0;
    }


// copy constructor
    template <typename Type>
    Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
    list_head( nullptr ), 
    list_tail( nullptr ),
    list_size( 0 )
    {
        Double_node<Type> *copyHead = new Double_node< Type >;      //  construct a new list
        Double_node<Type> *copyTail = new Double_node< Type >;      //  
        list_head = copyHead;                                       //
        list_tail = copyTail;                                       //

        if (!list.empty())                                          //  only add nodes if not empty, else only head and tail.
        {
            copyHead->next_node = copyTail;                         //  copy head ^ tail
            copyTail->previous_node = copyHead;                     //

            Double_node<Type> *currentNode = list.list_head->next();
            while (currentNode != list.list_tail)
            {
                push_back(currentNode->retrieve());                 // push_back to undo the reverse of order cause by pushing head first
                currentNode = currentNode->next();
            }
        }
    }

// destructor
    template <typename Type>
    Double_sentinel_list<Type>::~Double_sentinel_list()
    {
        while (!empty())    //delete all contents
        {
            pop_front();
        }
        delete list_head;   //delete head ^ tail
        delete list_tail;
    }



// count list size
    template <typename Type>
    int Double_sentinel_list<Type>::size() const
    {
        int sizeCounter = 0;

        Double_node<Type> *currentNode = list_head->next();     //start at the 1st non-S node

        while (currentNode != list_tail)                        //break before tail gets "counted"
        {
            sizeCounter += 1;
            currentNode = currentNode->next();
        }

        return sizeCounter;
    }



// is list empty?
    template <typename Type>
    bool Double_sentinel_list<Type>::empty() const
    {
        if(list_head->next()==list_tail)        //if S->S then empty
            return true;
        else
            return false;
    }



// return value of 1st/last element
    template <typename Type>
    Type Double_sentinel_list<Type>::front() const 
    {
        if (empty())
            throw underflow();
        
        return head()->next()->retrieve();         //1st element after list_head
    } 
    template <typename Type>
    Type Double_sentinel_list<Type>::back() const
    {
        if (empty())
            throw underflow();
        else
            tail()->previous()->retrieve();     //last element before list_tail
    }



// returns head and tail pointers
    template <typename Type>
    Double_node<Type> *Double_sentinel_list<Type>::head() const
    {
        return list_head;
    }

    template <typename Type>
    Double_node<Type> *Double_sentinel_list<Type>::tail() const
    {
        return list_tail;
    }
//


// count nodes matching input
    template <typename Type>
    int Double_sentinel_list<Type>::count( Type const &obj ) const
    {
        int nodeCounter = 0;

        Double_node<Type> *currentNode = list_head->next();     //
                                                                // exclude list head and tail
        while (currentNode != list_tail)                        //
        {
            if (currentNode->retrieve() == obj)
            {   nodeCounter += 1;   }

            currentNode = currentNode->next();
        }

        return nodeCounter;
    }



// swap
    template <typename Type>
    void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list )
    {
        std::swap( list_head, list.list_head );
        std::swap( list_tail, list.list_tail );
        std::swap( list_size, list.list_size );
    }
    template <typename Type>
    Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs )
    {
        Double_sentinel_list<Type> copy( rhs );
        swap( copy );
        return *this;
    }



// prepend/append to list
    template <typename Type>
    void Double_sentinel_list<Type>::push_front( Type const &obj )
    {                                                   //(content, prev, next)
        Double_node<Type> *newHead = new Double_node<Type>(obj, list_head, list_head->next());      // new node is before 1st element, and after head.
        list_head->next()->previous_node = newHead;                                                 // set old_1st_element.previous to new_1st_element
        list_head->next_node = newHead;                                                             // set head.next = new 1st element
        list_size += 1;
    }

    template <typename Type>
    void Double_sentinel_list<Type>::push_back( Type const &obj )
    {                                                   //(content, prev, next)
        Double_node<Type> *newTail = new Double_node<Type>(obj, list_tail->previous(), list_tail);  // new node is after last element, and before tail.
        list_tail->previous()->next_node = newTail;                                                 // set old_last_element.next to new_last_element
        list_tail->previous_node = newTail;                                                         // set tail.previous = new_last_element
        list_size += 1;
    }



// deletes 1st/last node
    template <typename Type>
    Type Double_sentinel_list<Type>::pop_front()
    {
        if (empty())
            throw underflow();
        else
        {
            Double_node<Type> *popThisNode = list_head->next();         //save node as a variable before delete
            
            list_head->next_node = popThisNode->next();                 // head.next = 2nd element
            popThisNode->next()->previous_node = list_head;             // 2nd_element.previous = head
            list_size -= 1;

            Type valuePopped = popThisNode->retrieve();                 //save node's value before delete, need for return
            delete popThisNode;
            return valuePopped;
        }
    }

    template <typename Type>
    Type Double_sentinel_list<Type>::pop_back()
    {
        if (empty())
            throw underflow();
        else
        {
            Double_node<Type> *popThisNode = list_tail->previous();     //save node as a variable before delete

            list_tail->previous_node = popThisNode->previous();         // tail.previous = 2nd last element
            popThisNode->previous()->next_node = list_tail;             // 2nd_last_element.next = tail
            list_size -= 1;

            Type valuePopped = popThisNode->retrieve();                 //save node's value before delete, need for return
            delete popThisNode;
            return valuePopped;
        }
    }



// delete 1st node that matches input
    template <typename Type>
    int Double_sentinel_list<Type>::erase( Type const &obj )
    {
        Double_node<Type> *currentNode = list_head->next();


        while (currentNode != list_tail)                                            //traverse through list
        {
            if (currentNode->retrieve() == obj)                                     //if match found, delete
            {                                                                           //
                currentNode->previous()->next_node = currentNode->next();               //node_before.next = node_after
                currentNode->next()->previous_node = currentNode->previous();           //node_after.previous = node_before
                                                                                        //
                delete currentNode;                                                     //
                return 1;                                                               //return once element found
            }                                                                       //
            currentNode = currentNode->next();                                      //if not found, keep traversing
        }
        return 0;                                                               //if no node deleted after full traversal
    }



// You can modify this function however you want:  it will not be tested
template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ){
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
