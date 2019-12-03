//
// Created by tymek on 15/10/2019.
//

#include <algorithm>
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
    if (vertex_list.size() == this->size) {
        int temp_result = calculate_route(vertex_list);
        if (*best > temp_result) {
            *best = temp_result;
            return 0;
        }
    }

    for (int i = 0; i < this->size; ++i) {
        bool exists = false;
        for (int j: vertex_list) {
            if (i == j) {
                exists = true;
                break;
            }
        }
        if (!exists) {
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
    cout << "Result: " << result << endl;
}

void Graph::dynamic_programming() {
    int **dp = nullptr; //[sciezka hamiltona][zakonczona w wierzcholku]
    dp = new int *[1 << this->size]; //wszyskie mozliwe sciezki

    for (int i = 0; i < (1 << this->size); ++i) {
        dp[i] = new int[this->size]; // wielkosc kolumny = rzad grafu
    }

    for (int i = 0; i < (1 << this->size); ++i) {
        for (int j = 0; j < this->size; ++j) {
            dp[i][j] = 1 << 30; // wszytkie koszty na niesskonczynosc
        }
    }

    for (int i = 0; i < this->size; i++) {
        dp[1 << i | 1][i] = this->matrix[0][i]; //koszt przejscia od 0 do n
    }

    for (int bit_mask = 0; bit_mask < 1 << this->size; ++bit_mask) {
        for (int v = 0; v < this->size; ++v) {
            if (!(bit_mask & (1 << v)))
                continue;    // odfiltrowanie sciezek ktore nie zawierają v, a maja sie w nim konczyc
            for (int j = 0; j < this->size; ++j) {
                if (!(bit_mask & (1
                        << j)))    // wierzcholek j, ktory ma byc potencjalnym przedluzeniem sciezki, nie moze znajdowac sie na dotychczasowej sciezce do v
                    dp[bit_mask | (1 << j)][j] = min(dp[bit_mask | (1 << j)][j], dp[bit_mask][v] +
                                                                                 this->matrix[v][j]); // sprawdzenie czy korzystniej do sciezki konczacej sie w v dodać droge do j, czy obecna sciezka do j jest lepsza
            }
        }
    }

    int result = 1 << 30;
    int sum;

    for (int i = 0; i < this->size; i++) { // szukanie minimalnego CYKLU w ostatnim wierszu
        sum = dp[(1 << this->size) - 1][i] + this->matrix[i][0];
        if (sum < result) {
            result = sum;
        }
    }

    cout << "Result: " << result << endl;
}

int Graph::calculate_route(vector<int> path) {
    int result = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        result += matrix[path[i]][path[i + 1]];
    }
    result += matrix[path[size-1]][path[0]];


    return result;

}

void Graph::cooling() {
    temperature *= COOLING_RATE;
}

vector<int> Graph::make_random_permutation(int size_of_permutation) {
    vector<int> vec;
    vec.reserve(size_of_permutation);
    for (int i = 0; i < size_of_permutation; ++i) {
        vec.push_back(i);
    }
    random_shuffle(vec.begin(), vec.end());

    return vec;
}

void Graph::sa() {
    vector<int> best_solution;
    vector<int> permutation = make_random_permutation(this->size);
    vector<int> next_step(permutation); //kontruktor kopiujacy

    this->temperature = 1e9;
    int result = 1 << 30;

    for (int i = 0; i < 50; ++i) { //liczba losowych miejsc startu
        while (temperature >= 0.1) {
            int number_of_steps = 3 * this->size;
            next_step = permutation;
            int permutation_value = calculate_route(next_step);

            while (number_of_steps-- > 0) {
                int first_position = rand() % this->size;   // potencjalne pozycja do zamiany
                int second_position = rand() % this->size;

                swap(next_step[first_position], next_step[second_position]);
                permutation_value = calculate_route(next_step);
                int diffrence = result - permutation_value;

                if (diffrence > 0) {
                    result = permutation_value;
                    best_solution = next_step;
                }
                if (diffrence > 0 || (diffrence < 0 && get_probability(diffrence) > ((double) rand() / RAND_MAX) + 1)) {
                    permutation = next_step;
                    break;
                } else {
                    swap(next_step[first_position], next_step[second_position]);
                }

            }

            cooling();

        }

        temperature = 1e9;
        permutation = make_random_permutation(this->size);
    }

    cout << "Result: " << result;
}

double Graph::get_probability(int diffrence) {
    return exp(diffrence / temperature);
}

void Graph::ts() {
    vector<vector< int > > tabu_matrix;
    vector<int> best_solution;
    vector<int> permutation = make_random_permutation(this->size);
    vector<int> next_step(permutation); //kontruktor kopiujacy
    int result = 1 << 30;

    tabu_matrix.resize(this->size);
    for (int i = 0; i < this->size; ++i) {
        tabu_matrix[i].resize(this->size, 0);
    }

    for (int i = 0; i < 69; ++i) {
        for (int step = 0; step < 10 * this->size; ++step) {

            int first_vertex_to_swap = 0, second_vertex_to_swap = 0, next_step_val = 1 << 30;

            for (int first_position = 0; first_position < this->size; ++first_position) {
                for (int second_position = first_position + 1; second_position < this->size; ++second_position) {

                    swap(permutation[first_position], permutation[second_position]);

                    int current_value = calculate_route(permutation);

                    if (current_value < result) {
                        result = current_value;
                        best_solution = permutation;
                    }

                    if (current_value < next_step_val) {
                        if (tabu_matrix[second_position][first_position] < step) {
                            next_step_val = current_value;
                            next_step = permutation;
                            first_vertex_to_swap = second_position;
                            second_vertex_to_swap = first_position;
                        }
                    }

                    swap(permutation[first_position], permutation[second_position]);
                }
            }
            permutation = next_step;
            tabu_matrix[first_vertex_to_swap][second_vertex_to_swap] += this->size;
        }
        permutation = make_random_permutation(this->size);

        for (int j = 0; j < this->size; ++j) {
            for (int k = 0; k < this->size; ++k) {
                tabu_matrix[j][k] = 0;
            }
        }
    }

    cout << "Result: " << result << endl;

}
