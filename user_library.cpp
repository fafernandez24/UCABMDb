#include "user_library.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool validateEmail(const string &email) {
    return email.find('@') != string::npos;
}

void saveUsers(User *head) {
    ofstream file("usuarios.txt");
    User *current = head;
    while (current != NULL) {
        file << current->email << "\t"
             << current->username << "\t"
             << current->age << "\t"
             << current->nationality << endl;
        current = current->next;
    }
    file.close();
}

void displayUsers() {
    ifstream file("usuarios.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void loadUsersFromFile(User **head) {
    ifstream file("usuarios.txt");
    string line;
    while (getline(file, line)) {
        User *newUser = new User;
        newUser->next = NULL;
        newUser->prev = NULL;
        istringstream iss(line);
        iss >> newUser->email;
        iss >> newUser->username;
        iss >> newUser->age;
        getline(iss, newUser->nationality);
        if (*head != NULL) {
            (*head)->prev = newUser;
            newUser->next = *head;
        }
        *head = newUser;
    }
    file.close();
}

bool isUserListEmpty(User *head) {
    return head == NULL;
}

/////////////////////////////////////////////////////////////////////////
void registerUser(User *&head) {
    User *newUser = new User;
    cout << "Ingrese Correo electronico: ";
    cin >> newUser->email;
    while (!validateEmail(newUser->email)) {
        cout << "Correo electronico invalido. Ingrese nuevamente: ";
        cin >> newUser->email;
    }
    cout << "Ingrese nombre de usuario: ";
    cin >> newUser->username;
    cout << "Ingrese edad: ";
    cin >> newUser->age;
    cout << "Ingrese nacionalidad: ";
    cin >> newUser->nationality;
    newUser->next = head;
    newUser->prev = NULL;
    if (head != NULL) {
        head->prev = newUser;
    }
    head = newUser;
}//////////////////////////////////////////////////////////////////

void deleteUser(User *&head, const std::string &email) {
    User *current = head;
    while (current != NULL) {
        if (current->email == email) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            delete current;
            cout << "Usuario con correo electronico " << email << " ha sido eliminado." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Usuario con correo electronico " << email << " no ha sido encontrado." << endl;
}
