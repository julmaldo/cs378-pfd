#include <iostream> // istream, ostream
#include <vector>
#include <queue>

using namespace std;

 // Object the represents the task
 
class Vertex
{
    public:
        int number; 
        int number_previous; 

        vector<Vertex*> succeeders;       
        Vertex()
        {
            number_previous= 0;
        }
};

 //comparison priority queue of verts with no predecessors
 
class Compare
{
public:
    
    bool operator()(Vertex* v1, Vertex* v2) 
    {
       return v1->number > v2->number;
    }
};

 //getting vert with no predecessors after the init
 
class Trans_verts
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Compare>* vertices_no_p; 
    Trans_verts(priority_queue<Vertex*, vector<Vertex*>, Compare>* q)
    {
        vertices_no_p = 
        q;
    }
    void operator()(Vertex& v) 
    {
       if(v.number_previous == 0)
        {
            vertices_no_p->push(&v);
        }
    }
};

//reduces number of predecessors
 
class Remove_predecessors
{
public:
    priority_queue<Vertex*, vector<Vertex*>, Compare>* vertices_no_p; 
    Remove_predecessors(priority_queue<Vertex*, vector<Vertex*>, Compare>* q)
    {
        vertices_no_p = q;
    }  
    void operator()(Vertex* v) 
    {
        if(--(v->number_previous) == 0)
        {
            vertices_no_p->push(v);
        }
    }
};

// solve the PFD problem 

 void solve_PFD(istream& r, ostream& w);

//read rules desired structure for the vector

void read_PFD(istream& r, int rules_size, vector<Vertex>& vertices);

//read single line of rule to const vector

void readHelper(istream& r, vector<Vertex>& vertices);

// write the solution out

void eval_PFD (vector<Vertex>& vertices, ostream& w);

//print out a number that represents a task

void print_PFD (ostream& w, int i);

