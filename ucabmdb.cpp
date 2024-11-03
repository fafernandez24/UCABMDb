// UCABMDB

#include <iostream>
#include <fstream>
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
          int movie_option = movieMenu();
          switch (movie_option){
            case 1: // VER PELICULAS
            {
              printMovie(movie_list);
              break;
            }
            case 2: // AGREGAR PELICULA
            {
              string movie_name, movie_type;
              int movie_premiere, movie_time;

              cout << "========================================\n";
              cout << "                ADD MOVIE               \n";
              cout << "========================================\n";
              cout << "\tNombre: ";
              cin >> movie_name;
              cout << "\tEstreno: ";
              cin >> movie_premiere;
              cout << "\tGenero: ";
              cin >> movie_type;
              cout << "\tDuracion: ";
              cin >> movie_time;
              cout << "========================================\n";

              addMovie(&movie_list, movie_name, movie_premiere, movie_type, movie_time);
              addMovieToFile(movie_name, movie_premiere, movie_type, movie_time);
              break;
            }
            case 3: // ELIMINAR PELICULA
            {
              string movie_name;
              cout << "========================================\n";
              cout << "              DELETE MOVIE              \n";
              cout << "========================================\n";
              cout << "\tNombre: ";
              cin >> movie_name;
              cout << "========================================\n";

              deleteMovie(&movie_list, movie_name);
              break;
            }
            case 4:
            {
              string movie_name;
              string quali_question; 
              cout << "========================================\n";
              cout << "              SEARCH MOVIE              \n";
              cout << "========================================\n";
              cout << "\tNombre: ";
              cin >> movie_name;
              cout << "========================================\n";
              searchMovie(movie_list, movie_name);
              break;
            }

            default:
            {
              if (movie_option == 0)
                cout << "Regresando al menu principal...\n";
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
          int users_option = usersMenu();
          switch (users_option){
            case 1: // VER PELICULAS
            {
              printUsers(users_list);
              break;
            }
            case 2: // AGREGAR PELICULA
            {
              string email, country;
              int years_old;

              cout << "========================================\n";
              cout << "                ADD USER                \n";
              cout << "========================================\n";
              cout << "\tEmail: ";
              cin >> email;
              cout << "\tEdad: ";
              cin >> years_old;
              cout << "\tPais: ";
              cin >> country;
              cout << "========================================\n";

              addUsers(&users_list, email, years_old, country);
              addUserToFile(email, years_old, country);
              break;
            }
            case 3: // ELIMINAR PELICULA
            {
              string email;
              cout << "========================================\n";
              cout << "              DELETE USER               \n";
              cout << "========================================\n";
              cout << "\tEmail: ";
              cin >> email;
              cout << "========================================\n";

              deleteUsers(&users_list, email);
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
        break;
      }

      case 4:
      {
        /* BUSCAR USUARIOS */
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
