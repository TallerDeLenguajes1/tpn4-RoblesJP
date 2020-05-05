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
TAREA* buscarPorId(TAREA**, int, int);

int main() {
    srand(time(NULL));
    int cantTareas;
    int buscarID;
    char buscarPalabra[100];
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
    cout << "-- Mostrando tareas realizadas\n";
    mostrar(tareasRealizadas, cantTareas);
    cout << "-- Mostrando tareas pendientes\n";
    mostrar(tareasPendientes, cantTareas);

    cout << ">> Filtrar tarea por palabra: ";
    cin >> buscarPalabra;
    cout << "-- Buscando en tareas pendientes...\n";
    if (buscarPorPalabra(tareasPendientes, buscarPalabra, cantTareas) != NULL) {
        mostrarTarea(buscarPorPalabra(tareasPendientes, buscarPalabra, cantTareas));
    } else {
        cout << "No existe tarea con la palabra \"" << buscarPalabra << "\"" << " en la lista de tareas pendientes\n";
    }
    cout << "\n-- Buscando en tareas realizadas...\n";
    if (buscarPorPalabra(tareasRealizadas, buscarPalabra, cantTareas) != NULL) {
        mostrarTarea(buscarPorPalabra(tareasRealizadas, buscarPalabra, cantTareas));
    } else {
        cout << "No existe tarea con la palabra \"" << buscarPalabra << "\"" << " en la lista de tareas realizadas";
    }

    cout << "\n>> Filtrar tarea por id: ";
    cin >> buscarID;
    cout << "-- Buscando en tareas pendientes...\n";
    if (buscarPorId(tareasPendientes, buscarID, cantTareas) != NULL) {
        mostrarTarea(buscarPorId(tareasPendientes, buscarID, cantTareas));
    } else {
        cout << "No existe tarea con id " << buscarID << " en la lista de tareas pendientes\n";
    }
    cout << "\n-- Buscando en tareas realizadas...\n";
    if (buscarPorId(tareasRealizadas, buscarID, cantTareas) != NULL) {
        mostrarTarea(buscarPorId(tareasRealizadas, buscarID, cantTareas));
    } else {
        cout << "No existe tarea con id " << buscarID << " en la lista de tareas realizadas";
    }

    cout << "\n";

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
        cin.ignore();
        cin.getline(auxDescr, 100);
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
            cout << ">> La tarea #" << tareasPendientes[i]->id << " fue realizada? SI[Y] NO[N]: ";
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

TAREA* buscarPorPalabra(TAREA** tareas, char* palabra, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL && strstr(tareas[i]->descripcion, palabra) != NULL) {
            return tareas[i];
        }
    }
    return NULL;
}

TAREA* buscarPorId(TAREA** tareas, int id, int cantTareas) {
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i] != NULL && tareas[i]->id == id) {
            return tareas[i];
        }
    }
    return NULL;
}