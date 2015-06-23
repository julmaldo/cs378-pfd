#include <iostream>
#include <vector>
#include <algorithm>

struct node {
	int id;
    std::vector<int> outgoing;
    std::vector<int> incoming;
    node(int nId, std::vector<int> out, std::vector<int> in):id(nId),outgoing(out),incoming(in){}
};


// PFD read

std::vector<node> PDF_read (int NumberV, int NumberR, std::istream& in );

//check node

bool chNode (const node& Node);

//PDF constrcut 

void PDFconstruct (int NumberV, std::vector<node>& graph);

void::vector<int> PDFeval(std::vector<node>& graph);

// PDF print
void PFDprint (std::vector<int> result, std::ostream& out);

//Pfd solve
void PDFsolve (std::istream& r, std::ostream& w);
