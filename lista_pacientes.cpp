#include <iostream>     // Librería estándar para entrada y salida de datos (cout, cin)
#include <windows.h>    // Permite usar funciones del sistema Windows (colores, sonidos)
#include <string>       // Librería para manejar cadenas de texto (string)
#include <locale.h>     // Permite configurar idioma y caracteres regionales (tildes, ñ)
#include <cstdlib>      // Contiene funciones del sistema (como system("cls"))
using namespace std;


// CONFIGURACIÓN DE CONSOLA

// Se obtiene el identificador de la consola para poder cambiar colores del texto.
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


// ESTRUCTURA DE DATOS PRINCIPAL


// Estructura "Paciente" que almacena los datos de cada paciente.
// Cada nodo representa un paciente dentro de la lista enlazada.
struct Paciente {
    int id;                 // Identificador único del paciente
    string nombre;          // Nombre completo
    int prioridad;          // Nivel de prioridad (1 = emergencia, 5 = leve)
    string sintoma;         // Descripción del síntoma principal
    Paciente* siguiente;    // Puntero al siguiente paciente (estructura dinámica enlazada)
};

// Puntero principal de la lista enlazada (inicio de la lista de pacientes)
Paciente* lista = NULL;



// FUNCIONES DEL MÓDULO DE SHARA

// Crea un nuevo paciente con los datos proporcionados.
// Devuelve un puntero al nuevo nodo creado.

Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente();   // Reserva memoria dinámica para un nuevo paciente
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;
    nuevo->siguiente = NULL;            // Al crearse, no apunta a nadie
    return nuevo;
}


// Registra un nuevo paciente en la lista enlazada.
// Permite ingresar los datos y asigna un color según prioridad.

void registrarPaciente() {
    int id, prioridad;
    string nombre, sintoma;

    cout << "\n=== REGISTRO DE PACIENTE ===\n";
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Síntoma: "; getline(cin, sintoma);
    cout << "Prioridad (1-5): "; cin >> prioridad;

    // Se crea el nuevo paciente
    Paciente* nuevo = crearPaciente(id, nombre, prioridad, sintoma);

    // Si la lista está vacía, el nuevo paciente será el primero.
    if (lista == NULL) lista = nuevo;
    else {
        // Si no, se recorre hasta el final para agregarlo al final de la lista.
        Paciente* actual = lista;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    // Cambia el color del texto según la prioridad (emergencia = rojo, leve = verde)
    if (prioridad == 1) SetConsoleTextAttribute(hConsole, 12); // Rojo
    else if (prioridad == 2) SetConsoleTextAttribute(hConsole, 14); // Amarillo
    else if (prioridad == 3) SetConsoleTextAttribute(hConsole, 13); // Magenta
    else SetConsoleTextAttribute(hConsole, 10); // Verde

    // Efecto de sonido para confirmar el registro
    Beep(800, 200);
    cout << "\nPaciente registrado correctamente.\n";

    // Se restablece el color al normal (blanco)
    SetConsoleTextAttribute(hConsole, 7);
}


// Muestra todos los pacientes registrados en la lista enlazada.
// Recorre la lista desde el inicio hasta el final.

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
        actual = actual->siguiente; // Avanza al siguiente nodo
    }
}


// Busca un paciente en la lista por su ID.
// Si lo encuentra, muestra sus datos.

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


// Elimina un paciente de la lista enlazada según su ID.
// Libera la memoria del nodo eliminado.

void eliminarPaciente() {
    int id;
    cout << "\nIngrese ID del paciente a eliminar: ";
    cin >> id;

    Paciente* actual = lista;
    Paciente* anterior = NULL;

    // Busca el paciente en la lista
    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si no se encuentra el ID
    if (actual == NULL) {
        cout << "\nNo se encontró paciente con ese ID.\n";
        return;
    }

    // Caso 1: el paciente a eliminar es el primero de la lista
    if (anterior == NULL) lista = actual->siguiente;
    // Caso 2: el paciente está en medio o al final
    else anterior->siguiente = actual->siguiente;

    cout << "\nPaciente " << actual->nombre << " eliminado.\n";
    delete actual; // Libera la memoria del nodo eliminado
}


// Permite modificar la prioridad de un paciente ya registrado.
// Se busca por ID y se actualiza el valor de prioridad.

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


// MENÚ PRINCIPAL DEL MÓDULO DE SHARA

void menuShara() {
    int op;
    do {
        system("cls"); // Limpia la pantalla antes de mostrar el menú
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

        // Espera una tecla antes de volver al menú
        if (op != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (op != 0);
}

// FUNCIÓN PRINCIPAL (MAIN)

int main() {
    setlocale(LC_ALL, "Spanish"); // Configura el idioma para tildes y ñ
    menuShara();                  // Ejecuta el menú principal de Shara
    return 0;
}

