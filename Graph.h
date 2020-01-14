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

#include "Ant.h"

using namespace std;

class Graph {
    int size;
    vector <vector <int> > matrix;

    double temperature = 1e9;
    double COOLING_RATE = 0.95;

    vector<vector< int > > population;
    vector<int> fitness;
    int population_size = 5000;
    int generations_number = 500;
    int tournament_number = 5;
    float cross_rate = 0.02;
    float mutation_rate = 0.02;

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
    void ts();

    void ga();
    void make_population();
    void select();
    void ordered_crossover(vector<int> &first_parent, vector<int> &second_parent);
    void inversion_mutation(vector<int> &path);

    void pa();
    void calculate_ant_routes(Ant* ant, vector<vector<int>> &routes, vector<vector<double>> &pheromones);
    void update_pheromones(vector<vector<double>> &pheromones, vector<vector<int>> &routes);
    double phi(int first_city, int second_city, Ant* ant, vector<vector<double>> &pheromones);
    int get_next_city(vector<double> &probabilities);

};


#endif //TRAVELLING_SALESMAN_GRAPH_H
