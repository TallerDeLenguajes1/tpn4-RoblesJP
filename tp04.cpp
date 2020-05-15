#include <cstring>
#include <iostream>
using namespace std;

// estructuras
typedef struct {
    int id;
    char* descripcion;
    int duracion; // [10, 100]
} TAREA;

struct NODO {
    TAREA* tarea;
    struct NODO* siguiente;
};
typedef struct NODO* LISTA;

// funciones
LISTA crearLista();
TAREA* crearTarea(int, char*, int);
struct NODO* crearNodo(TAREA*);
void insertarNodo(LISTA*, struct NODO*);
struct NODO* quitarNodo(LISTA*);
void mostrarTarea(TAREA* tarea);
void mostrar(LISTA L);
TAREA* buscarPorPalabra(LISTA, char*);
TAREA* buscarPorId(LISTA, int);

int main() {
    int cantTareas;
    int buscarID;
    char buscarPalabra[100];
    LISTA tareas = crearLista();
    LISTA tareasPendientes = crearLista();
    LISTA tareasRealizadas = crearLista();

    // cantidad de tareas
    do {
        cout << ">> Ingrese la cantidad de tareas: ";
        cin >> cantTareas;
        if (cantTareas < 0) {
            cout << "!Error: cantidad incorrecta\n";
        }
    } while(cantTareas < 0);

    // carga de tareas
    for (int i = 0; i < cantTareas; i++) {
        cout << "\n## TAREA #" << i + 1;
        int id = i + 1;
        char descripcion[50];
        cout << "\n>> Descripcion: ";
        cin >> descripcion;
        int duracion;
        do {
            cout << ">> Duracion: ";
            cin >> duracion;
            if (duracion < 10 || duracion > 100) {
                cout << "!Error: la duracion suele puede ser entre 10 y 100\n";
            }
        } while (duracion < 10 || duracion > 100);
        TAREA* nuevaTarea = crearTarea(id, descripcion, duracion);
        struct NODO* nuevoNodo = crearNodo(nuevaTarea);
        insertarNodo(&tareas, nuevoNodo);
    }
    cout << "\n";

    // pregunta si la tarea fue realizada
    char respuesta;
    while (tareas != NULL) {
        do {
            cout << ">> La tarea #" << tareas->tarea->id << " fue realizada? SI[Y] NO[N]: ";
            cin >> respuesta;
            if (respuesta != 'Y' && respuesta != 'N') {
                cout << "!Error: respuesta incorrecta\n";
            } 
        } while (respuesta != 'Y' && respuesta != 'N');

        if (respuesta == 'Y') {
            insertarNodo(&tareasRealizadas, quitarNodo(&tareas));
        } else {
            insertarNodo(&tareasPendientes, quitarNodo(&tareas));
        }
    }

    // muestra las tareas realizadas
    cout << "\n-- Mostrando tareas realizadas\n";
    mostrar(tareasRealizadas);
    // muestra las tareas pendientes
    cout << "-- Mostrando tareas pendientes\n";
    mostrar(tareasPendientes);

    
    // buscar tarea por palabra
    cout << ">> Buscar tarea por palabra: ";
    cin >> buscarPalabra;
    cout << "-- Buscando en tareas pendientes...\n";
    if (buscarPorPalabra(tareasPendientes, buscarPalabra) != NULL) {
        mostrarTarea(buscarPorPalabra(tareasPendientes, buscarPalabra));
    } else {
        cout << "No existe tarea con la palabra \"" << buscarPalabra << "\"" << " en la lista de tareas pendientes\n";
    }
    cout << "-- Buscando en tareas realizadas...\n";
    if (buscarPorPalabra(tareasRealizadas, buscarPalabra) != NULL) {
        mostrarTarea(buscarPorPalabra(tareasRealizadas, buscarPalabra));
    } else {
        cout << "No existe tarea con la palabra \"" << buscarPalabra << "\"" << " en la lista de tareas realizadas";
    }

    // buscar tarea por id
    cout << ">> Buscar tarea por id: ";
    cin >> buscarID;
    cout << "-- Buscando en tareas pendientes...\n";
    if (buscarPorId(tareasPendientes, buscarID) != NULL) {
        mostrarTarea(buscarPorId(tareasPendientes, buscarID));
    } else {
        cout << "No existe tarea con id " << buscarID << " en la lista de tareas pendientes\n\n";
    }
    cout << "-- Buscando en tareas realizadas...\n";
    if (buscarPorId(tareasRealizadas, buscarID) != NULL) {
        mostrarTarea(buscarPorId(tareasRealizadas, buscarID));
    } else {
        cout << "No existe tarea con id " << buscarID << " en la lista de tareas realizadas";
    }

    cout << "\n";
    return 0;
}

LISTA crearLista() {
    return NULL;
}

TAREA* crearTarea(int id, char* descripcion, int duracion) {
    TAREA* nuevaTarea = new TAREA;
    nuevaTarea->id = id;
    nuevaTarea->descripcion = descripcion;
    nuevaTarea->duracion = duracion;
    return nuevaTarea;
}

struct NODO* crearNodo(TAREA* tarea) {
    struct NODO* nuevoNodo = new struct NODO;
    nuevoNodo->tarea = tarea;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void insertarNodo(LISTA* L, struct NODO* nodo) {
    nodo->siguiente = *L;
    *L = nodo;
}

struct NODO* quitarNodo(LISTA* L) {
    struct NODO* aux;
    aux = *L;
    *L = (*L)->siguiente;
    aux->siguiente = NULL;
    return aux;
}

void mostrarTarea(TAREA* tarea) {
    cout << "## TareaID: " << tarea->id;
    cout << "\n# Descripcion: " << tarea->descripcion;
    cout << "\n# Duracion: " << tarea->duracion << "\n";
    cout << "\n";
}

void mostrar(LISTA L) {
    while (L != NULL) {
        mostrarTarea(L->tarea);
        L = L->siguiente;
    }
}   

TAREA* buscarPorPalabra(LISTA L, char* palabra) {
    while (L != NULL) {
        if (strstr(L->tarea->descripcion, palabra) != NULL) {
            return L->tarea;
        }
        L = L->siguiente;
    }
    return NULL;
}

TAREA* buscarPorId(LISTA L, int id) {
     while (L != NULL) {
        if (L->tarea->id == id) {
            return L->tarea;
        }
        L = L->siguiente;
    }
    return NULL;
}