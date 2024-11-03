#include <iostream>
#include "user_library.h"

using namespace std;
////agregar mas de un usuario///////
int main() {
    User *head = NULL;
    char option;
    do {
        registerUser(head);
        cout << "Quieres registrar otro usuario? (y/n): ";
        cin >> option;
    } while (option == 'y' || option == 'Y');

    saveUsers(head);
    cout << "\nRegistrar usuario:\n";
    displayUsers();

    return 0;
}
