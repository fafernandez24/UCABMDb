#include <iostream>
#include <fstream>
#include <string>
#include "moviesLibrary.h"
#include "usersLibrary.h"

using namespace std;

struct MovieCalification{

    string movie_name;
    string user_email;
    float calification;
    int id;

    Movie *movie;
    Users *user;
    MovieCalification *next_calification;

};

bool checkIntMovieCalificationId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

bool checkFloatMovieCalification(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stof(word) >= 0 && stof(word) <= 9999999) return true;

    return false;
}

MovieCalification *getMovieCalificationNode(MovieCalification *cali_head, string movie_name, string user_email){

    if (cali_head){
        MovieCalification *aux = cali_head;
        while (aux){
            if (aux -> movie_name == movie_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_calification;
        }
    }
    return NULL;
}

bool findMovieCalificationBool(MovieCalification *cali_head, string movie_name , string user_email){
    if (cali_head){
        MovieCalification *aux = cali_head;
        while (aux){
            if ((aux -> movie_name == movie_name) && (aux -> user -> email == user_email)) return true;
            aux = aux -> next_calification;
        }
    }
    return false;
}

float getCalification(){
    float cali = 0;
    do{
        cout << "\tCalificacion: ";
        cin >> cali;
    } while (cali < 0 || cali > 5);
    return cali;
}

int getMovieCalificationId(){

  string cali_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> cali_id;

    check_num = checkIntMovieCalificationId(cali_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(cali_id);
}

MovieCalification *createMovieCalification(float calification, int id, Movie *movie, Users *user){

    MovieCalification *new_calification = new MovieCalification;

    new_calification -> movie_name = movie->movie_name;
    new_calification -> user_email = user->email;
    new_calification -> calification = calification;
    new_calification -> id = id;
    
    new_calification -> movie = movie;
    new_calification -> user = user;
    new_calification -> next_calification = NULL;

    return new_calification;
}

void addMovieCalification(MovieCalification **cali_head, float calification, int id, Movie *movie, Users *user){

    MovieCalification *new_calification = createMovieCalification(calification, id, movie, user);

    if (!*cali_head) *cali_head = new_calification;
    else{
        new_calification->next_calification = *cali_head;
        *cali_head = new_calification;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS CALIFICACIONES DE PELICULAS Y USUARIOS */

int countNumCalificationInMovie(MovieCalification *cali_head, string movie_name){
    int count = 0;
    if (cali_head){
        MovieCalification *aux = cali_head;
        while (aux){
            if (aux->movie_name == movie_name) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countNumCalificationInUser(MovieCalification *cali_head, string user_email){
    int count = 0;
    if (cali_head){
        MovieCalification *aux = cali_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countUserMovieCali(MovieCalification *cali_head, string email){
    int count = 0;
    if (cali_head){
        MovieCalification *aux = cali_head;
        while (aux){
            if (aux->user->email == email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

void deleteMovieCalification(MovieCalification **cali_head, string movie_name, string user_email){

    if (*cali_head){

        MovieCalification *aux = *cali_head;

        if (aux -> movie_name == movie_name && aux -> user_email == user_email){
            *cali_head = aux -> next_calification;
            delete(aux);
        }
        else{

            MovieCalification *aux2 = NULL;

            while (aux){

                if (aux -> movie_name == movie_name && aux -> user_email == user_email){
                    aux2 -> next_calification = aux -> next_calification;
                    delete(aux);
                }

                aux2 = aux;
                aux = aux -> next_calification;

            }
        }
    }
    else
        cout << "ERROR. Lista de calificaciones vacia!\n";
}

void deleteMovieCali(MovieCalification **cali_head, string movie_name){

    if (*cali_head){
        
        MovieCalification *aux = *cali_head;

        if (aux->movie_name == movie_name){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            MovieCalification *aux2;

            while (aux->movie_name != movie_name || aux != NULL){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux->movie_name == movie_name){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else
        cout << "AVISO: No se encontraron calificaciones en esta pelicula!\n";
}

void deleteUserCali(MovieCalification **cali_head, string email){

    if (*cali_head){
        
        MovieCalification *aux = *cali_head;

        if (aux->user_email == email){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            MovieCalification *aux2 = NULL;

            while (aux->user_email != email){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux->user_email == email){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else{
        cout << "AVISO: No se encontraron calificaciones en esta pelicula!\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA CALIFICACIONES */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA CALIFICACIONES */

void readCaliFile(MovieCalification **cali_head, Movie *movie_head, Users *user_head){

  ifstream file;
  string text, movie_name, user_email;
  float calification;
  int data_line = 0, id;
  MovieCalification *aux = *cali_head;
  Movie *movie = NULL;
  Users *user = NULL;

  file.open("califile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de CALIFICACIONES!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "CALIFICATIONS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1) movie = getMovieNode(movie_head, text);

            if (data_line == 2) user = getUsersNode(user_head, text);

            if (data_line == 3) calification = stof(text);

            if (data_line == 4){
                if (checkIntMovieCalificationId(text) == true){
                    id = stoi(text);
                    addMovieCalification(&aux, calification, id, movie, user);
                }
            }

            ++data_line;

            if (data_line == 5) data_line = 0;

        }

        *cali_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de calificaciones!\n\n";
    }

    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN CALIFICACIONES */

void addCaliToFile(string movie_name, string user_email, float calification, int id){

  ofstream file;

  file.open("califile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << movie_name;
  file << endl << user_email;
  file << endl << calification;
  file << endl << id;

  file.close();
}

void writeCaliFile(MovieCalification *cali_head){

    if (cali_head){

        ofstream file;
        file.open("califile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        MovieCalification *aux = cali_head;

        file << "CALIFICATIONS\n\n";

        while(aux){


            file << aux -> movie_name << endl;
            file << aux -> user_email << endl;
            file << aux -> calification << endl;

            if (aux -> next_calification == NULL) file << aux -> id;
            else file << aux -> id << endl << endl;

            aux = aux -> next_calification;
        }
        }
    }
    else{
        ofstream file;
        file.open("califile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "CALIFICATIONS\n\n";
        }
    }
}

void editMovieCalification(MovieCalification *cali_head, float calification, string movie_name, string user_email){

    if (findMovieCalificationBool(cali_head, movie_name, user_email) == true){

        MovieCalification *new_cali = getMovieCalificationNode(cali_head, movie_name, user_email);
        new_cali -> calification = calification;
        cout << "AVISO: Calificacion EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

void addMovieCalificationMenu(MovieCalification **cali_head, Movie *movie_head, Users *user_head){

    cout << "========================================\n";
    cout << "     ADD OR EDIT MOVIE CALIFICATION     \n";
    cout << "========================================\n";
    string movie_name = getMovieName();
    float calification = getCalification();
    string user_email = getUsersEmail();
    int id = getMovieCalificationId();
    cout << "========================================\n";

    bool movie_exist = findMovie(movie_head, movie_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( movie_exist == true && user_exist == true){

        bool cali_exist = findMovieCalificationBool(*cali_head, movie_name, user_email);

        if ( cali_exist == false){

            Movie *movie = getMovieNode(movie_head, movie_name);
            Users *user = getUsersNode(user_head, user_email);
            addMovieCalification(&*cali_head, calification, id, movie, user);

            cout << "AVISO: Calificacion AGREGADA con exito\n";

        }
        else editMovieCalification(*cali_head, calification, movie_name, user_email);
        
        writeCaliFile(*cali_head);

    }
    else 
        cout << "ERROR. La pelicula o el usuario ingresado no han sido encontrados!\n";
}

void deleteMovieCalificationMenu(MovieCalification **cali_head){

    cout << "========================================\n";
    cout << "       DELETE MOVIE CALIFICATION        \n";
    cout << "========================================\n";
    string movie_name = getMovieName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool cali_exist = findMovieCalificationBool(*cali_head, movie_name, user_email);

    if (cali_exist == true){
        deleteMovieCalification(&*cali_head, movie_name, user_email);
        writeCaliFile(*cali_head);
        cout << "AVISO: La calificacion ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

int calificationsMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "        MOVIE CALIFICATION MENU         \n";
        cout << "========================================\n";
        cout << "(1) Mostrar calificaciones\n";
        cout << "(2) Agregar calificacion\n";
        cout << "(3) Borrar calificacion\n";
        cout << "(0) Volver a peliculas\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        cin >> menu;

        if (menu < "0" || menu > "3"){
            cout << "ERROR. Ingresaste " << menu << endl;
            cout << "Ingresa una opcion valida.\n";
        }

    } while (menu < "0" || menu > "3");

    return stoi(menu);
}

void printCalificationInUser(MovieCalification *cali_head, string email){

    cout << "========================================\n";
    cout << "          USER CALIFICATIONS            \n";
    cout << "========================================\n";    

    if (countNumCalificationInUser(cali_head, email) > 0){

        MovieCalification *aux = cali_head;
    
        while (aux){
            if (aux->user->email == email){
                cout << "Pelicula: " << aux->movie_name << endl;
                cout << "Calificacion: " << aux->calification << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
            }
            aux = aux->next_calification;
        }
    }
    else{
        cout << "AVISO: El usuario aun no tiene calificaciones.\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printCalificationInMovie(MovieCalification *cali_head, string movie_name){

    cout << "========================================\n";
    cout << "             CALIFICATIONS              \n";
    cout << "========================================\n";

    if (countNumCalificationInMovie(cali_head, movie_name) > 0){

        MovieCalification *aux = cali_head;
        
        while (aux){
            if (aux->movie_name == movie_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux -> calification << endl;
            }
            aux = aux->next_calification;
        }
    }
    else cout << "AVISO: Aun no hay calificaciones en la pelicula\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showMovieCalifications(MovieCalification *cali_head){

    cout << "========================================\n";
    cout << "          MOVIES CALIFICATIONS          \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        MovieCalification *aux = cali_head;

        while (aux){

            cout << "Pelicula: " << aux->movie_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Calificacion: " << aux->calification << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_calification;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////