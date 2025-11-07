


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
