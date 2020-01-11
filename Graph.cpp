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
    result += matrix[path[size - 1]][path[0]];


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

    for (int i = 0; i < 50; ++i) { //liczba losowych miejsc startu, tzw generacji
        while (temperature >= 0.1) {
            int number_of_steps = 3 * this->size;
            next_step = permutation;
            int permutation_value = calculate_route(next_step);

            while (number_of_steps-- > 0) {     // liczba zamian w ramach jedengo spadku temperatury
                int first_position = rand() % this->size;   // potencjalne pozycje do zamiany
                int second_position = rand() % this->size;

                swap(next_step[first_position], next_step[second_position]);
                permutation_value = calculate_route(next_step);
                int diffrence = result - permutation_value; // > 0 -> poprawiony wynik

                if (diffrence > 0) {    // jesli permutacja daje lepszy wynik, zapamietaj rezultat i sciezke
                    result = permutation_value;
                    best_solution = next_step;  // globalnie najlepsze rozwiazania
                }
                if (diffrence > 0 || (diffrence < 0 && get_probability(diffrence) > ((double) rand() / RAND_MAX))) {
                    permutation = next_step;    // jesli permutacja jest lepsza, lub temperatura i roznica pozwalaja pogorszyc, zapisz te permutacje
                    break;
                } else {
                    swap(next_step[first_position],
                         next_step[second_position]); // w przeciwnym wypadku wycofaj te zmiane
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
    vector<vector<int> > tabu_matrix;
    vector<int> best_solution;
    vector<int> permutation = make_random_permutation(this->size);
    vector<int> next_step(permutation); //kontruktor kopiujacy
    int result = 1 << 30;

    tabu_matrix.resize(this->size);
    for (int i = 0; i < this->size; ++i) {  // zapelnienie tablicy przejsc 0 - wyzerowanie macierzy tabu
        tabu_matrix[i].resize(this->size, 0);
    }

    for (int i = 0; i < 50; ++i) {  // ilosc pokolen
        for (int step = 0; step < 10 * this->size; ++step) { // kroki - wykorzystywane przy sprawdzaniu tabu

            int first_vertex_to_swap = 0, second_vertex_to_swap = 0, next_step_val = 1 << 30;

            for (int first_position = 0; first_position < this->size; ++first_position) {
                for (int second_position = first_position + 1; second_position < this->size; ++second_position) {

                    swap(permutation[first_position], permutation[second_position]);//zamiana w permutacji

                    int current_value = calculate_route(permutation); // policzenie wartosci tej zamiany

                    if (current_value < result) {   // zapisanie globalnie najlepszego kosztu i sciezki
                        result = current_value;
                        best_solution = permutation;
                    }

                    if (current_value < next_step_val) {    // jesli zamiana poprawia dlugosc sciezki
                        if (tabu_matrix[second_position][first_position] <
                            step) {  //jesli zamiany nie ma w macierzy tabu
                            next_step_val = current_value;  // zapisz wartosc tej permutacji
                            next_step = permutation;    // zapisz te permutacje
                            first_vertex_to_swap = second_position; // zapisanie ktore wierzcholki zostaly zamienione
                            second_vertex_to_swap = first_position; // w celu pozniejszego wpisania na liste tabu
                        }
                    }

                    swap(permutation[first_position], permutation[second_position]); // cofniecie zmiany
                }
            }
            permutation = next_step; // zapisanie najlepszej permutacji
            tabu_matrix[first_vertex_to_swap][second_vertex_to_swap] =
                    step + this->size; // zapisanie wierzcholkow do macierzy tabu
        }
        permutation = make_random_permutation(this->size);  // nowa permutacja dla nowego pokolenia

        for (int j = 0; j < this->size; ++j) {  // wyzerowanie listy tabu
            for (int k = 0; k < this->size; ++k) {
                tabu_matrix[j][k] = 0;
            }
        }
    }

    cout << "Result: " << result << endl;

}

void Graph::ga() {
    make_population();
    for (int j = 0; j < this->generations_number; ++j) {
        select();
        for (int i = 0; i < (int) (this->population_size * this->cross_rate); ++i) {
            int rand_index_1, rand_index_2;
            do {
                rand_index_1 = rand() % this->population_size;
                rand_index_2 = rand() % this->population_size;
            } while (rand_index_1 == rand_index_2);

            ordered_crossover(population[rand_index_1], population[rand_index_2]);
        }

        for (int i = 0; i < (int) (this->population_size * this->mutation_rate); ++i) {
            int rand_index = rand() % this->population_size;
            inversion_mutation(population[rand_index]);
        }
    }

    int best = INT32_MAX;
    vector<int> best_route = this->population[0];

    for (int k = 0; k < this->population_size; ++k) {
        this->fitness[k] = calculate_route(this->population[k]);
        if(best > this->fitness[k]){
            best = this->fitness[k];
            best_route = this->population[k];
        }
    }

    cout << "Result " << best << endl;
}

void Graph::make_population() {
    this->population.reserve(this->population_size);
    this->fitness.reserve(this->population_size);


    for (int i = 0; i < this->population_size; ++i) {
        vector<int> permutation = make_random_permutation(this->size);
        this->population.push_back(permutation);
        this->fitness.push_back(calculate_route(permutation));
    }
}

void Graph::select() {
    vector<vector<int>> selected_population;
    selected_population.reserve(this->population_size);

    for (int j = 0; j < this->population_size; ++j) {
        int best = INT32_MAX;
        int best_index = -1;
        for (int i = 0; i < this->tournament_number; ++i) {
            int random_index = rand() % this->population_size;
            int random_index_value = this->fitness[random_index];
            if (best > random_index_value) {
                best = random_index_value;
                best_index = random_index;
            }
        }
        selected_population.push_back(this->population[best_index]);
    }
    this->population = selected_population;
}

void Graph::ordered_crossover(vector<int> &first_parent, vector<int> &second_parent) {
    int k1, k2;
    vector<int> first_child(this->size, -1);
    vector<int> second_child(this->size, -1);

    do {
        k1 = rand() % (this->size -2) + 1;
        k2 = rand() % (this->size -2) + 1;  //in case of hitting last index, while loop won't break (numbers from 1 to n-1)
    } while (k1 == k2);

    if (k1 > k2) {
        swap(k1, k2);
    }

    for (int i = k1; i <= k2; ++i) {
        first_child[i] = second_parent[i];
        second_child[i] = first_parent[i];
    }

    vector<int>::iterator child_iterator = first_child.begin() + k2 + 1;
    vector<int>::iterator parent_iterator = first_parent.begin() + k2 + 1;

    while (child_iterator != first_child.begin() + k1) {
        if (first_child.end() ==
            find(first_child.begin(), first_child.end(), *parent_iterator)) { // jesli w potomku nie ma miasta z rodzica
            *child_iterator = *parent_iterator;

            if (child_iterator == first_child.end() - 1)    //end zwraca iterator ustawiony na element 'past the end'
                child_iterator = first_child.begin();       //powrot do poczatku
            else
                child_iterator++;

            if (parent_iterator == first_parent.end() - 1)
                parent_iterator = first_parent.begin();
            else
                parent_iterator++;
        } else {    // jesli miasto juz wystapilo to pomin i idz dalej
            if (parent_iterator == first_parent.end() - 1)
                parent_iterator = first_parent.begin();
            else
                parent_iterator++;
        }
    }

    child_iterator = second_child.begin() + k2 + 1;
    parent_iterator = second_parent.begin() + k2 + 1;

    while (child_iterator != second_child.begin() + k1) {
        if (second_child.end() == find(second_child.begin(), second_child.end(), *parent_iterator)) {
            *child_iterator = *parent_iterator;

            if (child_iterator == second_child.end() - 1)
                child_iterator = second_child.begin();
            else
                child_iterator++;

            if (parent_iterator == second_parent.end() - 1)
                parent_iterator = second_parent.begin();
            else
                parent_iterator++;
        } else {    // jesli miasto juz wystapilo to pomin i idz dalej
            if (parent_iterator == second_parent.end() - 1)
                parent_iterator = second_parent.begin();
            else
                parent_iterator++;
        }
    }

    first_parent = first_child;
    second_parent = second_child;
}

void Graph::inversion_mutation(vector<int> &path) {
    int rand1, rand2;   // rand 1 -dolna granica, rand2 - gorna granica
    do {
        rand1 = rand() % this->size;
        rand2 = rand() % this->size;
    } while (rand1 == rand2);

    if(rand1 > rand2){
        swap(rand1, rand2);
    }

    for(int i = rand1, j = rand2; i < j ; ++i, --j){
        std::swap(path[i], path[j]);
    }
}


