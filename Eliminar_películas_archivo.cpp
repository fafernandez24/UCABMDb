#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// Definición de la estructura 
struct Movie {
    string movie_name;
    int movie_premiere;
    string movie_type;
    int movie_time;
    Movie *next_movie;
    Movie *prev_movie;
};

void deleteMovieFromFile(string movie_name) {
    // Abrir el archivo 
    ifstream file("moviesfile.txt");
    if (file.fail()) {
        cout << "ERROR  No fue posible abrir el archivo!\n";
        return;
    }

    Movie *head = nullptr; 
    Movie *tail = nullptr; 
    string line;
    
    // Leer películas del archivo y crear la lista 
    while (getline(file, line)) {
        Movie *new_movie = new Movie;
        new_movie->movie_name = line;
        getline(file, line);
        new_movie->movie_premiere = stoi(line);
        getline(file, new_movie->movie_type);
        getline(file, line);
        new_movie->movie_time = stoi(line);

        new_movie->next_movie = nullptr;
        new_movie->prev_movie = tail;

        if (tail != nullptr) {
            tail->next_movie = new_movie;
        } else {
            head = new_movie;
        }
        tail = new_movie;
    }
    file.close();

    // Buscar y eliminar la película 
    Movie *aux = head;
    bool found = false;
    while (aux != nullptr) {
        if (aux->movie_name == movie_name) {
            if (aux->prev_movie != nullptr) {
                aux->prev_movie->next_movie = aux->next_movie;
            } else {
                head = aux->next_movie;
            }
            if (aux->next_movie != nullptr) {
                aux->next_movie->prev_movie = aux->prev_movie;
            }
            delete aux;
            found = true;
            cout << "Película eliminada correctamente.\n";
            break;
        }
        aux = aux->next_movie;
    }

    if (!found) {
        cout << "La película no fue encontrada.\n";
        return;
    }

    // Escribir de nuevo en el archivo
    ofstream out_file("moviesfile.txt");
    if (out_file.fail()) {
        cout << "ERROR. No se pudo abrir el archivo para escribir.\n";
        return;
    }

    aux = head; // Reiniciar aux para escribir en el archivo
    while (aux) {
        out_file << aux->movie_name << endl;
        out_file << aux->movie_premiere << endl;
        out_file << aux->movie_type << endl;
        out_file << aux->movie_time << endl;
        aux = aux->next_movie;
    }
    out_file.close(); // Cerrar el archivo de salida
}

int main() {
    string movie_name;
    cout << "Ingrese el nombre de la pelicula a eliminar: ";
    getline(cin, movie_name);
    deleteMovieFromFile(movie_name);
    return 0;
}
