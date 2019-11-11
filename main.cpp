#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

int main() {
    int option;
    Graph graph;
    cout << "Travelling Salesman Problem - MENU";

    do {
        cout << endl;
        cout << "==== MENU GLOWNE ===" << endl;
        cout << "1. Brute Force" << endl;
        cout << "2. Branch and bound" << endl;
        cout << "3. Dynamic programming" << endl;
        cout << "4. Read from file" << endl;
        cout << "5. Read from user" << endl;
        cout << "6. Display" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";
        cin >> option;
        cout << endl;
        string file_name;


        switch (option) {
            case 0:
                return 0;
            case 1:
                graph.brute_force();
                break;
            case 2:
            case 3:
                graph.dynamic_programming();
                break;
            case 4:
                //graph.clean();
                cout << "Pass file name" << endl;
                cin >> file_name;
                graph.read_from_file(file_name);
                break;
            case 5:
                graph.clean();
                graph.read_from_user();
                break;
            case 6:
                graph.print();

        }
    } while (option != 0);


    return 0;
}
