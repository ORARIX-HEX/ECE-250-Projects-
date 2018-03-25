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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"
#include <algorithm>
#include <functional>
enum edge_state { VISITED, UNVISITED};
class Weighted_graph {
	private:
		static const double INF;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		int count;
		int matrix_size;
        double **matrix;

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		// bool is_connected_to(int, int) const;
		// bool is_connected_indirect(int, int) const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n ):
count( 0 ), 
matrix_size( n ),
matrix( new double*[matrix_size] ){
 for (int i= 1; i<n; ++i)
 {
 	matrix[i] = new double[i];
 	for (int j= 0; j< i; ++j)
 	{
 		matrix[i][j]= INF;
 	}
 	
 }
}

Weighted_graph::~Weighted_graph() {
	for (int i=1; i<matrix_size; ++i)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
	matrix=0;

}
int Weighted_graph::degree(int n) const{
	if(n<0|| n>matrix_size)
	{
		throw illegal_argument();
	}
	return n;
}
int Weighted_graph::edge_count()const{
   return count;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	 //std::cout << "starting insert" << std::endl;
	
	if(i<0 || i>matrix_size-1 || j<0 || j>matrix_size-1 || d<=0)
	{
		throw illegal_argument();
	} 
    
	if (i == j)
	{
		return false;
	}
	
	
	int row = i>j? i:j;
	int col = j>i? i:j;
	if (matrix[row][col]== INF)
	{
		matrix[row][col]=d;
		++count;
		return true;
	}
    matrix[row][col]=d;
    return true;

}

bool Weighted_graph::erase_edge(int i, int j){
	
	if (i< 0 || i>matrix_size || j<0 || j>matrix_size)
	{
		throw illegal_argument();
	}
	if (i == j){
		return true;
	}
	
	int row = i>j? i:j;
	int col = j>i? i:j;
	if (matrix[row][col]==INF)
	{
       return false;
	}
    matrix[row][col]=INF;
	return true;
}
void Weighted_graph::clear_edges(){
	
	for (int i =1; i<matrix_size; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
				matrix[i][j] = INF;
				matrix[j][i] = INF;
		}
	}
 
}
struct graph_edge{
	int v1; // first vertex 
	int v2; // second vertex 
	double w; // weight of the edge between to vertices 
	edge_state state; // the state of the edge visited or unvisted 
	bool operator < (const graph_edge& rhs) const { 
		return w < rhs.w; // used when std::sort() is called on1 the graph 
	}
};

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	graph_edge *all_edges= new graph_edge[edge_count()]; // creates a struct of edges 
    int all_edge_counter=0;  // intializes the counter 

    for(int i=1; i< matrix_size; ++i) // copies all the edges from the graph to be tested 
	{
		for (int j=0; j<i; ++j)
		{
			if(matrix[i][j]!=INF) // adds edges that are not infinity 
			{
				all_edges[all_edge_counter].v1 = i; // first vertex 
				all_edges[all_edge_counter].v2 = j; // second vertex 
				all_edges[all_edge_counter].w = matrix[i][j]; // edge weight 
				all_edges[all_edge_counter].state = UNVISITED; // marks the dege as unvisited 
				++all_edge_counter; // increment the edge counter 
		   }
		}
	}
	
	std::sort(all_edges, all_edges + edge_count()); // sorts all edges in ascending order 
	Data_structures::Disjoint_sets dset (matrix_size); // create a disjoint set with all the edges in the sorted array 

	int count_mst=0; // intialize the number of edges to 0 
	int unvisited = edge_count(); // initializes the number of unvisited to the number of edges in the graph
    double weight_of_mst=0; // weight of minimum spanning tree  
    int edges_tested=0; // number of edges tested 
    int i=0;

	while (unvisited > 0 && count_mst!=matrix_size-1) // loop while edges are unvisited or the count is not n-1
	{
		if(all_edges[i].state==UNVISITED) // checks if the current edge is unvisited 
		{
          	all_edges[i].state = VISITED; // mark the edge as visited 
        	--unvisited; // decrement unvisited counter 
       
			if(dset.find(all_edges[i].v1)!= dset.find(all_edges[i].v2))
			{ 
				weight_of_mst+= all_edges[i].w;
				++count_mst;
                dset.set_union(all_edges[i].v1, all_edges[i].v2);
			}	
        
   		}
		++edges_tested;
		++i;
 	}
    /* tar -cvf ohenriet_pM.tar Weighted_graph.h Disjoint_sets.h 
   gzip ohenriet_pM.tar
    */
 	return std::pair<double,int>(weight_of_mst,edges_tested);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}

#endif