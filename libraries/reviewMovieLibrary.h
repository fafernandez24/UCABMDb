#include <iostream>
#include <fstream>
#include <string>
#include "calificationMovieLibrary.h"

using namespace std;

MovieReview *getMovieReviewNode(MovieReview *review_head, string movie_name, string user_email){

    if (review_head){
        MovieReview *aux = review_head;
        while (aux){
            if (aux -> movie_name == movie_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_review;
        }
    }
    return NULL;

}

bool findMovieReviewBool(MovieReview *review_head, string movie_name , string user_email){
    if (review_head){
        MovieReview *aux = review_head;
        while (aux){
            if ((aux -> movie_name == movie_name) && (aux -> user -> email == user_email)) return true;
            aux = aux -> next_review;
        }
    }
    return false;
}

/*
    Funcion que retorna la cantidad de reseñas que tenga una pelicula.

    @param *review_head Es un puntero de la estructura MovieReview que señala a la cabeza de la lista de reseñas designadas a peliculas.
    @param movie_name Es un dato de tipo cadena que maneja como contenido el nombre de la pelicula a la que se hizo reseña.

    @return La funcion retorna la variable count que segun tal condicion puede retornar 0 o un numero mayor.
*/
int countReviewByMovie(MovieReview *review_head, string movie_name){
    int count = 0;
    if (review_head){
        MovieReview *aux = review_head;
        while (aux){
            if (aux->movie_name == movie_name) ++count;
            aux = aux -> next_review;
        }
    }
    return count;
}

/*
    Funcion que retorna la cantidad de reseñas que tenga una pelicula.

    @param *review_head Es un puntero de la estructura MovieReview que señala a la cabeza de la lista de reseñas designadas a peliculas.
    @param user_email Es un dato de tipo cadena que maneja como contenido el email del usuario que hizo la reseña.

    @return La funcion retorna una variable de tipo entero llamada count que segun tal condicion puede retornar 0 o un numero mayor.
*/
int countReviewByUser(MovieReview *review_head, string user_email){
    int count = 0;
    if (review_head){
        MovieReview *aux = review_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux -> next_review;
        }
    }
    return count;
}

/* Funcion para obtener una reseña */
string getMovieReview(){

  string review;
  cin.ignore();
  cout << "\tReview: ";
  getline(cin, review);
  return review;
} 

MovieReview *createMovieReview(string review, int id, Movie *movie, Users *user){

    MovieReview *new_review = new MovieReview;

    new_review -> movie_name = movie->movie_name;
    new_review -> user_email = user -> email;
    new_review -> review = review;
    new_review -> id = id;

    new_review -> movie = movie;
    new_review -> user = user;

    new_review -> next_review = NULL;

    return new_review;
}

void addMovieReview(MovieReview **review_head, string review, int id, Movie *movie, Users *user){
    MovieReview *new_review =  createMovieReview(review, id, movie, user);
    if (review_head){
        new_review -> next_review = *review_head;
        *review_head = new_review;
    }
    else *review_head = new_review;
}

void deleteMovieReview(MovieReview **review_head, string movie_name, string user_email){

    if (*review_head){

        MovieReview *aux = *review_head;

        if (aux->movie_name == movie_name && aux->user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            MovieReview *aux2 = NULL;

            while (aux){
                aux2 = aux;
                aux = aux->next_review;
                if (aux->movie_name == movie_name && aux->user_email == user_email) break;
            }

            if (aux->movie_name == movie_name && aux->user_email == user_email){
                aux2 -> next_review = aux -> next_review;
                delete(aux);
            }
            else{
                cout << "ERROR. No se pudo encontrar la review.\n";
            }

        }
    }
    else{
        cout << "ERROR. Lista de reviews vacia!\n";
    }
}

void deleteMovieReviewByMovie(MovieReview **review_head, string movie_name){

    if (*review_head){

        MovieReview *aux = *review_head;

        if (aux->movie_name == movie_name){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            MovieReview *aux2 = NULL;

            while (aux){
                aux2 = aux;
                aux = aux -> next_review;
                if (aux->movie_name == movie_name) break;
            }

            if (aux->movie_name == movie_name){
                aux2 -> next_review = aux -> next_review;
                delete(aux);
            }
            else{
                cout << "ERROR. No se pudo encontrar la review.\n";
            }            
        }
    }
    else cout << "ERROR. Lista de reviews vacia!\n";
}

void deleteMovieReviewByUser(MovieReview **review_head, string user_email){

    MovieReview *aux = *review_head;

    if (aux){

        if (aux->user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            MovieReview *aux2 = NULL;

            while (aux){
                aux2 = aux;
                aux = aux -> next_review;
                if (aux->user_email == user_email) break;
            }

            if (aux->user_email == user_email){
                aux2 -> next_review = aux -> next_review;
                delete(aux);
            }
            else cout << "ERROR. No se encontraron reviews de este usuario.\n";
        }
    }
    else{
        cout << "ERROR. Lista de reviews vacia!\n";
    }
}

void editMovieReview(MovieReview *review_head, string review, string movie_name, string user_email){

    if (findMovieReviewBool(review_head, movie_name, user_email) == true){

        MovieReview *new_review = getMovieReviewNode(review_head, movie_name, user_email);
        new_review -> review = review;
        cout << "AVISO: Review EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}

int reviewsMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "           MOVIE REVIEWS MENU           \n";
        cout << "========================================\n";
        cout << "(1) Mostrar reviews \n";
        cout << "(2) Agregar review\n";
        cout << "(3) Borrar review\n";
        cout << "(0) Volver a peliculas\n";
        cout << "========================================\n";
        cout << " Opcion: ";
        cin >> menu;

        if (menu < "0" || menu > "3"){
            cout << "ERROR. Ingresaste " << menu << endl;
            cout << "Ingresa una opcion valida.\n";
        }

    } while (menu < "0" || menu > "3");

    return stoi(menu);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printReviewsInMovie(MovieReview *review_head, string movie_name){

    cout << "========================================\n";
    cout << "              MOVIE REVIEWS             \n";
    cout << "========================================\n";

    if (countReviewByMovie(review_head, movie_name) > 0){

        MovieReview *aux = review_head;
        
        while (aux){
            if (aux->movie_name == movie_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux -> review  << endl;
                cout << "========================================\n";
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews en la pelicula\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printReviewsInUser(MovieReview *review_head, string user_email){

    cout << "========================================\n";
    cout << "              USER REVIEWS              \n";
    cout << "========================================\n";

    if (countReviewByUser(review_head, user_email) > 0){

        MovieReview *aux = review_head;
        
        while (aux){
            if (aux->user_email == user_email){
                cout << "Movie: " << aux -> movie_name << endl;
                cout << "Review: " << aux -> review  << endl;
                cout << "========================================\n";
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews del usuario\n";
}

void showMovieReview(MovieReview *review_head){

    cout << "========================================\n";
    cout << "             MOVIES REVIEWS             \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        MovieReview *aux = review_head;

        while (aux){

            cout << "Pelicula: " << aux->movie_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Review: " << aux->review << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_review;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA REVIEWS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA REVIEWS */

void readReviewFile(MovieReview **review_head, Movie *movie_head, Users *user_head){

  ifstream file;
  string text, movie_name, user_email, review;
  int data_line = 0, id;
  MovieReview *aux = *review_head;
  Movie *movie = NULL;
  Users *user = NULL;

  file.open("reviewsfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de REVIEWS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "REVIEWS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1) movie = getMovieNode(movie_head, text);

            if (data_line == 2) user = getUsersNode(user_head, text);

            if (data_line == 3) review = text;

            if (data_line == 4){
                if (checkIntMovieCalificationId(text) == true){
                    id = stoi(text);
                    addMovieReview(&aux, review, id, movie, user);
                }
            }

            ++data_line;

            if (data_line == 5) data_line = 0;

        }

        *review_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de reviews!\n\n";
    }

    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN REVIEWS */

void addReviewToFile(string movie_name, string user_email, string review, int id){

  ofstream file;

  file.open("reviewsfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << movie_name;
  file << endl << user_email;
  file << endl << review;
  file << endl << id;

  file.close();
}

void writeReviewFile(MovieReview *reviews_head){

    if (reviews_head){

        ofstream file;
        file.open("reviewsfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

            MovieReview *aux = reviews_head;

            file << "REVIEWS\n\n";

            while(aux){

                file << aux -> movie_name << endl;
                file << aux -> user_email << endl;
                file << aux -> review << endl;

                if (aux -> next_review == NULL) file << aux -> id;
                else file << aux -> id << endl << endl;

                aux = aux -> next_review;
            }
        }
    }
    else{

        ofstream file;
        file.open("reviewsfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else file << "REVIEWS\n\n";
    
    }
}

void addMovieReviewMenu(MovieReview **review_head, Movie *movie_head, Users *user_head){

    cout << "========================================\n";
    cout << "        ADD OR EDIT MOVIE REVIEW        \n";
    cout << "========================================\n";
    string movie_name = getMovieName();
    string user_email = getUsersEmail();
    string review = getMovieReview();
    int id = getMovieCalificationId();
    cout << "========================================\n";

    bool movie_exist = findMovie(movie_head, movie_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( movie_exist == true && user_exist == true){

        bool review_exist = findMovieReviewBool(*review_head, movie_name, user_email);

        if ( review_exist == false){

            Movie *movie = getMovieNode(movie_head, movie_name);
            Users *user = getUsersNode(user_head, user_email);
            addMovieReview(&*review_head, review, id, movie, user);

            cout << "AVISO: review AGREGADA con exito\n";

        }
        else editMovieReview(*review_head, review, movie_name, user_email);
        
        writeReviewFile(*review_head);

    }
    else 
        cout << "ERROR. La pelicula o el usuario ingresado no han sido encontrados!\n";
}

void deleteMovieReviewMenu(MovieReview **review_head){

    cout << "========================================\n";
    cout << "           DELETE MOVIE REVIEW          \n";
    cout << "========================================\n";
    string movie_name = getMovieName();
    string user_email = getUsersEmail();
    cout << "\n";
    cout << "========================================\n";

    bool review_exist = findMovieReviewBool(*review_head, movie_name, user_email);

    if (review_exist == true){
        deleteMovieReview(&*review_head, movie_name, user_email);
        writeReviewFile(*review_head);
        cout << "AVISO: La review ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}