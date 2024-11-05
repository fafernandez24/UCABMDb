#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Definición de la estructura 
struct Users {
    int id;
    string email;
    int years_old;
    string country;
    Users *next_user;
    Users *prev_user;
};

// Eliminar un usuario del archivo
void deleteUserFromFile(string email) {
    ifstream file("usersfile.txt");
    if (file.fail()) {
        cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
        return;
    }

    Users *head = nullptr;
    Users *tail = nullptr;
    string line;
    
    // Leer usuarios del archivo 
    while (getline(file, line)) {
        Users *new_user = new Users;
        new_user->id = stoi(line); // Leer y asignar el ID
        getline(file, new_user->email);
        getline(file, line);
        new_user->years_old = stoi(line);
        getline(file, new_user->country);

        new_user->next_user = nullptr;
        new_user->prev_user = tail;

        if (tail != nullptr) {
            tail->next_user = new_user;
        } else {
            head = new_user;
        }
        tail = new_user;
    }
    file.close();

    // Eliminar el usuario especificado
    Users *aux = head;
    bool found = false;
    while (aux) {
        if (aux->email == email) {
            if (aux->prev_user) {
                aux->prev_user->next_user = aux->next_user;
            } else {
                head = aux->next_user; // Actualizar la cabeza
            }
            if (aux->next_user) {
                aux->next_user->prev_user = aux->prev_user;
            }
            delete aux; // Liberar memoria
            found = true;
            cout << "Usuario eliminado correctamente.\n";
            break;
        }
        aux = aux->next_user;
    }

    if (!found) {
        cout << "ERROR. No se encontro el usuario!\n";
        return;
    }

    // Escribir de nuevo en el archivo
    ofstream out_file("usersfile.txt");
    if (out_file.fail()) {
        cout << "ERROR. No se pudo abrir el archivo para escribir.\n";
        return;
    }

    aux = head; 
    while (aux) {
        out_file << aux->id << endl; // Escribir el ID
        out_file << aux->email << endl;
        out_file << aux->years_old << endl;
        out_file << aux->country << endl;
        aux = aux->next_user;
    }
    out_file.close(); 
}



