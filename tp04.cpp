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
void mostrarTarea(TAREA*);
void mostrar(TAREA**, int);
void check(TAREA**, TAREA**, int);
TAREA* buscarPorId(TAREA**, int, int);

int main() {
    srand(time(NULL));
    int cantTareas;
    int tareaID;
    TAREA** tareasPendientes;
    TAREA** tareasRealizadas;

    do {
        cout << ">> Ingrese la cantidad de tareas: ";
        cin >> cantTareas;
        if (cantTareas < 0) {
            cout << "!Error: cantidad incorrecta\n";
        }
    } while(cantTareas < 0);

    tareasPendientes = new TAREA*[cantTareas];
    tareasRealizadas = new TAREA*[cantTareas];

    cargaTareas(tareasPendientes, cantTareas);
    check(tareasPendientes, tareasRealizadas, cantTareas);
    cout << "# Mostrando tareas realizadas\n";
    mostrar(tareasRealizadas, cantTareas);
    cout << "# Mostrando tareas pendientes\n";
    mostrar(tareasPendientes, cantTareas);

    delete[] tareasPendientes;
    delete[] tareasRealizadas;
    return 0;
}

void cargaTareas(TAREA** tareas, int cantTareas) {
    char auxDescr[100];
    for (int i = 0; i < cantTareas; i++) {
        cout << "\n## TAREA #" << i + 1;
        tareas[i] = new TAREA;
        tareas[i]->id = i + 1;

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
    cout << "\n";
}

void mostrarTarea(TAREA* tarea) {
    cout << "## TareaID: " << tarea->id;
    cout << "\n# Descripcion: " << tarea->descripcion;
    cout << "\n# Duracion: " << tarea->duracion << "\n";
}

void mostrar(TAREA** tareas, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL) {
            mostrarTarea(tareas[i]);
            cout << "\n";
        }
    }
    cout << "\n";
}

void check(TAREA** tareasPendientes, TAREA** tareasRealizadas, int cantTareas) {
    char respuesta;
    for (int i = 0; i < cantTareas; i++) {
        do {
            cout << "-- La tarea #" << tareasPendientes[i]->id << " fue realizada? SI[Y] NO[N]: ";
            cin >> respuesta;
            if (respuesta != 'Y' && respuesta != 'N') {
                cout << "!Error: respuesta incorrecta\n";
            } 
        } while (respuesta != 'Y' && respuesta != 'N');

        if (respuesta == 'Y') {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        } else {
            tareasRealizadas[i] = NULL;
        }
    }
    cout << "\n";
}

TAREA* buscarPorId(TAREA** tareas, int id, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL && tareas[i]->id == id) {
            return tareas[i];
        }
    }
    return NULL;
}