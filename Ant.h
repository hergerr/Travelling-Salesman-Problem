//
// Created by tymek on 14.01.2020.
//
#include <vector>
#ifndef TRAVELLING_SALESMAN_ANT_H
#define TRAVELLING_SALESMAN_ANT_H

using namespace std;
class Ant {
public:
    int number;
    vector<bool> visited;
    Ant(int number, int number_of_vertex);
    ~Ant();
};


#endif //TRAVELLING_SALESMAN_ANT_H
