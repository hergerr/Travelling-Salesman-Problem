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
#include <math.h>

using namespace std;

class Graph {
    int size;
    vector <vector <int> > matrix;

    double temperature = 1e9;
    double COOLING_RATE = 0.95;

public:
    Graph();
    ~Graph();
    void read_from_file(string file_name);
    void read_from_user();
    int calculate_route(list<int> path);
    int calculate_route(vector<int> path);
    void brute_force();
    int tree_search(int*, list<int>);
    void dynamic_programming();
    void print();
    void clean();

    void sa();
    void cooling();
    vector<int> make_random_permutation(int size);
    double get_probability(int diffrence);

};


#endif //TRAVELLING_SALESMAN_GRAPH_H
