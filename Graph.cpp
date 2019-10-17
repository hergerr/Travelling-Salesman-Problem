//
// Created by tymek on 15/10/2019.
//

#include "Graph.h"

void Graph::read_from_file(string file_name) {
    ifstream in(file_name);

    if (!in) {
        cout << "Cannot open file.\n";
        return;
    }
    string name;

    in >> name;
    in >> this->size;

    this->matrix.resize(this->size);

    for (int y = 0; y < this->size; ++y) {
        this->matrix[y].resize(this->size);
        for (int x = 0; x < this->size; ++x) {
            in >> this->matrix[y][x];
            if (this->matrix[y][x] == -1) {
                this->matrix[y][x] = 0;
            }
        }
    }
}

Graph::Graph() {
}

void Graph::print() {
    for (int y = 0; y < this->size; ++y) {
        for (int x = 0; x < this->size; ++x) {
            cout << this->matrix[y][x] << " ";
        }
        cout << endl;
    }
    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    cout << calculate_route(lst) << endl;
}

Graph::~Graph() {
}

void Graph::read_from_user() {
    cout << "Enter size of matrix: ";
    cin >> this->size;
    this->matrix.resize(this->size);

    for (int y = 0; y < this->size; ++y) {
        this->matrix[y].resize(this->size);
        for (int x = 0; x < this->size; ++x) {
            cin >> this->matrix[y][x];
        }
    }
}

void Graph::clean() {
    for (int i = 0; i < this->size; ++i) {
        this->matrix[i].clear();
    }
    this->matrix.clear();
    this->size = 0;
}

int Graph::calculate_route(list<int> path) {
    if (path.size() == this->size) {
        int result = 0;
        int start = 0;
        while (!path.empty()) {
            result += this->matrix[start][path.front()];
            start = path.front();
            path.pop_front();
        }

        // powrot
        result += this->matrix[start][0];
        return result;
    }
}
