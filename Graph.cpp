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

int Graph::tree_search(int *best, list<int> vertex_list) {
    if(vertex_list.size()== this->size){
        int temp_result = calculate_route(vertex_list);
        if(*best > temp_result){
            *best = temp_result;
            return 0;
        }
    }

    for(int i=0; i<this->size; ++i){
        bool exists = false;
        for(int j: vertex_list){
            if(i==j){
                exists = true;
                break;
            }
        }
        if(!exists){
            vertex_list.push_back(i);
            tree_search(best, vertex_list);
            vertex_list.pop_back();
        }
    }

    return *best;
}

void Graph::brute_force() {
    list<int> vertex_list;
    vertex_list.push_back(0);
    int best = 1 << 30;
    int result = tree_search(&best, vertex_list);
    cout << result << endl;
}

void Graph::dynamic_programming() {
    int **dp = nullptr;
    dp = new int*[1 << this->size]; //wszyskie mozliwe sciezki

    for(int i=0; i<(1 << this->size); ++i){
       dp[i] = new int[this->size]; //koncowy wierzcholek
    }

    for (int i  = 0; i < (1<<this->size); ++i) {
        for(int j=0; j<this->size; ++j){
            dp[i][j] = 1 << 30; // wszytkie koszty na niesskonczynosc
        }
    }

    for(int i=0; i < this->size; i++){
        dp[1<<i | 1][i] = this->matrix[0][i]; //koszt przejscia od 0 do n
    }

    for(int bit_mask=0; bit_mask < 1 << this->size; ++bit_mask ){
        for(int v =0; v < this->size; ++v){
            if(!(bit_mask & (1 << v))) continue;
            for(int j = 0; j < this->size; ++j){
                if(!(bit_mask & (1<<j)))
                    dp[bit_mask | (1 << j)][j] = min(dp[bit_mask | (1 << j)][j], dp[bit_mask][v] + this->matrix[v][j]);
            }
        }
    }

    int result = 1<<30;
    int sum;

    for(int i = 0; i < this->size; i++){
        sum = dp[(1 << this->size) -1 ][i] + this->matrix[i][0];
        if(sum < result){
            result = sum;
        }
    }

    cout << result << endl;
}
