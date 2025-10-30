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

// Punteros globales
Paciente* frente = NULL;  // Cola de prioridad
Paciente* pila = NULL;    // Pila (historial de atendidos)


// FUNCIONES DE APOYO

Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente();
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;
    nuevo->siguiente = NULL;
    return nuevo;
}


// COLA DE PRIORIDAD (TRIAJE)

void encolarPaciente(Paciente* p) {
    if (p == NULL) return;
    Paciente* nuevo = crearPaciente(p->id, p->nombre, p->prioridad, p->sintoma);

    if (frente == NULL || nuevo->prioridad < frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
    } else {
        Paciente* actual = frente;
        while (actual->siguiente != NULL && actual->siguiente->prioridad <= nuevo->prioridad)
            actual = actual->siguiente;
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

void mostrarCola() {
    if (frente == NULL) {
        cout << "\nNo hay pacientes en la cola.\n";
        return;
    }

    Paciente* actual = frente;
    cout << "\n=== COLA DE ATENCIÓN ===\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id
             << " | " << actual->nombre
             << " | Prioridad: " << actual->prioridad
             << " | Síntoma: " << actual->sintoma << endl;
        actual = actual->siguiente;
    }
}

// PILA (HISTORIAL / MEMORIA TEMPORAL)

void pushHistorial(Paciente* atendido) {
    atendido->siguiente = pila;
    pila = atendido;
}

void desencolarPaciente() {
    if (frente == NULL) {
        cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    Paciente* atendido = frente;
    frente = frente->siguiente;
    pushHistorial(atendido);

    int pr = atendido->prioridad;
    if (pr == 1) SetConsoleTextAttribute(hConsole, 12);
    else if (pr == 2) SetConsoleTextAttribute(hConsole, 14);
    else if (pr == 3) SetConsoleTextAttribute(hConsole, 13);
    else SetConsoleTextAttribute(hConsole, 10);

    Beep(600 + (5 - pr) * 150, 180);
    cout << "\nAtendiendo paciente: " << atendido->nombre
         << " (Prioridad " << atendido->prioridad << ")\n";
    SetConsoleTextAttribute(hConsole, 7);
}

void mostrarHistorial() {
    if (pila == NULL) {
        cout << "\nNo hay historial de pacientes atendidos.\n";
        return;
    }

    Paciente* actual = pila;
    cout << "\n=== HISTORIAL DE PACIENTES ATENDIDOS ===\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id
             << " | " << actual->nombre
             << " | Prioridad: " << actual->prioridad << endl;
        actual = actual->siguiente;
    }
}


// LIBERAR MEMORIA

void liberarMemoria() {
    while (frente != NULL) {
        Paciente* t = frente;
        frente = frente->siguiente;
        delete t;
    }
    while (pila != NULL) {
        Paciente* t = pila;
        pila = pila->siguiente;
        delete t;
    }
    cout << "\nMemoria liberada correctamente.\n";
}


// MENÚ PRINCIPAL DEL MÓDULO DE EDY

void menuPlanificador() {
    int op;
    do {
        system("cls");
        cout << "\n========= PLANIFICADOR DE ATENCIÓN =========\n";
        cout << "1. Mostrar cola de pacientes\n";
        cout << "2. Atender siguiente paciente\n";
        cout << "3. Mostrar historial\n";
        cout << "0. Salir\n";
        cout << "Seleccione: ";
        cin >> op;

        switch (op) {
            case 1: mostrarCola(); break;
            case 2: desencolarPaciente(); break;
            case 3: mostrarHistorial(); break;
            case 0: liberarMemoria(); cout << "\nSaliendo del planificador...\n"; break;
            default: cout << "\nOpción inválida.\n"; break;
        }

        if (op != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (op != 0);
}


// PROGRAMA PRINCIPAL DE EDY

int main() {
    setlocale(LC_ALL, "Spanish");
    menuPlanificador();
    return 0;
}


