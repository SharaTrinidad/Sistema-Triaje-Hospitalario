#include <iostream>
#include <windows.h>   // Para manejar colores de consola y sonidos (Beep)
#include <string>
#include <locale.h>    // Para configurar idioma y acentos
#include <cstdlib>     // Para system("cls")
using namespace std;

// Configuración de consola
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Para cambiar color de texto en la consola


// Estructura del Paciente

struct Paciente {
    int id;            // Identificador único del paciente
    string nombre;     // Nombre del paciente
    int prioridad;     // Prioridad de atención (1: más urgente, 4: menos urgente)
    string sintoma;    // Síntoma que presenta el paciente
    Paciente* siguiente; // Puntero al siguiente paciente (para cola o pila)
};


// Punteros globales

Paciente* frente = NULL;  // Inicio de la cola de prioridad (pacientes en espera)
Paciente* pila = NULL;    // Pila para historial de pacientes atendidos


// FUNCIONES DE APOYO


// Crear un paciente dinámicamente
Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente(); // Reservar memoria
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;
    nuevo->siguiente = NULL;
    return nuevo;
}


// COLA DE PRIORIDAD (TRIAJE)


// Insertar paciente en la cola de atención según prioridad
void encolarPaciente(Paciente* p) {
    if (p == NULL) return;

    // Se crea una copia del paciente para la cola
    Paciente* nuevo = crearPaciente(p->id, p->nombre, p->prioridad, p->sintoma);

    // Si la cola está vacía o el nuevo paciente tiene mayor prioridad que el frente
    if (frente == NULL || nuevo->prioridad < frente->prioridad) {
        nuevo->siguiente = frente;
        frente = nuevo;
    } else {
        // Buscar posición correcta según prioridad
        Paciente* actual = frente;
        while (actual->siguiente != NULL && actual->siguiente->prioridad <= nuevo->prioridad)
            actual = actual->siguiente;
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

// Mostrar todos los pacientes en la cola
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


// Guardar paciente atendido en la pila (historial)
void pushHistorial(Paciente* atendido) {
    atendido->siguiente = pila;
    pila = atendido;
}

// Atender al siguiente paciente (desencolar)
void desencolarPaciente() {
    if (frente == NULL) {
        cout << "\nNo hay pacientes en espera.\n";
        return;
    }

    // Sacar paciente del frente de la cola
    Paciente* atendido = frente;
    frente = frente->siguiente;

    // Guardarlo en el historial
    pushHistorial(atendido);

    // Cambiar color y sonido según prioridad
    int pr = atendido->prioridad;
    if (pr == 1) SetConsoleTextAttribute(hConsole, 12); // Rojo
    else if (pr == 2) SetConsoleTextAttribute(hConsole, 14); // Amarillo
    else if (pr == 3) SetConsoleTextAttribute(hConsole, 13); // Magenta
    else SetConsoleTextAttribute(hConsole, 10); // Verde

    Beep(600 + (5 - pr) * 150, 180); // Sonido según prioridad
    cout << "\nAtendiendo paciente: " << atendido->nombre
         << " (Prioridad " << atendido->prioridad << ")\n";
    SetConsoleTextAttribute(hConsole, 7); // Restaurar color original
}

// Mostrar historial de pacientes atendidos
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


// Liberar toda la memoria dinámica usada
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


// MENÚ PRINCIPAL

void menuPlanificador() {
    int op;
    do {
        system("cls"); // Limpiar pantalla
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


// PROGRAMA PRINCIPAL

int main() {
    setlocale(LC_ALL, "Spanish"); // Para que acepte acentos en consola
    menuPlanificador();           // Llamada al menú principal
    return 0;
}

