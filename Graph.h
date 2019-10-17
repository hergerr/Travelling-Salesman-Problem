//
// Created by tymek on 15/10/2019.
//

#ifndef TRAVELLING_SALESMAN_GRAPH_H
#define TRAVELLING_SALESMAN_GRAPH_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

class Graph {
    int size;
    vector <vector <int> > matrix;

public:
    Graph();
    ~Graph();
    void read_from_file(string file_name);
    void read_from_user();
    int calculate_route(list<int> path);
    void print();
    void clean();
};


#endif //TRAVELLING_SALESMAN_GRAPH_H
