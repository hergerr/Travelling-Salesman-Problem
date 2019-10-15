#include <iostream>
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

        switch(option) {
            case 0:
                return 0;
            case 1:
            case 2:
            case 3:
            case 4:
                graph.clean();
                graph.read_from_file("data17.txt");
                break;
            case 5:
                graph.clean();
                graph.read_from_user();
                break;
            case 6:
                graph.print();

        }
    }
    while( option != 0);



    return 0;
}
