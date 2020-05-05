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
void mostrar(TAREA**, int);
void mostrarTarea(TAREA*);

int main() {
    srand(time(NULL));
    int cantTareas;
    TAREA** tareas;
    TAREA** tareasRealizadas;

    do {
        cout << ">> Ingrese la cantidad de tareas: ";
        cin >> cantTareas;
        if (cantTareas < 0) {
            cout << "!Error: cantidad incorrecta\n";
        }
    } while(cantTareas < 0);

    tareas = new TAREA*[cantTareas];
    tareasRealizadas = new TAREA*[cantTareas];

    cargaTareas(tareas, cantTareas);
    cout << "# Mostrando tareas\n";
    mostrar(tareas, cantTareas);

    return 0;
}

void cargaTareas(TAREA** tarea, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        cout << "\n## TAREA #" << i + 1;
        tarea[i] = new TAREA;
        tarea[i]->id = i + 1;

        char auxDescr[30];
        cout << "\n>> Descripcion: ";
        cin >> auxDescr;
        tarea[i]->descripcion = new char[strlen(auxDescr) + 1];
        strcpy(tarea[i]->descripcion, auxDescr);

        do {
            cout << ">> Duracion: ";
            cin >> tarea[i]->duracion;
            if (tarea[i]->duracion < 10 || tarea[i]->duracion > 100) {
                cout << "!Error: la duracion suele puede ser entre 10 y 100\n";
            }
        } while (tarea[i]->duracion < 10 || tarea[i]->duracion > 100);
    }
    cout << "\n";
}

void mostrar(TAREA** tarea, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        mostrarTarea(tarea[i]);
        cout << "\n";
    }
}

void mostrarTarea(TAREA* tarea) {
    cout << "## TareaID: " << tarea->id;
    cout << "\n# Descripcion: " << tarea->descripcion;
    cout << "\n# Duracion: " << tarea->duracion << "\n";
}