#ifndef PFD_H
#define	PFD_H

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <queue> // priority queue
#include <vector> // vector
#include <cassert> // assert

// -------
// structs
// -------

typedef struct node {
    int name;
    std::vector<int> edges;
    bool operator< (const node& rhs) const {
        if (edges.size() == rhs.edges.size())
            return name > rhs.name;
        else return edges.size() > rhs.edges.size();
    }
};

// --------
// PFD_read
// --------

/**
* reads input into individual nodes
* @param input a std::istream 
* @param nodes a std::vector<node> by reference
*/
void PFD_read (std::istream&, std::vector<node>&);

// ---------
// PFD_check
// ---------

/**
* verifies that all nodes are accounted for
* @param nodes a std::vector<node> by reference
* @param num_of_tasks the number of tasks given
*/
void PFD_check (std::vector<node>&, int);

// ----------
// PFD_update
// ----------

/**
* updates priority queue after element is popped
* @param nodes a std::priority_queue<node>
* @param edge the edge to be removed
*/
void PFD_update (std::priority_queue<node>&, int);

// ---------
// PFD_print
// ---------

/**
* prints the nodes in order of priority
* @param output a std::ostream
* @param nodes a std::priority_queue<node>
*/
void PFD_print (std::ostream&, std::priority_queue<node>);

// ---------
// PFD_solve
// ---------

/**
* read, prioritize, print result
* @param r a std::istream
* @param w a std::ostream
*/
void PFD_solve (std::istream&, std::ostream&);

#endif	// PFD_H
