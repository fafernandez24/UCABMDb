// UCABMDb
// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "libraries/ucabmdbLibrary.h"

using namespace std;

int main(){

  welcomeScreenUCABMDb();

  Users *users_list = NULL; // LISTA DE PELICULAS
  Movie *movie_list = NULL; // LISTA DE USUARIOS
  Serie *serie_list = NULL; // LISTA DE SERIES

  MovieCalification *calification_movies_list = NULL; // LISTA DE CALIFICACIONES EN PELICULAS
  MovieReview *review_movies_list = NULL; // LISTA DE RESEÑAS EN PELICULAS

  SerieCalification *calification_series_list = NULL; // LISTA DE CALIFICACIONES EN SERIES
  SerieReview *review_series_list = NULL; // LISTA DE RESEÑAS EN SERIES
  SeasonReview *review_seasons_list = NULL; // LISTA DE RESEÑAS EN TEMPORADAS
  ChapterReview *review_chapter_list = NULL; // LISTA DE RESEÑAS EN CAPITULOS

  ///////////////////////////////////////////////////////////////////////////////////////////////////

  readUsersFile(&users_list);
  readMoviesFile(&movie_list);

  readSeriesFile(&serie_list);
  readSeasonsFile(serie_list);
  readChaptersFile(serie_list);

  readMovieCaliFile(&calification_movies_list, movie_list, users_list);
  readReviewFile(&review_movies_list, movie_list, users_list);

  readSerieCaliFile(&calification_series_list, serie_list, users_list);
  readSerieReviewFile(&review_series_list, serie_list, users_list);
  readSeasonReviewFile(&review_seasons_list, serie_list, users_list);

  readChapterReviewFile(&review_chapter_list, serie_list, users_list);

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
              deleteMovieMenu(&movie_list, &calification_movies_list, &review_movies_list);
              break;
            }
            case 4:
            {
              printMovie(movie_list, calification_movies_list, review_movies_list);
              break;
            }
            case 5:
            {
              int cali_menu = 0;

              do{
                cali_menu = calificationMovieMenu();

                switch(cali_menu){

                  case 1:
                  {
                    showMovieCalifications(calification_movies_list);
                    break;
                  }
                  case 2:
                  {
                    addMovieCalificationMenu(&calification_movies_list, movie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteMovieCalificationMenu(&calification_movies_list);
                    break;
                  }
                  default:
                  {
                    if (cali_menu == 0) cout << "AVISO: Regresaste al menu de peliculas...\n";
                    else cout << "VUELVE A INTENTAR\n";
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
                    showMovieReview(review_movies_list);
                    break;
                  }
                  case 2:
                  {
                    addMovieReviewMenu(&review_movies_list, movie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteMovieReviewMenu(&review_movies_list);
                    break;
                  }
                  default:
                  {
                    if (menu_review == 0) cout << "AVISO: Regresaste al menu de peliculas...\n";
                    else cout << "VUELVE A INTENTAR\n";
                    break;
                  }

                }

              }while (menu_review != 0);
              break;
            }
            default:
            {
              if (movie_option == 0){
                cout << "AVISO: Regresaste al menu principal...\n";
                system("cls");
              }
              else cout << "VUELVE A INTENTAR\n";  
              break;
            }
          }
        }
        main_option = -1;
        break;
      }
      case 2: // DESPLEGAR MENU DE SERIES
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
              deleteSerieMenu(&serie_list, &calification_series_list, &review_series_list, &review_seasons_list, &review_chapter_list);
              break;
            }
            case 4:{
              printSerie(&serie_list, calification_series_list, review_series_list, &review_seasons_list, &review_chapter_list, users_list);
              break;
            }
            case 5:
            {
              int cali_menu = 0;

              do{

                cali_menu = calificationSerieMenu();

                switch(cali_menu){

                  case 1:
                  {
                    showSerieCalifications(calification_series_list);
                    break;
                  }
                  case 2:
                  {
                    addSerieCalificationMenu(&calification_series_list, serie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteSerieCalificationMenu(&calification_series_list);
                    break;
                  }
                  default:
                  {
                    if (cali_menu == 0) cout << "AVISO: Regresaste al menu de series...\n";
                    else cout << "VUELVE A INTENTAR\n"; 
                    break;
                  }

                }

              }while (cali_menu != 0);

              break;
            }
            case 6:
            {
              int menu_review = 0;

              do{

                menu_review = reviewSerieMenu();

                switch (menu_review){

                  case 1:
                  {
                    showSerieReview(review_series_list);
                    break;
                  }
                  case 2:
                  {
                    addSerieReviewMenu(&review_series_list, serie_list, users_list);
                    break;
                  }
                  case 3:
                  {
                    deleteSerieReviewMenu(&review_series_list);
                    break;
                  }
                  default:
                  {
                    if (menu_review == 0) cout << "AVISO: Regresaste al menu de series...\n";
                    else cout << "VUELVE A INTENTAR\n";
                    break;
                  }

                }

              }while (menu_review != 0);
              break;

            }
            default:
            {
              if (serie_option == 0){
                cout << "AVISO: Regresaste al menu principal...\n";
                system("cls");
              }
              else cout << "VUELVE A INTENTAR\n"; 
              break;
            }

          }

        }while (serie_option != 0);

        break;
      }
      case 3: // DESPLEGAR MENU DE USUARIOS
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
              deleteUsersMenu(&users_list, &calification_movies_list, &review_movies_list, &calification_series_list, &review_series_list, &review_seasons_list, &review_chapter_list);
              break;
            }
            case 4:
            {
              printUser(users_list, calification_movies_list, review_movies_list, calification_series_list, review_series_list, review_seasons_list, review_chapter_list);
              break;
            }
            default:
            {
              if (users_option == 0){
                cout << "Regresando al menu principal...\n";
                system("cls");
              }
              else cout << "VUELVE A INTENTAR\n";  
              break;
            }
          }
        }
        main_option = -1;
        break;
      }
      case 4:
      {
        int featured_option = 0;

        do{

          featured_option = outstandingMenu();

          switch(featured_option){

            case 1:{
              driveOustandingMovie(calification_movies_list, review_movies_list);
              break;
            }
            case 2:{
              driveOustandingSerie(calification_series_list, review_series_list);
              break;
            }
            case 3:{
              driveOustandingSeason(review_seasons_list);
              break;
            }
            case 4:{
              driveOustandingChapter(review_chapter_list);
              break;
            }
            default:
            {
              if (featured_option == 0){
                cout << "Regresando al menu principal...\n";
                system("cls");
              }
              else cout << "VUELVE A INTENTAR\n";  

              break;
            }
          }
          

        }while (featured_option != 0);

        break;
      }
      default:
      {
        if (main_option == 0){
          system("cls");

          freeMovie(&movie_list);
          freeMovieCali(&calification_movies_list);
          freeMovieRev(&review_movies_list);

          freeSerie(&serie_list);

          freeSerieCali(&calification_series_list);
          freeSerieRev(&review_series_list);

          freeSeasonRev(&review_seasons_list);
          freeChapterRev(&review_chapter_list);

          cout << "\nGRACIAS POR VISITARNOS!\n";
        }
        else cout << "VUELVE A INTENTAR!\n";
        break;
      }
    }
  }

  system("pause");
  return 0;
}
