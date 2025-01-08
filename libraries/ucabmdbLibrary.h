// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "reportLibrary.h"

using namespace std;

/*
  @brief Imprime a traves de caracteres ASCII una mensaje de bienbenida a UCABMDb.
*/
void welcomeScreenUCABMDb(){

  cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
  cout << char(186) << "                                 " << char(186) << endl;
  cout << char(186) << "   UCABMDb te da la bienvenida   " << char(186) << endl;
  cout << char(186) << "                                 " << char(186) << endl;
  cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;

  system("pause");
  system("cls");
  cout << endl;

}

/*
  @brief Borra al usuario indicado y todas las calificaciones y reseñas que tenga.

  @param users_head Puntero cabeza de la lista de usuarios.
  @param cali_head Puntero cabeza de la lista de calificaciones en peliculas.
  @param review_head Puntero cabeza de la lista de reseñas en peliculas.
  @param cali_serie_head Puntero cabeza de la lista de calificaciones en series.
  @param review_serie_head Puntero cabeza de la lista de reseñas en series.
  @param review_season_head Puntero cabeza de la lista de reseñas en temporadas.
  @param review_chapter_head Puntero cabeza de la lista de reseñas en capitulos.

*/
void deleteUsersMenu(Users **users_head, MovieCalification **cali_head, MovieReview **review_head, SerieCalification **cali_serie_head, SerieReview **review_serie_head, SeasonReview **review_season_head, ChapterReview **review_chapter_head){

  cout << "========================================\n";
  cout << "              DELETE USER               \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  cout << "========================================\n";

  bool users_exist = findUsers(*users_head, email);

  if (users_exist == true){

    int count_cali = countNumMovieCalificationInUser(*cali_head, email), count_review = countReviewByUser(*review_head, email);

    int count_cali_serie = countNumSerieCalificationInUser(*cali_serie_head, email), count_review_serie = countNumSerieReviewInUser(*review_serie_head, email); 

    int count_review_season = countNumSeasonReviewInUser(*review_season_head, email), count_review_chapter = countNumChapterReviewInUser(*review_chapter_head, email);

    for (int i = 0; i < count_cali; ++i){
      deleteUserMovieCali(&*cali_head, email);
    }

    for (int i = 0; i < count_review; ++i){
      deleteMovieReviewByUser(&*review_head, email);
    }

    for (int i = 0; i < count_cali_serie; ++i){
      deleteUserSerieCali(&*cali_serie_head, email);
    }

    for (int i = 0; i < count_review_serie; ++i){
      deleteSerieReviewByUser(&*review_serie_head, email);
    }

    for (int i = 0; i < count_review_season; ++i){
      deleteSeasonRevByUser(&*review_season_head, email);
    }

    for (int i = 0; i < count_review_chapter; ++i){
      deleteChapterRevByUser(&*review_chapter_head, email);
    }

    deleteUsers(&*users_head, email);

    writeUsersFile(*users_head);
    writeMovieCaliFile(*cali_head);
    writeReviewFile(*review_head);
    writeSerieCaliFile(*cali_serie_head);
    writeSerieReviewFile(*review_serie_head);
    writeSeasonReviewFile(*review_season_head);
    writeChapterReviewFile(*review_chapter_head);

    cout << "AVISO: El usuario se borro correctamente!\n";
  }
  else cout << "ERROR. El usuario no se pudo encontrar!\n";
}

/*

  @brief Borra la pelicula indicada y todas las calificaciones y reseñas que tenga.

  @param movie_head Puntero cabeza de la lista de peliculas.
  @param cali_head  Puntero cabeza de la lista de las calificaciones en pelicula.
  @param review_head Puntero cabeza de la lista de reseñas en peliculas.

*/
void deleteMovieMenu(Movie **movie_head, MovieCalification **cali_head, MovieReview **review_head){

  cout << "========================================\n";
  cout << "              DELETE MOVIE              \n";
  cout << "========================================\n";
  string movie_name = getMovieName();
  cout << "========================================\n";

  bool movie_exist = findMovie(*movie_head, movie_name);

  if (movie_exist == true){

    int count_cali = countNumMovieCalificationInMovie(*cali_head, movie_name), count_review = countReviewByMovie(*review_head, movie_name);

    for (int i = 0; i < count_cali; ++i){
      deleteMovieCali(&*cali_head, movie_name);
    }

    for (int i = 0; i < count_review; ++i){
      deleteMovieReviewByMovie(&*review_head, movie_name);
    }

    deleteMovie(&*movie_head, movie_name);

    writeMovieFile(*movie_head);
    writeMovieCaliFile(*cali_head);
    writeReviewFile(*review_head);
    cout << "AVISO: La pelicula se borro correctamente!\n";
  }
  else cout << "ERROR. No se encontro la pelicula!\n";
}

/*

  @brief Borra el capitulo indicado y toda reseña que tenga.

  @param chapter_head Puntero cabeza de la lista de capitulos.
  @param review_head Puntero cabeza de la lista de reseñas en capitulos.
  @param serie_head Puntero cabeza de la lista de series.
  @param serie_name Nombre de la serie a la que pertenece el capitulo.

*/
void deleteChapterMenu(Chapter **chapter_head, ChapterReview **review_head, Serie *serie_head, string serie_name){

  cout << "========================================\n";
  cout << "              DELETE CHAPTER             \n";
  cout << "========================================\n";
  string chapter_name = getChapterName();
  cout << "========================================\n";

  bool chapter_exist = findChapterByName(*chapter_head, chapter_name);

  if (chapter_exist == true){


    int count_review = countNumChapterReviewInChapter(*review_head, chapter_name);

    for (int i = 0; i < count_review; ++i){
      deleteChapterRev(&*review_head, chapter_name, serie_name);
    }

    deleteChapter(&*chapter_head, chapter_name);

    writeChapterFile(serie_head);
    writeChapterReviewFile(*review_head);
    cout << "AVISO: El capitulo se borro correctamente!\n";
  }
  else cout << "ERROR. No se encontro el capitulo!\n";
}

/*

  @brief Borra la temporada indicada y todas las reseñas que tenga.

  @param season_head Puntero cabeza de la lista de temporadas.
  @param season_review_head Puntero cabeza de la lista de reseñas en temporadas.
  @param chapter_review_head Puntero cabeza de la lista de reseñas en capitulos.
  @param serie_head Puntero cabeza de la lista de series.
  @param serie_name Nombre de la serie a la que pertenece la temporada.

*/
void deleteSeasonMenu(Season **season_head, SeasonReview **season_review_head, ChapterReview **chapter_review_head, Serie *serie_head, string serie_name){

  cout << "========================================\n";
  cout << "              DELETE SEASON             \n";
  cout << "========================================\n";
  string season_name = getSeasonName();
  cout << "========================================\n";

  bool season_exist = findSeasonByName(*season_head, season_name);

  if (season_exist == true){

    Season *aux = *season_head;

    while (aux->season_name != season_name) aux = aux->next_season;

    Chapter *aux2 = aux->chapters_head;

    while (aux2){

      int count_review = countNumChapterReviewInChapter(*chapter_review_head, aux2->chapter_name);

      for (int i = 0; i < count_review; ++i){
        deleteChapterRev(&*chapter_review_head, serie_name, aux2->chapter_name);
      }
      aux2 = aux2->next_chapter;
    }

    int count_season_review = countNumSeasonReviewInSeason(*season_review_head, season_name);

    for (int j = 0; j < count_season_review; ++j){
      deleteSeasonRev(&*season_review_head, serie_name, season_name);
    }

    deleteSeason(&*season_head, season_name);

    writeSeasonsFile(serie_head);
    writeSeasonReviewFile(*season_review_head);
    writeChapterFile(serie_head);
    writeChapterReviewFile(*chapter_review_head);

    cout << "AVISO: La temporada se borro correctamente!\n";
  }
  else cout << "ERROR. No se encontro la temporada!\n";
}

/*

  @brief Borra la serie indicada y todas las calificaciones y reseñas que tenga.

  @param serie_head Puntero cabeza de la lista de series.
  @param serie_cali_head Puntero cabeza de la lista de calificaciones en series.
  @param serie_rev_head Puntero cabeza de la lista de reseñas en series.
  @param season_rev_head Puntero cabeza de la lista de reseñas en temporadas.
  @param chapter_rev_head Puntero cabeza de la lista de reseñas en capitulos.

*/
void deleteSerieMenu(Serie **serie_head, SerieCalification **serie_cali_head, SerieReview **serie_rev_head, SeasonReview **season_rev_head, ChapterReview **chapter_rev_head){

  cout << "========================================\n";
  cout << "               DELETE SERIE             \n";
  cout << "========================================\n";
  string serie_name = getSerieName();
  cout << "========================================\n";

  bool bol = findSerieByName(*serie_head, serie_name);

  if (bol == true){

    int count_cali_serie = countNumSerieCalificationInSerie(*serie_cali_head, serie_name);
    int count_rev_serie = countNumSerieReviewInSerie(*serie_rev_head, serie_name);

    int count_rev_season = countNumSeasonReviewInSerie(*season_rev_head, serie_name);
    int count_rev_chapter = countNumChapterReviewInSerie(*chapter_rev_head, serie_name);

    for (int i = 0; i < count_rev_chapter; ++i){
      deleteChapterRevBySerie(&*chapter_rev_head, serie_name);
    }

    for (int i = 0; i < count_rev_season; ++i){
      deleteSeasonRevBySerie(&*season_rev_head, serie_name);
    }

    for (int i = 0; i < count_rev_serie; ++i){
      deleteSerieReviewBySerie(&*serie_rev_head, serie_name);
    }

    for (int i = 0; i < count_cali_serie; ++i){
      deleteSerieCali(&*serie_cali_head, serie_name);
    }

    deleteSerie(&*serie_head, serie_name);

    writeSerieFile(*serie_head);
    writeSerieCaliFile(*serie_cali_head);
    writeSerieReviewFile(*serie_rev_head);

    writeSeasonsFile(*serie_head);
    writeSeasonReviewFile(*season_rev_head);
    writeChapterFile(*serie_head);
    writeChapterReviewFile(*chapter_rev_head);

  }
  else{
    cout << "ERROR. No se encontro la serie!\n";
  }
}

/* FUNCIONES */

/*
  @brief Imprime el menu principal de UCABMDb.
  @return int Entrada de tipo entero ingresada por el usuario.
*/
int mainMenu(){

  string menu;

  cout << "========================================\n";
  cout << "                MAIN MENU               \n";
  cout << "========================================\n";
  cout << "(1) Peliculas\n";
  cout << "(2) Series\n";
  cout << "(3) Usuarios\n";
  cout << "(4) Destacados\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "4") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

/*
  @brief Imprime el menu de calificaciones y reseñas hechas por el usuario.
  @return int Entrada de tipo entero ingresada por el usuario.
*/
int caliAndReviewMenu(){

  string menu;

  cout << "========================================\n";
  cout << "    CALIS AND REVIEWS FROM USER MENU    \n";
  cout << "========================================\n";
  cout << "(1) Calificaciones de las peliculas\n";
  cout << "(2) Reviews de las peliculas\n";
  cout << "(3) Calificaciones de las series\n";
  cout << "(4) Reviews de las series\n";
  cout << "(5) Reviews de las temporadas\n";
  cout << "(6) Reviews de los capitulos\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "6") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

/*
  @brief Imprime el usuario indicado y despliega un sub-menu para ver las calificaciones y reseñas hechas por el usuario.

  @param users_head Puntero cabeza de la lista de usuarios.
  @param cali_movie_head Puntero cabeza de la lista de calificaciones en peliculas.
  @param review_movie_head Puntero cabeza de la lista de reseñas en peliculas.
  @param cali_serie_head Puntero cabeza de la lista de calificaciones en series.
  @param review_serie_head Puntero cabeza de la lista de reseñas en series.
  @param review_season_head Puntero cabeza de la lista de reseñas en temporadas.
  @param review_chapter_head Puntero cabeza de la lista de reseñas en capitulos.
  @param user_email Email del usuario a buscar.

*/
void searchUsers(Users *users_head, MovieCalification *cali_movie_head, MovieReview *review_movie_head, SerieCalification *cali_serie_head, SerieReview *review_serie_head, SeasonReview *review_season_head, ChapterReview *review_chapter_head, string user_email){
   
   if (users_head){

      Users *aux = getUsersNode(users_head, user_email);

      cout << " " << aux -> email << endl;
      cout << "========================================\n";
      cout << "\tUser age: " << aux->years_old << endl;
      cout << "\tUser country: " << aux->country << endl;
      cout << "\tUser ID: " << aux->id << endl;
      cout << "========================================\n";

      int cali_menu = 0;
      
      do{

        cali_menu = caliAndReviewMenu();

        switch(cali_menu){

          case 1:
          {
            printMovieCalificationInUser(cali_movie_head, user_email);
            break; 
          }
          case 2:
          {
            printReviewsInUser(review_movie_head, user_email);
            break;
          }
          case 3:
          {
            printSerieCalificationInSerie(cali_serie_head, user_email);
            break;
          }
          case 4:
          {
            printSerieReviewsInUser(review_serie_head, user_email);
            break;
          }
          case 5:
          {
            printSeasonReviewInUser(review_season_head, user_email);
            break;
          }
          case 6:
          {
            printChapterReviewInUser(review_chapter_head, user_email);
            break;
          }
          default:
          {
            if (cali_menu == 0) cout << "AVISO: Regresando al menu de usuarios!\n";
            break;
          }

        }

      }while (cali_menu != 0);

   }
   else{
      cout << "ERROR. Lista de usuarios vacia.\n";
   }
}

/*
  @brief Imprime la pelicula indicada y despliega las calificaciones y reseñas hechas en la pelicula.

  @param movie_head Puntero cabeza de la lista de peliculas.
  @param cali_head Puntero cabeza de la lista de calificaciones en peliculas.
  @param review_head Puntero cabeza de la lista de reseñas en peliculas.
  @param name Nombre de la pelicula a buscar.

*/
void searchMovie(Movie *movie_head, MovieCalification *cali_head, MovieReview *review_head, string name){
   
   if (movie_head){

      Movie *aux = getMovieNode(movie_head, name);

      cout << " " << aux -> movie_name << endl;
      cout << "========================================\n";
      cout << "\tMovie premiere: " << aux->movie_premiere << endl;
      cout << "\tMovie type: " << aux->movie_type << endl;
      cout << "\tMovie time: " << aux->movie_time << " min" << endl;
      cout << "\tMovie ID: " << aux->movie_id << endl;
      cout << "========================================\n";
      printMovieCalificationInMovie(cali_head, name);
      printReviewsInMovie(review_head, name);
   }
   else{
      cout << "ERROR. Lista de peliculas vacia.\n";
   }
}

/*
  @brief Imprime la serie indicada y despliega las calificaciones y reseñas hechas en la serie.

  @param serie_head Puntero cabeza de la lista de series.
  @param cali_head Puntero cabeza de la lista de calificaciones en series.
  @param review_head Puntero cabeza de la lista de reseñas en series.
  @param name Nombre de la serie a buscar.

*/
void searchSerie(Serie *serie_head, SerieCalification *cali_head, SerieReview *review_head, string name){
   
   if (serie_head){

      Serie *aux = getSerieNodeByName(serie_head, name);

      cout << " " << aux -> serie_name << endl;
      cout << "========================================\n";
      cout << "\tSerie premiere: " << aux->serie_premiere << endl;
      cout << "\tSerie type: " << aux->type  << endl;
      cout << "\tSerie ID: " << aux->id << endl;
      cout << "========================================\n";



      printSerieCalificationInSerie(cali_head, name);
      printSerieReviewsInSerie(review_head, name);
   }
   else{
      cout << "ERROR. Lista de series vacia.\n";
   }
}

/*

  @brief Procedimiento para implementar el menu de capitulos y sus respectivas reseñas.

  @param chapter_head Puntero cabeza de la lista de capitulos.
  @param serie_head Puntero cabeza de la lista de series.
  @param review_chapter_list Puntero cabeza de la lista de reseñas en capitulos.
  @param user_head Puntero cabeza de la lista de usuarios.
  @param serie_name Nombre de la serie a la que pertenece el capitulo.

*/
void driveChapters(Chapter **chapter_head, Serie *serie_head, ChapterReview **review_chapter_list, Users *user_head, string serie_name){

  int chapter_option = -1;

  while (chapter_option != 0){

    chapter_option = chapterMenu();

    switch(chapter_option){

      case 1:{
        printChaptersList(*chapter_head);    
        break;
      }
      case 2:
      {
        addChapterMenu(&*chapter_head);
        writeChapterFile(serie_head);
        break;
      }
      case 3:{
        deleteChapterMenu(&*chapter_head, &*review_chapter_list, serie_head, serie_name);
        writeChapterFile(serie_head);
        break;
      }
      case 4:
      {
        showChapter(*chapter_head);
        break;
      }
      case 5:
      {

        int rev_menu = 0;

        do{

          rev_menu = reviewChapterMenu();

          switch(rev_menu){

            case 1:
            {
              showChapterReviewBySerie(*review_chapter_list, serie_name);
              break;
            }
            case 2:
            {
              addChapterReviewMenu(&*review_chapter_list, *chapter_head, user_head, serie_name);
              break;
            }
            case 3:
            {
              deleteChapterReviewMenu(&*review_chapter_list);
              break;
            }
            default:
            {
              if (rev_menu == 0) cout << "AVISO: Regresaste al menu de capitulos...\n";
              else cout << "VUELVE A INTENTAR\n"; 
              break;
            }

          }

        }while (rev_menu != 0);

        break;

      }
      default:
      {
        if (chapter_option == 0) cout << "AVISO: Regresando al menu de temporadas!\n";
        break;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/*
  @brief Procedimiento para implementar el menu de temporadas sus respectivos capitulos y reseñas.

  @param serie Puntero de la serie que pertenece la temporada.
  @param review_seasons_list Puntero cabeza de la lista de reseñas en temporadas.
  @param review_chapter_list Puntero cabeza de la lista de reseñas en capitulos.
  @param serie_head Puntero cabeza de la lista de series.
  @param user_head Puntero cabeza de la lista de usuarios.

*/
void driveSeasons(Serie **serie, SeasonReview **review_seasons_list, ChapterReview **review_chapter_list, Serie *serie_head, Users *user_head){

  Serie *aux = *serie;
  Season *season_head = aux->season_head;

  int season_option = -1;

  while (season_option != 0){

    season_option = seasonMenu();

    switch(season_option){

      case 1:{
        printSeasonsList(aux);
        break;
      }
      case 2:
      {
        addSeasonMenu(&aux->season_head, aux->id);
        break;
      }
      case 3:{
        deleteSeasonMenu(&aux->season_head, &*review_seasons_list, &*review_chapter_list, serie_head, aux->serie_name);
        break;
      }
      case 4:
      {
        string season_name = searchSeason();

        if (findSeasonByName(aux->season_head, season_name) == true){

          printSeason(season_head, season_name);
          printSeasonReviewInSeason(*review_seasons_list, season_name);

          Season *aux2 = season_head;

          while (aux2->season_name != season_name) aux2 = aux2->next_season;

          printChaptersList(aux2->chapters_head);
          driveChapters(&aux2->chapters_head, serie_head, &*review_chapter_list, user_head, aux->serie_name);

        }
        else{
          cout << "ERROR. No se encontro la temporada indicada!\n";
        }
        
        break;
      }
      case 5:
      {
        int rev_menu = 0;

        do{

          rev_menu = reviewSeasonMenu();

          switch(rev_menu){

            case 1:
            {
              showSeasonReviewBySerie(*review_seasons_list, aux->serie_name);
              break;
            }
            case 2:
            {
              addSeasonReviewMenu(&*review_seasons_list, season_head, user_head, aux->serie_name);
              break;
            }
            case 3:
            {
              deleteSeasonReviewMenu(&*review_seasons_list);
              break;
            }
            default:
            {
              if (rev_menu == 0) cout << "AVISO: Regresaste al menu de temporadas...\n";
              else cout << "VUELVE A INTENTAR\n"; 
              break;
            }

          }

        }while (rev_menu != 0);

        break;
      }
      default:
      {
        cout << "AVISO: Regresando al menu de series!\n";
        break;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printUser(Users *user_head, MovieCalification *cali_movie_head, MovieReview *review_movie_head, SerieCalification *cali_serie_head, SerieReview *review_serie_head, SeasonReview *review_season_head, ChapterReview *review_chapter_head){

  string user_email = searchUserMenu();
  bool bol = findUsers(user_head, user_email);

  if (bol == true)
    searchUsers(user_head, cali_movie_head, review_movie_head, cali_serie_head, review_serie_head, review_season_head, review_chapter_head, user_email);
  else 
    cout << "ERROR. No se encontro al usuario!\n";

}

void printMovie(Movie *movie_head, MovieCalification *cali_head, MovieReview *review_head){

  string movie_name = searchMovieMenu();
  bool bol = findMovie(movie_head, movie_name);

  if (bol == true)
    searchMovie(movie_head, cali_head, review_head, movie_name);
  else 
    cout << "ERROR. No se encontro la pelicula!\n";

}

void printSerie(Serie **serie_head, SerieCalification *cali_head, SerieReview *review_head, SeasonReview **review_seasons_list, ChapterReview **review_chapter_list, Users *user_head){

  if (serie_head){

    string serie_name = searchSerieMenu();

    bool bol = findSerieByName(*serie_head, serie_name);

    if (bol == true){

      searchSerie(*serie_head, cali_head, review_head, serie_name);

      Serie *aux = getSerieNodeByName(*serie_head, serie_name);
      
      printSeasonsList(aux);
      driveSeasons(&aux, &*review_seasons_list, &*review_chapter_list,  *serie_head, user_head);

    }
    else{
      cout << "ERROR. No se encontro la serie indicada!\n";
    }
  }
}

void freeMovie(Movie **movie_head){
  if (*movie_head){
    while (*movie_head){
      Movie *aux = *movie_head;
      *movie_head = aux->next_movie;
      delete(aux);
    }
  }
}

void freeSeason(Season **season_head){
  if (*season_head){
    while (*season_head){
      Season *aux = *season_head;
      *season_head = aux->next_season;
      delete(aux);
    }
  }
}

void freeSerie(Serie **serie_head){
  if (*serie_head){
    while (*serie_head){
      Serie *aux = *serie_head;
      *serie_head = aux->next_serie;
      freeSeason(&aux->season_head);
      delete(aux);
    }
  }
}

void freeMovieCali(MovieCalification **cali_head){
  if (*cali_head){
    while (*cali_head){
      MovieCalification *aux = *cali_head;
      *cali_head = aux->next_calification;
      delete(aux);
    }
  }
}

void freeMovieRev(MovieReview **rev_head){
  if (*rev_head){
    while (*rev_head){
      MovieReview *aux = *rev_head;
      *rev_head = aux->next_review;
      delete(aux);
    }
  }
}

void freeSerieCali(SerieCalification **cali_head){
  if (*cali_head){
    while (*cali_head){
      SerieCalification *aux = *cali_head;
      *cali_head = aux->next_calification;
      delete(aux);
    }
  }
}

void freeSerieRev(SerieReview **rev_head){
  if (*rev_head){
    while (*rev_head){
      SerieReview *aux = *rev_head;
      *rev_head = aux->next_review;
      delete(aux);
    }
  }
}

void freeSeasonRev(SeasonReview **rev_head){
  if (*rev_head){
    while (*rev_head){
      SeasonReview *aux = *rev_head;
      *rev_head = aux->next_review;
      delete(aux);
    }
  }
}

void freeChapterRev(ChapterReview **rev_head){
  if (*rev_head){
    while (*rev_head){
      ChapterReview *aux = *rev_head;
      *rev_head = aux->next_review;
      delete(aux);
    }
  }
}

