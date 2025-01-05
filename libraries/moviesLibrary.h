// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "usersLibrary.h"

using namespace std;
using  sizeType = std::string::size_type;

/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCIONES DE VALIDACION DE TIPO BOOLEANO*/

/* FUNCION PARA VALIDAR LA FECHA DE ESTRENO DE LA PELICULA */

bool checkIntDataPremiere(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 1895 && stoi(word) <= 9999) return true;

    return false;
}

/* FUNCION PARA VALIDAR LA DURACION DE UNA PELICULA */

bool checkIntDataTime(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 51420) return true;

    return false;
}

bool checkIntMovieId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// FUNCIONES & PROCEDIMIENTOS

/* Funcion que busca retornar un puntero que apunte a un elemento de tipo pelicula */

Movie *createMovie(string name, int premiere, string type, int time, int id){

  Movie *new_movie = new Movie;

  new_movie -> movie_name = name;
  new_movie -> movie_premiere = premiere;
  new_movie -> movie_type = type;
  new_movie -> movie_time = time;
  new_movie -> movie_id = id;

  new_movie -> next_movie = NULL;

  return new_movie;
}

Movie *getMovieNode(Movie *movies_head, string movie_name){
  if (movies_head){
    Movie *aux = movies_head;
    while (aux){
      if (aux -> movie_name == movie_name) return aux;
      aux = aux->next_movie;
    }
  }
  return movies_head;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS PELICULAS */

/* Funcion para obtener el nombre de la pelicula */
string getMovieName(){

  string movie_name;
  cin.ignore();
  cout << "\tNombre de la pelicula: ";
  getline(cin, movie_name);
  return movie_name;
} 

/* Funcion para obtener el año de estreno de la pelicula */
int getMoviePremiere(){

  string movie_premiere;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tEstreno: ";
    cin >> movie_premiere;

    check_num = checkIntDataPremiere(movie_premiere);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 1985 y 9999!\n";
    }
  }
  return stoi(movie_premiere);
}

/* Funcion para obtener el genero de la pelicula */
string getMovieType(){

  string movie_type;
  cin.ignore();
  cout << "\tGenero: ";
  getline(cin, movie_type);
  return movie_type;
} 

/* Funcion para obtener el tiempo que dura la pelicula */
int getMovieTime(){

  string movie_time;
  bool check_num = false;

  while (check_num == false){

    cout << "\tDuracion: ";
    cin >> movie_time;

    check_num = checkIntDataTime(movie_time);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 0 y 51420!\n";
    }
  }
  return stoi(movie_time);
}

int getMovieId(){

  string movie_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> movie_id;

    check_num = checkIntMovieId(movie_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(movie_id);
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* Procedimiento para mostras las peliculas en pantalla */

void printMovieList(Movie *movie_head){

  Movie *aux = movie_head;
  int movie_num = 1;

  cout << "========================================\n";
  cout << "                PELICULAS\n";
  cout << "========================================\n";

  if (movie_head){
    while (aux){

      cout << "              Movie #" << movie_num << "              \n";
      cout << "========================================\n";
      cout << "\tMovie name: " << aux->movie_name << endl;
      cout << "\tMovie premiere: " << aux->movie_premiere << endl;
      cout << "\tMovie type: " << aux->movie_type << endl;
      cout << "\tMovie time: " << aux->movie_time << " min" << endl;
      cout << "\tMovie ID: " << aux -> movie_id << endl;
      cout << "========================================\n";

      aux = aux->next_movie;
      ++movie_num;
    }
  }
  else{

    cout << "                Movie #0                \n";
    cout << "========================================\n";
    cout << "\tAun no hay peliculas...\n";
    cout << "========================================\n";
    cout << endl;
  }

}

/* Procedimiento para agregar peliculas */

void addMovie(Movie **movie_head, string name, int premiere, string type, int time, int id){

  Movie *new_movie = createMovie(name, premiere, type, time, id);

  if (!*movie_head){
    *movie_head = new_movie;
  }
  else{

    Movie *aux = *movie_head;

    while (aux->next_movie != NULL){
      aux = aux -> next_movie;
    }

    aux -> next_movie = new_movie;
    
  }
}

/* Procedimiento para eliminar peliculas */

void deleteMovie(Movie **movie_head, string name){

  if (*movie_head){

    Movie *aux = *movie_head;

    if (aux -> movie_name != name){
      Movie *aux2 = NULL;

      while (aux -> movie_name != name){
        aux2 = aux;
        aux = aux -> next_movie;
      }
      aux2 -> next_movie = aux -> next_movie;
      delete(aux);
    }
    else{
      *movie_head = aux -> next_movie;
      delete(aux);
    }
  }
  else{
    cout << "ERROR. Lista de peliculas vacia\n";
  }
}

/* FUNCION QUE RETORNA UN TIPO DE DATO BOOLEANO QUE DETERMINA SI UNA PELICA SE ENCUENTRA O NO EN LA LISTA DE PELICULAS */

bool findMovie(Movie *movie_head, string name){
   if (movie_head){
      Movie *aux = movie_head;
      while (aux){
        if (aux -> movie_name == name) return true;
        aux = aux -> next_movie;
      }
   }
  return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA PELICULAS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA PELICULAS */

void readMoviesFile(Movie **movie_head){

  ifstream file;
  string text, movie_name, movie_type;
  int data_line = 0, movie_premiere, movie_time, movie_id;
  Movie *aux = *movie_head;

  file.open("moviesfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de PELICULAS!\n";
  }

  getline(file, text);

  if (text == "MOVIES"){

    while(!file.eof()){

      getline(file,text);

      if (data_line == 3) movie_type = text;

      if (data_line == 4){

        if (checkIntDataTime(text) == true){
          movie_time = stoi(text);
        }
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de peliculas!\n\n";
          file.close();
        }
      }

      if (data_line == 2){
        
        if (checkIntDataPremiere(text) == true) movie_premiere = stoi(text);
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de peliculas!\n\n";
          file.close();
        }
      }

      if (data_line == 1) movie_name = text;

      if (data_line == 5){

        if (checkIntMovieId(text) == true){
          movie_id = stoi(text);
          addMovie(&aux, movie_name, movie_premiere, movie_type, movie_time, movie_id);
        }
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de peliculas!\n\n";
          file.close();
        }
      }

      ++data_line;

      if (data_line == 6) data_line = 0;

    }

  *movie_head = aux;

  }
  else{
    cout << "\nERROR. Dato invalidos en el archivo!\n";
    cout << "AVISO: No se cargaron los datos del archivo de peliculas!\n\n";
  }

  file.close();
}


/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN PELICULAS */

void addMovieToFile(string movie_name, int movie_premiere, string movie_type, int movie_time, int movie_id){

    ofstream file;

    file.open("moviesfile.txt", ios::app);

    if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
    }

    file << endl;
    file << endl << movie_name;
    file << endl << movie_premiere;
    file << endl << movie_type;
    file << endl << movie_time;
    file << endl << movie_id;

    file.close();
}

void writeMovieFile(Movie *movie_head){

  if (movie_head){

    ofstream file;
    file.open("moviesfile.txt", ios::out);

    if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo\n";
      exit(1);
    }
    else{

      Movie *aux = movie_head;

      file << "MOVIES\n\n";

      while(aux){


        file << aux -> movie_name << endl;
        file << aux -> movie_premiere << endl;
        file << aux -> movie_type << endl;
        file << aux -> movie_time << endl;

        if (aux -> next_movie == NULL) file << aux -> movie_id;
        else file << aux -> movie_id << endl << endl;

        aux = aux -> next_movie;
      }
    }
  }
  else cout << "ERROR. Lista de peliculas vacia!";
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCIONES */

/* FUNCIONES PARA LOS MENUS*/

int movieMenu(){

  string menu;

  cout << "========================================\n";
  cout << "               MOVIE MENU               \n";
  cout << "========================================\n";
  cout << "(1) Ver peliculas\n";
  cout << "(2) Agregar pelicula\n";
  cout << "(3) Eliminar pelicula\n";
  cout << "(4) Buscar pelicula\n";
  cout << "(5) Calificaciones\n";
  cout << "(6) Reviews\n";
  cout << "(0) Regresar al menu principal\n";
  cout << "========================================" << endl;
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";
  
  if (menu >= "0"  && menu <= "6") return stoi(menu);

  cout << "========================================\n";
  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  cout << "========================================\n";
  return -1;
}

/* PROCEDIMIENTO DE UN MENU PARA AGREGAR UNA PELICULA */

void addMovieMenu(Movie **movie_head){

  cout << "========================================\n";
  cout << "                ADD MOVIE               \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  int movie_premiere = getMoviePremiere();
  string movie_type = getMovieType();
  int movie_time = getMovieTime();
  int movie_id = getMovieId();
  cout << "========================================\n";

  bool movie_exist = findMovie(*movie_head, movie_name);

  if (movie_exist == false){
    addMovie(&*movie_head, movie_name, movie_premiere, movie_type, movie_time, movie_id);
    addMovieToFile(movie_name, movie_premiere, movie_type, movie_time, movie_id);
    cout << "AVISO: La pelicula se agrego correctamente!\n";
  }
  else cout << "AVISO: La pelicula ya se encuentra agregada!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA PELICULA */

string searchMovieMenu(){

  cout << "========================================\n";
  cout << "              SEARCH MOVIE              \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  cout << "========================================\n";

  return movie_name;
}

/////////////////////////////////////////////////////////////////////////////////////////////
