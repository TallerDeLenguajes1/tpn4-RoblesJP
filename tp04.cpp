#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// estructuras
struct Tarea {
    int id;
    char* descripcion;
    int duracion; // [10, 100]
};

// funciones


int main() {
    int cantTareas;
    do {
        cin.clear();
        cout << ">> Ingrese la cantidad de tareas: ";
        cin >> cantTareas;
        if (cantTareas < 0) {
            cout << "!Error: cantidad incorrecta\n";
        }
    } while(cantTareas < 0);

    return 0;
}