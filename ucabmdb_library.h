#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// STRUCTS

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

/*El siguiente struct sirve para almacenar el conjunto de elementos de los capitulos dentro de las temporadas
  de las series como el nombre, la fecha de estreno, los capitulos, la duracion y el pais.*/

struct Chapter{
    string chapter_name;
    int chapter_premiere;
    int chapter_time;
    int chapter_num;

    Chapter *next_chapter;
    Chapter *prev_chapter;
};

/*El siguiente struct sirve para almacenar el conjunto de elementos de las temporadas dentro de las series
  como el nombre, la fecha de estreno, los capitulos, la duracion y el pais.*/

struct Season{
    string season_name;
    int season_premiere;
    Chapter *chapters;

    Season *next_season;
    Season *prev_season;
};

/*El siguiente struct sirve para almacenar el conjunto de elemntos de las series
  como el nombre, la fecha de estreno, el genero, la duracion, las temporadas y el pais.*/

struct Series{
    string series_name;
    int series_premiere;
    string series_type;
    int series_time;
    Season *seasons;
    string series_country;

    Series *next_series;
    Series *prev_series;
};

/*El siguiente struct sirve para almacenar el conjunto de elementos de los usuarios
  como el correo, la edad, el pais, la calificaciones y las reseñas.*/

struct Users{
    string email;
    int years_old;
    string country;

    Users *next_user;
    Users *prev_user;
};

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
      cout << "\tMovie time: " << aux->movie_time << endl;
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

/* PROCEDIMIENTOS & FUNCIONES PARA LOS USUARIOS */

/* Funcion que busca retornar un puntero que apunte a un elemento de tipo usuario */

Users *createUser(string email, int old, string country){

  Users *new_user = new Users;

  new_user -> email = email;
  new_user -> years_old = old;
  new_user -> country = country;

  new_user -> next_user = NULL;
  new_user -> prev_user = NULL;

  return new_user;
}

/* Procedimiento para mostras las peliculas en pantalla */

void printUsers(Users *users_head){

  Users *aux = users_head;
  int users_num = 1;

  cout << "========================================\n";
  cout << "                USUARIOS\n";
  cout << "========================================\n";

  if (users_head){
    while (aux){

      cout << "              User #" << users_num << "              \n";
      cout << "========================================\n";
      cout << "\tUsers email: " << aux-> email << endl;
      cout << "\tMovie premiere: " << aux->years_old << endl;
      cout << "\tMovie type: " << aux->country << endl;
      cout << "========================================\n";

      aux = aux->next_user;
      ++users_num;
    }
  }
  else{

    cout << "========================================\n";
    cout << "                User #0\n";
    cout << "========================================\n";
    cout << "\tAun no hay usuarios...\n";
    cout << "========================================\n";
    cout << endl;
  }
}

/* Procedimiento para agregar peliculas */

void addUsers(Users **users_head, string email, int years_old, string country){

    Users *new_user = createUser(email, years_old, country);

    if (!*users_head){
      *users_head = new_user;
    }
    else{
      new_user -> next_user = *users_head;
      *users_head = new_user;   
    }
}

/* Procedimiento para eliminar peliculas */

void deleteUsers(Users **users_head, string email){

  if (*users_head){

    Users *aux = *users_head;

    if (aux -> email != email){
      Users *aux2 = NULL;

      while (aux -> email != email || aux ->next_user == NULL){
        aux2 = aux;
        aux = aux -> next_user;
      }
      aux2 -> next_user = aux -> next_user;
      delete(aux);
    }
    else{
      *users_head = aux -> next_user;
      delete(aux);
    }
  }
  else{
    cout << "ERROR. Lista de usuarios vacia.\n";
  }
}

/* FUNCIONES */

/* FUNCIONES PARA LOS MENUS*/

int mainMenu(){

  string menu;

  cout << "========================================\n";
  cout << "                MAIN MENU               \n";
  cout << "========================================\n";
  cout << "(1) Peliculas\n";
  cout << "(2) Series\n";
  cout << "(3) Usuario\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";

  if (menu == "0" || menu == "1" || menu == "2" || menu == "3")
    return stoi(menu);
  else{
    cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
    cout << "Por favor ingresar una opcion correcta.\n";
    return -1;
  }

  return 0;
}

int movieMenu(){

  string menu;

  cout << "========================================\n";
  cout << "               MOVIE MENU               \n";
  cout << "========================================\n";
  cout << "(1) Ver peliculas\n";
  cout << "(2) Agregar pelicula\n";
  cout << "(3) Eliminar pelicula\n";
  cout << "(4) Buscar pelicula\n";
  cout << "(5) Destacado\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";

  if (menu == "0" || menu == "1" || menu == "2" || menu == "3" || menu == "4" || menu == "5")
    return stoi(menu);
  else{
    cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
    cout << "Por favor ingresar una opcion correcta.\n";
    return -1;
  }

  return 0;
}

int usersMenu(){

  string menu;

  cout << "========================================\n";
  cout << "               USERS MENU               \n";
  cout << "========================================\n";
  cout << "(1) Ver usuarios\n";
  cout << "(2) Agregar usuario\n";
  cout << "(3) Eliminar usuario\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";

  if (menu == "0" || menu == "1" || menu == "2" || menu == "3" || menu == "4")
    return stoi(menu);
  else{
    cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
    cout << "Por favor ingresar una opcion correcta.\n";
    return -1;
  }

  return 0;
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
      cout << "\tMovie time: " << aux->movie_time << endl;
      cout << "========================================\n";
   }
   else{
      cout << "ERROR. Lista de peliculas vacia.\n";
   }
}

/* PROCEDIMIENTO PARA LOS ARCHIVOS */

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA PELICULAS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA USUARIOS */

void readMoviesFile(Movie **movie_head){

    ifstream file;
    string text, movie_name, movie_type;
    int data_line = 0, movie_premiere, movie_time;
    Movie *aux = *movie_head;


    file.open("moviesfile.txt", ios::in);

    if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
        exit(1);
    }

    while(!file.eof()){

        getline(file,text);

        if (data_line == 3) movie_type = text;

        if (data_line == 4){
            movie_time = stoi(text);
            addMovie(&aux, movie_name, movie_premiere, movie_type, movie_time);
        }

        if (data_line == 2) movie_premiere = stoi(text);

        if (data_line == 1) movie_name = text;

        ++data_line;

        if (data_line == 5) data_line = 0;

    }

    *movie_head = aux;
    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN PELICULAS */

void addMovieToFile(string movie_name, int movie_premiere, string movie_type, int movie_time){

    ofstream file;

    file.open("usersfile.txt", ios::app);

    if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo";
        exit(1);
    }

    file << endl;
    file << endl << movie_name;
    file << endl << movie_premiere;
    file << endl << movie_type;
    file << endl << movie_time;

    file.close();
}

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA USUARIOS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA USUARIOS */

void readUsersFile(Users **users_head){

  ifstream file;
  string text, email, country;
  int data_line = 0, years_old;
  Users *aux = *users_head;


  file.open("usersfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
      exit(1);
  }

  while(!file.eof()){

      getline(file,text);

      if (data_line == 3){
          country = text;
          addUsers(&aux, email, years_old, country);
      }

      if (data_line == 2) years_old = stoi(text);

      if (data_line == 1) email = text;

      ++data_line;

      if (data_line == 4) data_line = 0;
  }

  *users_head = aux;
  file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN USUARIOS */

void addUserToFile(string email, int years_old, string country){

  ofstream file;

  file.open("usersfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << email;
  file << endl << years_old;
  file << endl << country;

  file.close();
}
