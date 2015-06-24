#include "PFD.h"

// ----
// read
// ----

void PFD_read (std::istream& input, std::vector<node>& nodes) {
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

        nodes.push_back(temp);
    }
    
    if (num_of_tasks != num_of_rules) {
        PFD_check(nodes, num_of_tasks);
    }
    assert(nodes.size() > 0);
}

// -----
// check
// -----

void PFD_check (std::vector<node>& nodes, int num_of_tasks) {
    assert(num_of_tasks > 0);
    int nodes_size = nodes.size();
    
    for (int i = 1; i <= num_of_tasks; i++) {
        bool node_exists = false;
        
        for (int j = 0; j < nodes_size; j++) {
            if (i == nodes[j].name) {
                node_exists = true;
                break;
            }
        }
        
        if (!node_exists) {
            node temp;
            temp.name = i;
            nodes.push_back(temp);
        }
    }
    
    assert(nodes.size() > 0);
}

// ------
// update
// ------

void PFD_update (std::priority_queue<node>& nodes, int edge) {
    assert(nodes.size() > 0);
    std::vector<node> temp;
    
    while (!nodes.empty()) {
        temp.push_back(nodes.top());
        nodes.pop();
    }
    
    for (unsigned int i = 0; i < temp.size(); i++) {
        for (unsigned int j = 0; j < temp[i].edges.size(); j++) {
            if (temp[i].edges[j] == edge) {
                temp[i].edges.erase(temp[i].edges.begin()+j);
                break;
            }
        }
    }
    
    for (unsigned int i = 0; i < temp.size(); i++) {
        nodes.push(temp[i]);
    }
}

// -----
// print
// -----

void PFD_print (std::ostream& output, std::priority_queue<node> nodes) {
    assert(nodes.size() > 0);
    int top;
    
    while (!nodes.empty()) {
        top = nodes.top().name;
        output << top << " ";
        nodes.pop();
        if (nodes.size() != 0)
            PFD_update(nodes, top);
    }
    output << std::endl << std::endl;
}

// -----
// solve
// -----

void PFD_solve (std::istream& input, std::ostream& output) {
    std::vector<node> nodes;
    PFD_read(input, nodes);
    
    std::priority_queue<node> sorted_nodes(nodes.begin(), nodes.end());
    
    PFD_print(output, sorted_nodes);
}
