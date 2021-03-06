/*************************************************
 * Quadratic_hash_table_tester
 * A class for testing quadratic hash tables.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2007 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef DOUBLE_HASH_TABLE_TESTER_H
#define DOUBLE_HASH_TABLE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Quadratic_hash_table.h"

#include <iostream>


template <typename Type>
class Quadratic_hash_table_tester:public Tester< Quadratic_hash_table<Type> > {
	using Tester< Quadratic_hash_table<Type> >::object;
	using Tester< Quadratic_hash_table<Type> >::command;

	public:
		Quadratic_hash_table_tester( Quadratic_hash_table<Type> *obj =
0 ):Tester< Quadratic_hash_table<Type> >( obj ) {
			// empty
		}

		void process();
};


/****************************************************
 * void process()
 *
 * Process the current command.  For quadratic hash tables, these include:
 *
 *  Constructors
 *
 *   new             constructor     create a queue with the default array size
 *   new: n          constructor     create a queue with an array size of n
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   capacity n      capacity        the capacity equals n
 *   load_factor d   load_factor     the load factor equals d
 *   empty b         empty           the result is the Boolean value b (0/1)
 *   member n b      member          checks if n is in the hash table (return value b)
 *   bin n m         bin             checks if m is in bin n
 *
 *  Mutators
 *
 *   insert n        insert          the element can be inserted into the hash table (always succeeds)
 *   insert!         insert          an overflow exception is expected
 *   erase n b       erase           the element can be inserted into the hash table
 *   clear           clear           empties the hash table
 *
 *  Others
 *
 *   cout            cout << hash    print the hash table
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

template <typename Type>
void Quadratic_hash_table_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Quadratic_hash_table<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "new:" ) {
		int n;
		std::cin >> n;
		object = new Quadratic_hash_table<Type>( n );
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "capacity" ) {
		// check if the capacity equals the next integer read

		int expected_capacity;

		std::cin >> expected_capacity;

		int actual_capacity = object->capacity();

		if ( actual_capacity == expected_capacity ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in capacity(): expecting the value '" << expected_capacity << "' but got '" << actual_capacity << "'" << std::endl;
		}
	} else if ( command == "load_factor" ) {
		// check if the load factor equals the next double read

		double expected_load_factor;

		std::cin >> expected_load_factor;

		double actual_load_factor = object->load_factor();

		if ( actual_load_factor == expected_load_factor ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in load_factor(): expecting the value '" << expected_load_factor << "' but got '" << actual_load_factor << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "member" ) {
		// check if the element is in the object

		Type n;
		bool expected_member;

		std::cin >> n;
		std::cin >> expected_member;

		bool actual_member = object->member( n );

		if ( actual_member == expected_member ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in member(" << n << "): expecting the value '" << expected_member << "' but got '" << actual_member << "'" << std::endl;
		}
	} else if ( command == "bin" ) {
		// check the element in the specified bin

		int n;
		Type expected_value;

		std::cin >> n;
		std::cin >> expected_value;

		Type actual_value = object->bin( n );

		if ( actual_value == expected_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in bin(" << n << "): expecting the value '" << expected_value << "' but got '" << actual_value << "'" << std::endl;
		}
	} else if ( command == "insert" ) {
		// insert the next integer read onto the hash table

		Type n;

		std::cin >> n;

		object->insert( n );
		std::cout << "Okay" << std::endl;
        } else if ( command == "insert!" ) {
                // cannot insert due to the table being full

                Type n;

                std::cin >> n;

                try {
                        object->insert( n );
                        std::cout << "Failure in insert(" << n << "): expecting to catch an exception but did not" << std::endl;
                } catch( overflow ) {
                        std::cout << "Okay" << std::endl;
                } catch (...) {
                        std::cout << "Failure in insert(" << n << "): expecting an overflow exception but caught a different exception" << std::endl;
                }
	} else if ( command == "erase" ) {
		// check the element in the specified bin

		Type n;
		bool expected_value;

		std::cin >> n;
		std::cin >> expected_value;

		bool actual_value = object->erase( n );

		if ( actual_value == expected_value ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in erase(" << n << "): expecting the value '" << expected_value << "' but got '" << actual_value << "'" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear();

		std::cout << "Okay" << std::endl;
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif