#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

// estructuras
typedef struct {
    int id;
    char* descripcion;
    int duracion; // [10, 100]
} TAREA;

// funciones
void cargaTareas(TAREA**, int);

int main() {
    srand(time(NULL));
    int cantTareas;
    TAREA** tareas;
    TAREA** tareasRealizadas;

    do {
        cin.clear();
        cout << ">> Ingrese la cantidad de tareas: ";
        cin >> cantTareas;
        if (cantTareas < 0) {
            cout << "!Error: cantidad incorrecta\n";
        }
    } while(cantTareas < 0);

    tareas = new TAREA*[cantTareas];
    tareasRealizadas = new TAREA*[cantTareas];

    cargaTareas(tareas, cantTareas);


    return 0;
}

void cargaTareas(TAREA** tareas, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        cout << "\n# TAREA #" << i + 1;
        tareas[i] = new TAREA;
        tareas[i]->id = i + 1;

        char auxDescr[30];
        cout << "\n>> Descripcion: ";
        cin >> auxDescr;
        tareas[i]->descripcion = new char[strlen(auxDescr) + 1];
        strcpy(tareas[i]->descripcion, auxDescr);

        do {
            cout << ">> Duracion: ";
            cin >> tareas[i]->duracion;
            if (tareas[i]->duracion < 10 || tareas[i]->duracion > 100) {
                cout << "!Error: la duracion suele puede ser entre 10 y 100\n";
            }
        } while (tareas[i]->duracion < 10 || tareas[i]->duracion > 100);
    }
}