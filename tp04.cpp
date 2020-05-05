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
TAREA* buscarPorPalabra(TAREA**, char*, int);

int main() {
    srand(time(NULL));
    int cantTareas;
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

void cargaTareas(TAREA** tarea, int cantTareas) {
    char auxDescr[100];
    for (int i = 0; i < cantTareas; i++) {
        cout << "\n## TAREA #" << i + 1;
        tarea[i] = new TAREA;
        tarea[i]->id = i + 1;

        cout << "\n>> Descripcion: ";
        cin.ignore();
        cin.getline(auxDescr, 100);
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

void mostrarTarea(TAREA* tarea) {
    cout << "## TareaID: " << tarea->id;
    cout << "\n# Descripcion: " << tarea->descripcion;
    cout << "\n# Duracion: " << tarea->duracion << "\n";
}

void mostrar(TAREA** tarea, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tarea[i] != NULL) {
            mostrarTarea(tarea[i]);
            cout << "\n";
        }
    }
    cout << "\n";
}

void check(TAREA** tareaPendiente, TAREA** tareaRealizada, int cantTareas) {
    char respuesta;
    for (int i = 0; i < cantTareas; i++) {
        do {
            cout << "-- La tarea #" << tareaPendiente[i]->id << " fue realizada? SI[Y] NO[N]: ";
            cin >> respuesta;
            if (respuesta != 'Y' && respuesta != 'N') {
                cout << "!Error: respuesta incorrecta\n";
            } 
        } while (respuesta != 'Y' && respuesta != 'N');

        if (respuesta == 'Y') {
            tareaRealizada[i] = tareaPendiente[i];
            tareaPendiente[i] = NULL;
        } else {
            tareaRealizada[i] = NULL;
        }
    }
    cout << "\n";
}

TAREA* buscarPorPalabra(TAREA** tareas, char* palabra, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL && strstr(tareas[i]->descripcion, palabra) != NULL) {
            return tareas[i];
        }
    }
    return NULL;
}