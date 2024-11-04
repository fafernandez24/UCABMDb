#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definición de la estructura Movie
struct Movie {
    string movie_name;
    int movie_premiere;
    string movie_type;
    int movie_time;
    Movie *next_movie;
    Movie *prev_movie;
};

void deleteMovieFromFile(string movie_name) {
    // Abrir el archivo para lectura
    ifstream file("moviesfile.txt");
    if (file.fail()) {
        cout << "ERROR. No se pudo abrir el archivo de PELICULAS!\n";
        return;
    }

    Movie *head = nullptr; // Inicializar la lista enlazada
    string line;
    
    // Leer películas del archivo y crear la lista enlazada
    while (getline(file, line)) {
        Movie *new_movie = new Movie;
        new_movie->movie_name = line;
        getline(file, line);
        new_movie->movie_premiere = stoi(line);
        getline(file, new_movie->movie_type);
        getline(file, line);
        new_movie->movie_time = stoi(line);

        // Enlazar la nueva película
        new_movie->next_movie = head;
        new_movie->prev_movie = nullptr;
        if (head) {
            head->prev_movie = new_movie;
        }
        head = new_movie;
    }
    file.close(); // Cerrar el archivo de entrada

    // Eliminar la película especificada
    Movie *aux = head;
    bool found = false; // Bandera para verificar si se encontró la película
    while (aux) {
        if (aux->movie_name == movie_name) {
            found = true; // Marcamos que hemos encontrado la película
            // Si es la primera película
            if (aux->prev_movie) {
                aux->prev_movie->next_movie = aux->next_movie;
            } else {
                head = aux->next_movie; // Actualizar la cabeza
            }
            if (aux->next_movie) {
                aux->next_movie->prev_movie = aux->prev_movie;
            }
            delete aux; // Liberar memoria
            cout << "Película eliminada correctamente.\n";
            break;
        }
        aux = aux->next_movie;
    }

    if (!found) {
        cout << "La película no fue encontrada.\n";
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
