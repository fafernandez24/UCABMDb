#include <iostream>
#include <fstream>
#include <string>
#include "reviewMovieLibrary.h"

using namespace std;

/* PROCEDIMIENTO DEL MENU PARA BORRAR LA PELICULA CON CALIFICACIONES */

void deleteMovieMenu(Movie **movie_head, MovieCalification **cali_head, MovieReview **review_head){

  cout << "========================================\n";
  cout << "              DELETE MOVIE              \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  cout << "========================================\n";

  bool movie_exist = findMovie(*movie_head, movie_name);

  if (movie_exist == true){

    int count_cali = countNumCalificationInMovie(*cali_head, movie_name), count_review = countReviewByMovie(*review_head, movie_name);

    for (int i = 0; i < count_cali; ++i){
      deleteMovieCali(&*cali_head, movie_name);
    }

    for (int i = 0; i < count_review; ++i){
      deleteMovieReviewByMovie(&*review_head, movie_name);
    }

    deleteMovie(&*movie_head, movie_name);

    writeMovieFile(*movie_head);
    writeCaliFile(*cali_head);
    writeReviewFile(*review_head);
    cout << "AVISO: La pelicula se borro correctamente!\n";
  }
  else cout << "ERROR. No se encontro la pelicula!\n";
}

void deleteUsersMenu(Users **users_head, MovieCalification **cali_head, MovieReview **review_head){

  cout << "========================================\n";
  cout << "              DELETE USER               \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  cout << "========================================\n";

  bool users_exist = findUsers(*users_head, email);

  if (users_exist == true){

    int count_cali = countNumCalificationInUser(*cali_head, email), count_review = countReviewByUser(*review_head, email);

    for (int i = 0; i < count_cali; ++i){
      deleteUserCali(&*cali_head, email);
    }

    for (int i = 0; i < count_review; ++i){
      deleteMovieReviewByUser(&*review_head, email);
    }

    deleteUsers(&*users_head, email);

    writeUsersFile(*users_head);
    writeCaliFile(*cali_head);
    writeReviewFile(*review_head);

    cout << "AVISO: El usuario se borro correctamente!\n";
  }
  else cout << "ERROR. El usuario no se pudo encontrar!\n";
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

  if (menu >= "0"  && menu <= "3") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

void searchMovie(Movie *movie_head, MovieCalification *cali_head, MovieReview *review_head, string name){
   
   if (movie_head){

      Movie *aux = getMovieNode(movie_head, name);

      cout << aux -> movie_name << endl;
      cout << "========================================\n";
      cout << "\tMovie premiere: " << aux->movie_premiere << endl;
      cout << "\tMovie type: " << aux->movie_type << endl;
      cout << "\tMovie time: " << aux->movie_time << " min" << endl;
      cout << "\tMovie ID: " << aux->movie_id << endl;
      cout << "========================================\n";
      printCalificationInMovie(cali_head, name);
      printReviewsInMovie(review_head, name);
   }
   else{
      cout << "ERROR. Lista de peliculas vacia.\n";
   }
}

void searchUsers(Users *users_head, MovieCalification *cali_head, MovieReview *review_head, string user_email){
   
   if (users_head){

      Users *aux = getUsersNode(users_head, user_email);

      cout << aux -> email << endl;
      cout << "========================================\n";
      cout << "\tUser age: " << aux->years_old << endl;
      cout << "\tUser country: " << aux->country << endl;
      cout << "\tUser ID: " << aux->id << endl;
      cout << "========================================\n";
      printCalificationInUser(cali_head, user_email);
      printReviewsInUser(review_head, user_email);
   }
   else{
      cout << "ERROR. Lista de usuarios vacia.\n";
   }
}

void movieCaliAndReviewMenuByMovie(MovieCalification *cali_head, MovieReview *review_head, string movie_name){

  string menu_option = "";
  int option = 0;

  do{

  cout << "| 1 - calificaciones | 2 - reviews | 0 - regresar al menu de peliculas |\n";
  cout << "Opcion: ";
  cin >> menu_option;

  if (menu_option >= "0" && menu_option <= "2"){
    option = stoi(menu_option);

    if (option == 1) printCalificationInMovie(cali_head, movie_name);
    if (option == 2) printReviewsInMovie(review_head, movie_name);
  }
  else cout << "ERROR. Ingresaste una opcion invalida!\n";

  }while(option != 0);

}

void caliAndReviewMenuByUser(MovieCalification *cali_head, MovieReview *review_head, string user_email){

  string menu_option = "";
  int option = 0;

  do{

  cout << "| 1 - calificaciones en peliculas | 2 - reviews en peliculas | 0 - regresar al menu de usuarios |\n";
  cout << "Opcion: ";
  cin >> menu_option;

  if (menu_option >= "0" && menu_option <= "2"){
    option = stoi(menu_option);

    if (option == 1) printCalificationInUser(cali_head, user_email);
    if (option == 2) printReviewsInUser(review_head, user_email);
  }
  else cout << "ERROR. Ingresaste una opcion invalida!\n";

  }while(option != 0);

}

void printMovie(Movie *movie_head, MovieCalification *cali_head, MovieReview *review_head){

  string movie_name = searchMovieMenu();
  bool bol = findMovie(movie_head, movie_name);

  if (bol == true)
    searchMovie(movie_head, cali_head, review_head, movie_name);
  else 
    cout << "ERROR. No se encontro la pelicula!\n";

}

void printUser(Users *user_head, MovieCalification *cali_head, MovieReview *review_head){

  string user_email = searchUserMenu();
  bool bol = findUsers(user_head, user_email);

  if (bol == true)
    searchUsers(user_head, cali_head, review_head, user_email);
  else 
    cout << "ERROR. No se encontro al usuario!\n";

}
