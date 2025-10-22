#include <iostream>
#include <string>
using namespace std;

struct Paciente {
    int id;
    string nombre;
    int prioridad;
    string sintoma;
    Paciente* siguiente;
};

Paciente* lista = NULL;

// Crear paciente
Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente();
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Registrar paciente
void registrarPaciente() {
    int id, prioridad;
    string nombre, sintoma;

    cout << "\nREGISTRO DE PACIENTE\n";
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Síntoma: "; getline(cin, sintoma);
    cout << "Prioridad (1-5): "; cin >> prioridad;

    Paciente* nuevo = crearPaciente(id, nombre, prioridad, sintoma);
    if (lista == NULL) lista = nuevo;
    else {
        Paciente* actual = lista;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    cout << "\nPaciente registrado correctamente.\n";
}

// Mostrar pacientes
void mostrarPacientes() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    Paciente* actual = lista;
    cout << "\nLISTA DE PACIENTES:\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id
             << " | " << actual->nombre
             << " | Prioridad: " << actual->prioridad
             << " | Síntoma: " << actual->sintoma << endl;
        actual = actual->siguiente;
    }
}

// Buscar paciente por ID
void buscarPaciente() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    int id;
    cout << "\nIngrese ID a buscar: ";
    cin >> id;

    Paciente* actual = lista;
    while (actual != NULL) {
        if (actual->id == id) {
            cout << "\nPaciente encontrado:\n";
            cout << actual->nombre << " | Prioridad: " << actual->prioridad
                 << " | Síntoma: " << actual->sintoma << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "\nPaciente no encontrado.\n";
}

// Eliminar paciente por ID
void eliminarPaciente() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    int id;
    cout << "\nIngrese ID del paciente a eliminar: ";
    cin >> id;

    Paciente* actual = lista;
    Paciente* anterior = NULL;

    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "\nNo se encontró paciente con ese ID.\n";
        return;
    }

    if (anterior == NULL) lista = actual->siguiente;
    else anterior->siguiente = actual->siguiente;

    delete actual;
    cout << "\nPaciente eliminado correctamente.\n";
}

// Modificar prioridad
void modificarPrioridad() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    int id, nueva;
    cout << "\nIngrese ID del paciente: ";
    cin >> id;
    cout << "Nueva prioridad: ";
    cin >> nueva;

    Paciente* actual = lista;
    while (actual != NULL) {
        if (actual->id == id) {
            actual->prioridad = nueva;
            cout << "\nPrioridad actualizada.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "\nPaciente no encontrado.\n";
}

