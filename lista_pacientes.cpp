#include <iostream>
#include <windows.h>
#include <string>
#include <locale.h>
#include <cstdlib>
using namespace std;

// Configuración de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Estructura del paciente
struct Paciente {
    int id;
    string nombre;
    int prioridad;
    string sintoma;
    Paciente* siguiente;
};

// Lista enlazada principal
Paciente* lista = NULL;


// FUNCIONES DE LISTA (SHARA)

Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente();
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;
    nuevo->siguiente = NULL;
    return nuevo;
}

void registrarPaciente() {
    int id, prioridad;
    string nombre, sintoma;

    cout << "\n=== REGISTRO DE PACIENTE ===\n";
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

    // Colores según prioridad
    if (prioridad == 1) SetConsoleTextAttribute(hConsole, 12);
    else if (prioridad == 2) SetConsoleTextAttribute(hConsole, 14);
    else if (prioridad == 3) SetConsoleTextAttribute(hConsole, 13);
    else SetConsoleTextAttribute(hConsole, 10);

    Beep(800, 200);
    cout << "\nPaciente registrado correctamente.\n";
    SetConsoleTextAttribute(hConsole, 7);
}

void mostrarPacientes() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    Paciente* actual = lista;
    cout << "\n=== LISTA DE PACIENTES ===\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id
             << " | " << actual->nombre
             << " | Prioridad: " << actual->prioridad
             << " | Síntoma: " << actual->sintoma << endl;
        actual = actual->siguiente;
    }
}

void buscarPaciente() {
    if (lista == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    int id;
    cout << "\nIngrese ID del paciente a buscar: ";
    cin >> id;

    Paciente* actual = lista;
    while (actual != NULL) {
        if (actual->id == id) {
            cout << "\nPaciente encontrado: "
                 << actual->nombre << " | Prioridad " << actual->prioridad << endl;
            return;
        }
        actual = actual->siguiente;
    }
    cout << "\nPaciente no encontrado.\n";
}

void eliminarPaciente() {
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

    cout << "\nPaciente " << actual->nombre << " eliminado.\n";
    delete actual;
}

void modificarPrioridad() {
    int id, nueva;
    cout << "\nIngrese ID del paciente: ";
    cin >> id;
    cout << "Nueva prioridad: ";
    cin >> nueva;

    Paciente* actual = lista;
    while (actual != NULL) {
        if (actual->id == id) {
            actual->prioridad = nueva;
            cout << "\nPrioridad actualizada correctamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "\nPaciente no encontrado.\n";
}


// MENÚ DE SHARA

void menuShara() {
    int op;
    do {
        system("cls");
        cout << "\n========= GESTOR DE PACIENTES =========\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Mostrar pacientes\n";
        cout << "3. Buscar paciente\n";
        cout << "4. Eliminar paciente\n";
        cout << "5. Modificar prioridad\n";
        cout << "0. Salir\n";
        cout << "Seleccione: "; cin >> op;

        switch (op) {
            case 1: registrarPaciente(); break;
            case 2: mostrarPacientes(); break;
            case 3: buscarPaciente(); break;
            case 4: eliminarPaciente(); break;
            case 5: modificarPrioridad(); break;
            case 0: cout << "\nSaliendo del módulo de Shara...\n"; break;
            default: cout << "\nOpción inválida.\n"; break;
        }

        if (op != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (op != 0);
}


// MAIN DE SHARA

int main() {
    setlocale(LC_ALL, "Spanish");
    menuShara();
    return 0;
}

