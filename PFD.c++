#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <queue>
#include <algorithm> //for_each
#include <cstdio> //for NULL

#include "PFD.h"

using namespace std;


/*
void PFD_solve (std::istream& input, std::ostream& output) {
    std::vector<node> nodes;
    PFD_read(input, nodes);
    
    std::priority_queue<node> sorted_nodes(nodes.begin(), nodes.end());
    
    PFD_print(output, sorted_nodes);
*/
  void solve_PFD(istream& r, ostream& w)
{
    assert(r != NULL);
    assert(w != NULL);

    int t_size, r_size;
    r >> t_size;
    r >> r_size;
   
    vector<Vertex> vertices(t_size);
    
    for(int a = 0, b = 1; a < (int)vertices.size(); ++a, ++b)
    {
        vertices[a].number = b;
    }

    read_PFD(r, r_size, vertices);

    eval_PFD(vertices, w);
}

/*void PFD_read (std::istream& input, std::vector<node>& nodes) {
    int num_of_tasks, num_of_rules, num_of_edges;
  input >> num_of_tasks;
    input >> num_of_rules;
    assert(num_of_tasks > 0);
    
    for (int i = 0; i < num_of_rules; i++) {
        node temp;
       input >> temp.name;
               input >> num_of_edges;
        for (int j = 0; j < num_of_edges; j++) {
           int edge;
            input >> edge;
           temp.edges.push_back(edge);
        }
        */
 void read_PFD(istream& r, int r_size, vector<Vertex>& vertices)
{
    while(r_size-- != 0)
    {
        readHelper(r, vertices);
    }
}
/*void read_rules(istream& r, int rules_size, vector<Vertex>& vertices)
{
    assert(r != NULL);
    assert(rules_size >= 0);
    assert(rules_size < 100);
    assert(!vertices.empty());
    assert(vertices.size() <= 100);

    while(rules_size-- != 0)
    {
        read_rule(r, vertices);
    }
}*/
 void readHelper(istream& r, vector<Vertex>& vertices)
{
   
    int index, predecessors_size, predecessor;

    r >> index; r >> predecessors_size;
    vertices[index-1].number_previous = predecessors_size;

    while(predecessors_size-- != 0)
    {
        r >> predecessor;
        vertices[predecessor-1].succeeders.push_back(&vertices[index-1]);
    }
}

inline bool solved(vector<Vertex>& vertices)
{
    

    for(int a = 0; a < (int)vertices.size(); ++a)
    {
        if(vertices[a].number_previous != 0)
        {
            return false;
        }
    }
    return true;
}

 void eval_PFD (vector<Vertex>& vertices, ostream& w)
{
   
   
    priority_queue<Vertex*, vector<Vertex*>, Compare> vertices_no_p;

    
    for_each(vertices.begin(), vertices.end(), Trans_verts(&vertices_no_p));
    
    int vert;
    vector<Vertex*>* succeeders;
    while(!vertices_no_p.empty()) 
   {
        vert = vertices_no_p.top()->number;
        succeeders = &(vertices_no_p.top()->succeeders);
        
        print_PFD(w, vert);
        
        vertices_no_p.pop();

      /*
      while (!nodes.empty()) {
        top = nodes.top().name;
        output << top << " ";
        nodes.pop();
        if (nodes.size() != 0)
            PFD_update(nodes, top);
      */
        for_each(succeeders->begin(), succeeders->end(), Remove_predecessors(&vertices_no_p));
    }

}
 void print_PFD (ostream& w, int i) 
{
    assert(i > 0);
    assert(i <= 100);
    w << i << " ";
} 

