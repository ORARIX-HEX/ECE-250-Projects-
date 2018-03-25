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
 * Professor Douglas Harder's Implemetation of quadretic probing was used for inser, memeber and erase functions 
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		int erased;
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;
       
		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};
/*
 * Quadratic_hash_table.h
 *
 * Henrietta Dchuko Odiete 
 * 2015-03-23
 *
 * The class implements a quadraric hash table 
 * using quadratic probing on a table of size 2^m
 * all operations of the class are assumed to be O(n)
 * This is the best case run time of all functions within the class 
 *
 * Member Variables:     int count; // the number of elements in the hash table 
 *		                 int power;   // the number i.e 2^m is the size of the table
 *		                 int array_size;   // the size of the hash table 
 *		                 int mask;  // upper index of the hash table 
 *		                 int erased; // stores the count of bins marked as erased 
 *		                 
 *		                 bin_state_t *occupied; // an enumerated tyoe that keeps track of the status of the bins 
 *  type variable        Type *array; // the hash table       
 *
 * Class Variables:          int mask;  // intializes the size of the hash table         
 *  type variable        
 *                       cannot be negative 
 *
 * Class Constants:            // static const variables
 *								 int size() const; // returns the number of elements in hash table 
 *							     int capacity() const; // returns the number of bins in the hash table 
 *								 double load_factor() const; // calculates the load factor 
 *   							 given by the number of erased and occupied divided by the capacity 
 *								 bool empty() const; // returns true if the size is zero 
 *								  
 *								 bool member( Type const & ) const; //  returns true if an element is in the hash table 
 *								 Type bin( int ) const; // returns the element stored at a particular bin 
 * 
 *
 * Member Functions (Accessors):
 *      int size() const; // returns the number of elements in the hash table 
 *		int capacity() const; // returns the size of the hash table 
 *
 * Member Functions (Mutators):
 *  
 *  void insert( Type const & ); // inserts an object in to the appropriate bin using quadratic porbing 
 *		bool erase( Type const & ); // marks an object in the hash table as erased when found and returns true otherwise false is returned 
 *		void clear();// sets all the elements in the hash table to unoccupied and resets the count and erased variables 
 *
 *
 * Class Functions:            // static functions
 *		Quadratic_hash_table( int = 5 ); // class constructor intializes the size and static variables 
 *		~Quadratic_hash_table(); // deallocates memory for the class 
 *
 * Bugs:           // if applicable
 * Todo:           // if applicable
 * References:     // if applicable (very useful)
 */

/*
 * Quadratic_hash_table<Type>::Quadratic_hash_table(int m ){
 *
 *class constructor 
 * Intializes all member variables including the size of the hash table 
 * sets all the bin to be intially unoccupied 
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  no return type 
 */
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}

	erased = 0;
}
/*
 * Quadratic_hash_table<Type>::~Quadratic_hash_table(){
 * class destructor 
 * deallocates memory for the claass 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  no return type 
 */
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table(){
    delete [] array;
    delete [] occupied;

}
/*
 * int Quadratic_hash_table<Type>::size() const{
 *
 * returns the number of elements in the hash table 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  retuns an integer 
 */
template <typename Type>
int Quadratic_hash_table<Type>::size() const{
 return count;
}
/*
 * int Quadratic_hash_table<Type>::capacity() const{
 *
 * returns the number of avaliable bins in the hash table 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  retuns an integer 
 */
template <typename Type>
int Quadratic_hash_table<Type>:: capacity() const{
	return array_size;

}
/*
 * double Quadratic_hash_table<Type>::load_factor() const{
 *
 * returns the number of erased bins and the count divided by the array size  
 *
 * the sum of erased and double is statically cast to a double to prevent integer division 
 *
 * Returns:
 *  retuns a double 
 */
template <typename Type>
double Quadratic_hash_table <Type>:: load_factor() const{
   
  double total= erased + count;
  double size= array_size;
  //std::cout << " total:" << total << " size:" << size ; 
  double load_factor= static_cast<double>(total)/size;  

  return load_factor;

}

/*
 * bool Quadratic_hash_table<Type>::empty() const{
 *
 * returns trus if the has table is empty 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  retuns a boolean 
 */

template <typename Type>
bool Quadratic_hash_table<Type>:: empty() const{

    return count==0;
}
/*
 * bool Quadratic_hash_table<Type>::member(Type const &obj) 
 * Professor Douglas Harder's Implementation of quadratic probing is used 
 * finds an object in the hash table 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  retuns true if the ibject was found, false otherwise 
 */
template <typename Type>
bool Quadratic_hash_table<Type>::member(Type const &obj) const{
   	// bin is set to hash value by taking the integer modulo of the array_size 
    int bin= static_cast<int>(obj)%capacity();

   for(int i=0; i<array_size; ++i)
   {
      bin= (bin + i)% capacity();
      if(array[bin]==obj && occupied[bin]==OCCUPIED)
      {
      	return true;
      }

      if(occupied[bin]==UNOCCUPIED)
      {
          return false;
      	
      }

   }
   return false;

}
/*
 * bool Quadratic_hash_table<Type>::bin(int n) const{
 *
 * returns the value stored the a particular bin 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  retuns a Type  
 */

template <typename Type>
Type Quadratic_hash_table<Type>:: bin(int n)const{

  return array[n];

}

template <typename Type>
void Quadratic_hash_table<Type>:: print() const{

}
/*
 * void Quadratic_hash_table<Type>:: insert(Type const &obj)
 * Professor Douglas Harder's Implementation of quadratic probing is used 
 * inserts the value in the appropriate bin 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  no return type  
 */
template <typename Type>
void Quadratic_hash_table<Type>:: insert(Type const &obj){
	// Finds an empty bin and inserts the object in place
	// overflow exception ins tHrown if hash table ia at capacity 
	// bin is assign to the hash value of the object to be inserted 
 if(capacity()==size())
  {
  	throw overflow();
  }
  // bin is set to hash value by taking the integer modulo of the array_size 
  int bin=static_cast<int>(obj)% capacity();

   for(int i=0; i<array_size; ++i)
   {
      bin= (bin + i)% capacity();
      //objects are inserted in bin is marked as unoccupied 
      // count is then incremented 
      if(occupied[bin]== UNOCCUPIED)
      {
         array[bin]=obj;
         occupied[bin]=OCCUPIED;
         ++count;
      }
      // insertions are also done if a bin was previously marked as erased 
      //  erased counter is decremented 
      else if (occupied[bin]== ERASED)
      {
      	array[bin]=obj;
      	occupied[bin]=OCCUPIED;
      	++count;
      	--erased;
      }
      // if the object already exist in the hash table do nothing 
      if(array[bin]==obj)
      	{
      		return;
      	}
   }
}
/*
 * bool Quadratic_hash_table<Type>:: erase(Type const &obj){
 * Professor Douglas Harder's Implementation of quadratic probing is used 
 * finds an element and then marks it as erased 
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  returns true if the value is found, fals otherwise 
 */
template <typename Type>
bool Quadratic_hash_table<Type>:: erase(Type const &obj){
	// bin is set to hash value by taking the integer modulo of the array_size 
  int bin=static_cast<int>(obj) % capacity();

   for(int i=0; i<array_size; ++i)
   {
      bin= (bin + i)% capacity();
      // if the object is retrieved then mark it as erased 
      // increment erase size and decrement the size conter 
      // returns a value of true if object is found 
      if(array[bin]==obj && occupied[bin]==OCCUPIED)
      {
         occupied[bin]=ERASED;
         --count;
         ++erased;
         return true;
      }
      // while looping to find the object
      // if a bin is unoccupied or marked as erased
      // the object does not exist in the hash table 
      if(occupied[bin]==UNOCCUPIED)
      {

      	return false;
      }
   }
   // if the object could not be found after looping 
   return false;
      
}
/*
 * void Quadratic_hash_table<Type>:: clear()
 * resets all the bins to be unoccupied 
 * resets all bins to unoccupied 
 * sets the couters erased and count to zero 
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  returns true if the value is found, fals otherwise 
 */
template <typename Type>
void Quadratic_hash_table<Type>:: clear(){
  
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}

	 count=0;
	 erased=0;

}


template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

//   tar -cvf ohenriet_pM.tar Quadratic_hash_table.h

#endif