// UCABMDB

#include <iostream>
#include <fstream>
#include <string>
#include "movies_library.h"
#include "users_library.h"
#include "ucabmdb_library.h"

using namespace std;

int main(){

  Movie *movie_list = NULL;
  Users *users_list = NULL;

  readMoviesFile(&movie_list);
  readUsersFile(&users_list);

  int main_option = -1;
  while (main_option != 0){
    main_option = mainMenu();

    switch(main_option){
      case 1: // DESPLEGAR MENU DE PELICULAS
      {
        int movie_option = -1;
        while (movie_option != 0){

          movie_option = movieMenu();
          switch (movie_option){
            case 1: // VER PELICULAS
            {
              printMovie(movie_list);
              break;
            }
            case 2: // AGREGAR PELICULA
            {
              addMovieMenu(&movie_list);
              break;
            }
            case 3: // ELIMINAR PELICULA
            {
              deleteMovieMenu(&movie_list);
              break;
            }
            case 4:
            {
              searchMovieMenu(movie_list);
              break;
            }
            default:
            {
              if (movie_option == 0) cout << "Regresando al menu principal...\n";
              else cout << "VUELVE A INTENTAR\n";  
              break;
            }
          }
        }
        main_option = -1;
        break;
      }
      case 2:
      {
        cout << "SERIES MENU\n";
        cout << "COMING SOON\n";
        break;
      }
      case 3:
      {
  
        int users_option = -1;
        while (users_option != 0){
          users_option = usersMenu();
          switch (users_option){
            case 1: // VER PELICULAS
            {
              printUsers(users_list);
              break;
            }
            case 2: // AGREGAR PELICULA
            {
              addUsersMenu(&users_list);
              break;
            }
            case 3: // ELIMINAR PELICULA
            {
              deleteUsersMenu(&users_list);
              break;
            }

            case 4:
            {
              searchUsersMenu(users_list);
              break;
            }
            default:
            {
              if (users_option == 0) cout << "Regresando al menu principal...\n";
              else cout << "VUELVE A INTENTAR\n";  
              break;
            }
          }
        }
        main_option = -1;
        break;
      }
      default:
      {
        if (main_option == 0) cout << "GRACIAS POR VISITARNOS!\n";
        else cout << "VUELVE A INTENTAR!\n";
        break;
      }
    }
  }

  system("pause");
  return 0;
}
