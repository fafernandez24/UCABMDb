#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using  sizeType = std::string::size_type;

/////////////////////////////////////////////////////////////////////////////////////////////

// STRUCT

/*El siguiente struct sirve para almacenar el conjunto de elementos de las peliculas
  como el nombre, la fecha de estreno, el genero, la duracion y el pais.*/
  
struct Movie{
    string movie_name;
    int movie_premiere;
    string movie_type;
    int movie_time;

    Movie *next_movie;
    Movie *prev_movie;
};

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

/////////////////////////////////////////////////////////////////////////////////////////////

// FUNCIONES & PROCEDIMIENTOS

/* Funcion que busca retornar un puntero que apunte a un elemento de tipo pelicula */

Movie *createMovie(string name, int premiere, string type, int time){

  Movie *new_movie = new Movie;

  new_movie -> movie_name = name;
  new_movie -> movie_premiere = premiere;
  new_movie -> movie_type = type;
  new_movie -> movie_time = time;

  new_movie -> next_movie = NULL;
  new_movie -> prev_movie = NULL;

  return new_movie;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS PELICULAS */

/* Funcion para obtener el nombre de la pelicula */
string getMovieName(){

  string movie_name;
  cin.ignore();
  cout << "\tNombre: ";
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

/////////////////////////////////////////////////////////////////////////////////////////////

/* Procedimiento para mostras las peliculas en pantalla */

void printMovie(Movie *movie_head){

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

void addMovie(Movie **movie_head, string name, int premiere, string type, int time){

    Movie *new_movie = createMovie(name,premiere, type, time);

    if (!*movie_head){
      *movie_head = new_movie;
    }
    else{
      new_movie -> next_movie = *movie_head;
      *movie_head = new_movie;   
      new_movie -> next_movie -> prev_movie = *movie_head;
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

void searchMovie(Movie *movie_head, string name){
   
   if (movie_head){

      Movie *aux = movie_head;
      int movie_num = 1;

      while (aux -> movie_name != name){
        aux = aux -> next_movie;
        ++movie_num;
      }

      cout << "              Movie #" << movie_num << "              \n";
      cout << "========================================\n";
      cout << "\tMovie name: " << aux->movie_name << endl;
      cout << "\tMovie premiere: " << aux->movie_premiere << endl;
      cout << "\tMovie type: " << aux->movie_type << endl;
      cout << "\tMovie time: " << aux->movie_time << " min" << endl;
      cout << "========================================\n";
   }
   else{
      cout << "ERROR. Lista de peliculas vacia.\n";
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
  int data_line = 0, movie_premiere, movie_time;
  Movie *aux = *movie_head;


  file.open("moviesfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
  }

  getline(file, text);

  if (text == "MOVIES"){

    while(!file.eof()){

      getline(file,text);

      if (data_line == 3) movie_type = text;

      if (data_line == 4){

        if (checkIntDataTime(text) == true){
          movie_time = stoi(text);
          addMovie(&aux, movie_name, movie_premiere, movie_type, movie_time);
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

      ++data_line;

      if (data_line == 5) data_line = 0;
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

void addMovieToFile(string movie_name, int movie_premiere, string movie_type, int movie_time){

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

        if (aux -> next_movie == NULL) file << aux -> movie_time;
        else file << aux -> movie_time << endl << endl;

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
  cout << "(0) Salir\n";
  cout << "========================================" << endl;
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";
  
  if (menu >= "0"  && menu <= "3") return stoi(menu);

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
  cout << "========================================\n";

  bool movie_exist = findMovie(*movie_head, movie_name);

  if (movie_exist == false){
    addMovie(&*movie_head, movie_name, movie_premiere, movie_type, movie_time);
    addMovieToFile(movie_name, movie_premiere, movie_type, movie_time);
    cout << "La pelicula se agrego correctamente!\n";
  }
  else cout << "AVISO: La pelicula ya se encuentra agregada!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BORRAR LA PELICULA */

void deleteMovieMenu(Movie **movie_head){

  cout << "========================================\n";
  cout << "              DELETE MOVIE              \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  cout << "========================================\n";

  bool movie_exist = findMovie(*movie_head, movie_name);

  if (movie_exist == true){
    deleteMovie(&*movie_head, movie_name);
    writeMovieFile(*movie_head);
    cout << "La pelicula se borro correctamente!\n";
  }
  else cout << "ERROR. No se encontro la pelicula!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA PELICULA */

void searchMovieMenu(Movie *movie_head){

  cout << "========================================\n";
  cout << "              SEARCH MOVIE              \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  cout << "========================================\n";

  bool movie_exist = findMovie(movie_head, movie_name);

  if (movie_exist == true) searchMovie(movie_head, movie_name);
  else cout << "ERROR. No se encontro la pelicula!\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
