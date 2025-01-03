// UCABMDB

#include <iostream>
#include <fstream>
#include <string>
#include "libraries/ucabmdbLibrary.h"

using namespace std;

int main(){

  Users *users_list = NULL; // LISTA DE PELICULAS
  Movie *movie_list = NULL; // LISTA DE USUARIOS
  Serie *serie_list = NULL; // LISTA DE SERIES

  MovieCalification *calification_list = NULL;
  MovieReview *review_list = NULL;

  readUsersFile(&users_list); 
  readMoviesFile(&movie_list);

  readSeriesFile(&serie_list);
  readSeasonsFile(serie_list);
  readChaptersFile(serie_list);
  readCaliFile(&calification_list, movie_list, users_list);
  readReviewFile(&review_list, movie_list, users_list);

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
              printMovieList(movie_list);
              break;
            }
            case 2: // AGREGAR PELICULA
            {
              addMovieMenu(&movie_list);
              break;
            }
            case 3: // ELIMINAR PELICULA
            {
              deleteMovieMenu(&movie_list, &calification_list, &review_list);
              break;
            }
            case 4:
            {
              printMovie(movie_list, calification_list, review_list);
              break;
            }
            case 5:
            {
              int cali_menu = 0;

              do{
                cali_menu = calificationsMenu();

                switch(cali_menu){

                  case 1:
                  {
                    showMovieCalifications(calification_list);
                    break;
                  }
                  case 2:
                  {
                    addMovieCalificationMenu(&calification_list, movie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteMovieCalificationMenu(&calification_list);
                    break;
                  }
                  default:
                  {
                    cout << "AVISO: Regresaste al menu de peliculas...\n";
                    break;
                  }
                }

              } while (cali_menu != 0);
              break;
            }
            case 6:
            {
              int menu_review = 0;

              do{

                menu_review = reviewsMenu();

                switch (menu_review){

                  case 1:
                  {
                    showMovieReview(review_list);
                    break;
                  }
                  case 2:
                  {
                    addMovieReviewMenu(&review_list, movie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteMovieReviewMenu(&review_list);
                    break;
                  }
                  default:
                  {
                    cout << "AVISO: Regresaste al menu de peliculas...\n";
                    break;
                  }
                }

              }while (menu_review != 0);
              break;
            }
            default:
            {
              if (movie_option == 0) cout << "AVISO: Regresaste al menu principal...\n";
              else cout << "VUELVE A INTENTAR\n";  
              break;
            }
          }
        }
        main_option = -1;
        break;
      }
      case 2:  // DESPLEGAR MENU DE SERIES
      {
        int serie_option = 0;

        do{

          serie_option = serieMenu();

          switch(serie_option){

            case 1:
            {
              printSerieList(serie_list);
              break;
            }
            case 2:
            {
              addSerieMenu(&serie_list);
              break;
            }
            case 3:{
              cout << "ELIMINAR SERIE\n";
              cout << "COMING SOON\n";
              break;
            }
            case 4:{
              showSerieByName(&serie_list);
              writeSeasonsFile(serie_list);
              writeChapterFile(serie_list);
            }
          }

        }while (serie_option != 0);

        break;
      }
      case 3:
      {
        
        int users_option = -1;
        while (users_option != 0){
          users_option = usersMenu();
          switch (users_option){
            case 1: // VER USUARIOS
            {
              printUsersList(users_list);
              break;
            }
            case 2: // AGREGAR USUARIO
            {
              addUsersMenu(&users_list);
              break;
            }
            case 3: // ELIMINAR USUARIO
            {
              deleteUsersMenu(&users_list, &calification_list, &review_list);
              break;
            }
            case 4:
            {
              printUser(users_list, calification_list, review_list);
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
