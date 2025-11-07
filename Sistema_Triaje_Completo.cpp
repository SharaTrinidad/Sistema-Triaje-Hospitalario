#include <iostream>   // Librería estándar para entrada y salida de datos (cout, cin)
#include <windows.h>  // Permite el uso de colores en consola y funciones como Beep()
#include <string>     // Para usar variables tipo string
#include <locale.h>   // Permite configurar idioma (tildes, ñ)
#include <cstdlib>    // Para funciones del sistema como system("cls")

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Manejo de color en consola

// ESTRUCTURA DEL PACIENTE
// Cada nodo de la lista representa a un paciente con sus datos básicos
struct Paciente {
    int id; 				// Identificador único del paciente
    string nombre;			// Nombre del paciente
    int prioridad;			// Nivel de prioridad (1 = crítica, 5 = leve)
    string sintoma;			// Síntoma principal
    Paciente* siguiente;	// Puntero al siguiente paciente en la lista
};

// Punteros globales , se usan para manejar las 3 estructuras dinámicas
Paciente* lista = NULL;   // Lista enlazada de pacientes registrados
Paciente* frente = NULL;  // Cola de prioridad (triaje)
Paciente* pila = NULL;    // Pila (historial de pacientes atendidos)


// FUNCIÓN: Crear un nuevo paciente (nodo de la lista)

Paciente* crearPaciente(int id, string nombre, int prioridad, string sintoma) {
    Paciente* nuevo = new Paciente();  // Se reserva memoria dinámica
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sintoma = sintoma;		//Todavia no apunta a nadie
    nuevo->siguiente = NULL;
    return nuevo;
}

// FUNCIÓN: Registrar paciente con validaciones
void registrarPaciente() {
    int id, prioridad;
    string nombre, sintoma;
    bool idUnico = false;  // Verifica que el ID no se repita

    cout << "\n=== REGISTRO DE PACIENTE ===\n";
    
    // VALIDACIÓN DE ID (único y positivo)
    do {
        cout << "ID: ";
        cin >> id;

        if (id <= 0) {
            cout << "Error: el ID debe ser un número positivo.\n";
            continue;
        }

        // Verificar si el ID ya existe en la lista
        idUnico = true;
        Paciente* actual = lista;
        while (actual != NULL) {
            if (actual->id == id) {
                cout << "Error: ya existe un paciente con ese ID.\n";
                idUnico = false;
                break;
            }
            actual = actual->siguiente;
        }

    } while (!idUnico);

    cin.ignore(); // Limpia el buffer antes de usar getline()


    //  VALIDAR NOMBRE (no vacío)
    cout << "Nombre: ";
    getline(cin, nombre);
    while (nombre == "") {
        cout << "Error: el nombre no puede estar vacío. Ingrese nuevamente: ";
        getline(cin, nombre);
    }

    //  VALIDAR SÍNTOMA (no vacío)
    cout << "Síntoma: ";
    getline(cin, sintoma);
    while (sintoma == "") {
        cout << "Error: el síntoma no puede estar vacío. Ingrese nuevamente: ";
        getline(cin, sintoma);
    }

    // ?? VALIDAR PRIORIDAD (entre 1 y 5)
    cout << "Prioridad (1-5): ";
    cin >> prioridad;
    while (prioridad < 1 || prioridad > 5) {
        cout << "Error: la prioridad debe estar entre 1 y 5. Intente nuevamente: ";
        cin >> prioridad;
    }
    
	// Crear el nuevo paciente
    Paciente* nuevo = crearPaciente(id, nombre, prioridad, sintoma);
    
    // Insertar al final de la lista
    if (lista == NULL) lista = nuevo;
    else {
        Paciente* actual = lista;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
    }

    // Colores según prioridad
    if (prioridad == 1) SetConsoleTextAttribute(hConsole, 12);  // Rojo (crítico)
    else if (prioridad == 2) SetConsoleTextAttribute(hConsole, 14); // Amarillo (media)
    else if (prioridad == 3) SetConsoleTextAttribute(hConsole, 13); // Magenta
    else SetConsoleTextAttribute(hConsole, 10); // Verde (leve)

    Beep(800, 200); // Sonido al registrar
    cout << "\nPaciente registrado correctamente.\n";
    
    SetConsoleTextAttribute(hConsole, 7); // Restaurar color normal
}

// FUNCIÓN: Mostrar lista completa de pacientes registrados
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

// FUNCIÓN: Buscar paciente por ID
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

// FUNCIÓN: Eliminar paciente de la lista por ID
void eliminarPaciente() {
    int id;
    cout << "\nIngrese ID del paciente a eliminar: ";
    cin >> id;

    Paciente* actual = lista;
    Paciente* anterior = NULL;

	// Buscar paciete en la lista
    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    
	// Si no se encontró el ID del paciente
    if (actual == NULL) {
        cout << "\nNo se encontró paciente con ese ID.\n";
        return;
    }
    
	// Si el paciente a eliminar es el primero
    if (anterior == NULL) lista = actual->siguiente;
    else anterior->siguiente = actual->siguiente;

    cout << "\nPaciente " << actual->nombre << " eliminado.\n";
    delete actual; // lliberar memoria del nodo eliminado
}


// FUNCIÓN: Modificar prioridad de un paciente
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

//Edy
// COLA DE PRIORIDAD (TRIAJE)
// Esta cola se usa para ordenar pacientes según urgencia médica.
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

// Prepara la cola en base a la lista de pacientes
void prepararCola() {
    while (frente != NULL) {
        Paciente* t = frente; //Guardamos el primer nodo temporalmente
        frente = frente->siguiente;    // Avanzamos al siguiente nodo
        delete t;						// Liberamos la memoriadel nodo anterior
    }
    Paciente* actual = lista;			
    while (actual != NULL) {
        encolarPaciente(actual);		// la función se encarga de insertarlos en orden de prioridad
        actual = actual->siguiente;		// pasamos al siguiente paciente de la lista
    }
    cout << "\nCola creada según prioridad.\n";
}

// Mostrar pacientes en la cola (orden de atención)
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


// PILA (HISTORIAL DE ATENDIDOS)
// Se usa una pila para registrar el orden en que fueron atendidos.
void pushHistorial(Paciente* atendido) {
    atendido->siguiente = pila;
    pila = atendido;
}

// Atiende al paciente con mayor prioridad y lo pasa al historial
void atenderPaciente() {
    if (frente == NULL) {
        cout << "\nNo hay pacientes en la cola.\n";
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

// Mostrar el historial completo (último atendido primero)
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


// LIBERAR MEMORIA al cerrar el programa

void liberarMemoria() {
    while (lista != NULL) { Paciente* t = lista; lista = lista->siguiente; delete t; }
    while (frente != NULL) { Paciente* t = frente; frente = frente->siguiente; delete t; }
    while (pila != NULL) { Paciente* t = pila; pila = pila->siguiente; delete t; }
    cout << "\nMemoria liberada correctamente.\n";
}


// MENÚ PRINCIPAL

void menu() {
    int op;
    do {
        system("cls");
        cout << "\n========= SISTEMA DE TRIAJE HOSPITALARIO =========\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Mostrar pacientes\n";
        cout << "3. Buscar paciente\n";
        cout << "4. Eliminar paciente\n";
        cout << "5. Modificar prioridad\n";
        cout << "6. Preparar cola de atención\n";
        cout << "7. Mostrar cola de atención\n";
        cout << "8. Atender siguiente paciente\n";
        cout << "9. Mostrar historial\n";
        cout << "0. Salir\n";
        cout << "Seleccione: "; cin >> op;

        switch (op) {
            case 1: registrarPaciente(); break;
            case 2: mostrarPacientes(); break;
            case 3: buscarPaciente(); break;
            case 4: eliminarPaciente(); break;
            case 5: modificarPrioridad(); break;
            case 6: prepararCola(); break;
            case 7: mostrarCola(); break;
            case 8: atenderPaciente(); break;
            case 9: mostrarHistorial(); break;
            case 0: liberarMemoria(); cout << "\nSaliendo del sistema...\n"; break;
            default: cout << "\nOpción inválida.\n"; break;
        }

        if (op != 0) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore();
            cin.get();  // Espera una tecla para continuar
        }

    } while (op != 0);
}


// Función principal MAIN

int main() {
    setlocale(LC_ALL, "Spanish"); // Permite usar tildes y ñ
    menu(); 					  // Inicia el menú del programa
    return 0;
}
