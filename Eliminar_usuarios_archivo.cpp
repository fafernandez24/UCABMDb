//* Procedimiento para eliminar un usuario del archivo *//

void deleteUserFromFile(string email) {
    ifstream file("usersfile.txt");
    if (file.fail()) {
        cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
        return;
    }

    Users *head = nullptr;
    string line;
    while (getline(file, line)) {
        Users *new_user = new Users;
        new_user->email = line;
        getline(file, line);
        new_user->years_old = stoi(line);
        getline(file, new_user->country);
        
        // Enlazar el nuevo usuario
        new_user->next_user = head;
        new_user->prev_user = nullptr;
        if (head) {
            head->prev_user = new_user;
        }
        head = new_user;
    }
    file.close();

    // Eliminar el usuario especificado
    Users *aux = head;
    while (aux) {
        if (aux->email == email) {
            // Si es el primer usuario
            if (aux->prev_user) {
                aux->prev_user->next_user = aux->next_user;
            } else {
                head = aux->next_user; // Actualizar la cabeza
            }
            if (aux->next_user) {
                aux->next_user->prev_user = aux->prev_user;
            }
            delete aux; // Liberar memoria
            cout << "Usuario eliminado correctamente.\n";
            break;
        }
        aux = aux->next_user;
    }

    // Escribir de nuevo en el archivo
    ofstream out_file("usersfile.txt");
    aux = head;
    while (aux) {
        out_file << aux->email << endl;
        out_file << aux->years_old << endl;
        out_file << aux->country << endl;
        aux = aux->next_user;
    }
    out_file.close();
}
