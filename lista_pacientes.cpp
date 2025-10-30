#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

//  Manejo de colores
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct Paciente {
    int id;
    string nombre;
    int prioridad; // 1=Crítico, 5=Leve
    string sintoma;
    Paciente* siguiente;
};

Paciente* lista = NULL;

// Crear un nuevo paciente
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

    cout << "\n=== REGISTRO DE PACIENTE ===\n";
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Síntoma: "; getline(cin, sintoma);
    cout << "Prioridad (1-5): "; cin >> prioridad;

    Paciente* nuevo = crearPaciente(id, nombre, prioridad, sintoma);
    if (lista == NULL)
        lista = nuevo;
    else {
        Paciente* actual = lista;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    // ?? Color y sonido según prioridad
    switch (prioridad) {
        case 1:
            SetConsoleTextAttribute(hConsole, 12);
            Beep(1200, 200);
            cout << "\n??  Paciente CRÍTICO registrado.\n";
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, 14);
            Beep(1000, 150);
            cout << "\n??  Paciente URGENTE registrado.\n";
            break;
        case 3:
            SetConsoleTextAttribute(hConsole, 13);
            Beep(800, 150);
            cout << "\n??  Paciente MODERADO registrado.\n";
            break;
        default:
            SetConsoleTextAttribute(hConsole, 10);
            Beep(600, 120);
            cout << "\n?? Paciente LEVE registrado.\n";
            break;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

// Mostrar todos los pacientes
void mostrarPacientes() {
    if (lista == NULL) {
        cout << "\n?? No hay pacientes registrados.\n";
        return;
    }
    Paciente* actual = lista;
    cout << "\n=== LISTA DE PACIENTES ===\n";
    while (actual != NULL) {
        cout << "ID: " << actual->id << " | " << actual->nombre
             << " | Prioridad: " << actual->prioridad

