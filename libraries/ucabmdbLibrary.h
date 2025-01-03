// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "calificationChapterLibrary.h"

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

void deleteUsersMenu(Users **users_head, MovieCalification **cali_head, MovieReview **review_head){

  cout << "========================================\n";
  cout << "              DELETE USER               \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  cout << "========================================\n";

  bool users_exist = findUsers(*users_head, email);

  if (users_exist == true){

    int count_cali = countNumMovieCalificationInUser(*cali_head, email), count_review = countReviewByUser(*review_head, email);

    for (int i = 0; i < count_cali; ++i){
      deleteUserMovieCali(&*cali_head, email);
    }

    for (int i = 0; i < count_review; ++i){
      deleteMovieReviewByUser(&*review_head, email);
    }

    deleteUsers(&*users_head, email);

    writeUsersFile(*users_head);
    writeMovieCaliFile(*cali_head);
    writeReviewFile(*review_head);

    cout << "AVISO: El usuario se borro correctamente!\n";
  }
  else cout << "ERROR. El usuario no se pudo encontrar!\n";
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

int caliAndReviewMenu(){

  string menu;

  cout << "========================================\n";
  cout << "    CALIS AND REVIEWS FROM USER MENU    \n";
  cout << "========================================\n";
  cout << "(1) Calificaciones de las peliculas\n";
  cout << "(2) Reviews de las peliculas\n";
  cout << "(3) Calificaciones de las series\n";
  cout << "(4) Reviews de las series\n";
  cout << "(5) Calificaciones de las temporadas\n";
  cout << "(6) Calificaciones de los capitulos\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "6") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

void searchUsers(Users *users_head, MovieCalification *cali_movie_head, MovieReview *review_movie_head, SerieCalification *cali_serie_head, SerieReview *review_serie_head, SeasonCalification *cali_season_head, ChapterCalification *cali_chapter_head, string user_email){
   
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
            printSeasonCalificationInUser(cali_season_head, user_email);
            break;
          }
          case 6:
          {
            printChapterCalificationInUser(cali_chapter_head, user_email);
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

void driveChapters(Chapter **chapter_head, Serie *serie_head, ChapterCalification **calification_chapter_list, Users *user_head, string serie_name){

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
        deleteChapterMenu(&*chapter_head);
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

        int cali_menu = 0;

        do{

          cali_menu = calificationChapterMenu();

          switch(cali_menu){

            case 1:
            {
              showChapterCalificationsBySerie(*calification_chapter_list, serie_name);
              break;
            }
            case 2:
            {
              addChapterCalificationMenu(&*calification_chapter_list, *chapter_head, user_head, serie_name);
              break;
            }
            case 3:
            {
              deleteChapterCalificationMenu(&*calification_chapter_list);
              break;
            }
            default:
            {
              if (cali_menu == 0) cout << "AVISO: Regresaste al menu de temporadas...\n";
              else cout << "VUELVE A INTENTAR\n"; 
              break;
            }

          }

        }while (cali_menu != 0);

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

void driveSeasons(Serie **serie, SeasonCalification **calification_season_list, ChapterCalification **calification_chapter_list, Serie *serie_head, Users *user_head){

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
        cout << "BORRAR TEMPORADA\n";
        cout << "COMING SOON\n";
        break;
      }
      case 4:
      {
        string season_name = searchSeason();

        if (findSeasonByName(aux->season_head, season_name) == true){

          printSeason(season_head, season_name);
          printSeasonCalificationInSeason(*calification_season_list, season_name);

          Season *aux2 = season_head;

          while (aux2->season_name != season_name) aux2 = aux2->next_season;

          printChaptersList(aux2->chapters_head);
          driveChapters(&aux2->chapters_head, serie_head, &*calification_chapter_list, user_head, aux->serie_name);

        }
        else{
          cout << "ERROR. No se encontro la temporada indicada!\n";
        }
        
        break;
      }
      case 5:
      {
        int cali_menu = 0;

        do{

          cali_menu = calificationSeasonMenu();

          switch(cali_menu){

            case 1:
            {
              showSeasonCalificationsBySerie(*calification_season_list, aux->serie_name);
              break;
            }
            case 2:
            {
              addSeasonCalificationMenu(&*calification_season_list, season_head, user_head, aux->serie_name);
              break;
            }
            case 3:
            {
              deleteSeasonCalificationMenu(&*calification_season_list);
              break;
            }
            default:
            {
              if (cali_menu == 0) cout << "AVISO: Regresaste al menu de temporadas...\n";
              else cout << "VUELVE A INTENTAR\n"; 
              break;
            }

          }

        }while (cali_menu != 0);

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

void printUser(Users *user_head, MovieCalification *cali_movie_head, MovieReview *review_movie_head, SerieCalification *cali_serie_head, SerieReview *review_serie_head, SeasonCalification *cali_season_head, ChapterCalification *cali_chapter_head){

  string user_email = searchUserMenu();
  bool bol = findUsers(user_head, user_email);

  if (bol == true)
    searchUsers(user_head, cali_movie_head, review_movie_head, cali_serie_head, review_serie_head, cali_season_head, cali_chapter_head, user_email);
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

void printSerie(Serie **serie_head, SerieCalification *cali_head, SerieReview *review_head, SeasonCalification **calification_season_list, ChapterCalification **calification_chapter_list, Users *user_head){

  if (serie_head){

    string serie_name = searchSerieMenu();

    bool bol = findSerieByName(*serie_head, serie_name);

    if (bol == true){

      searchSerie(*serie_head, cali_head, review_head, serie_name);

      Serie *aux = getSerieNodeByName(*serie_head, serie_name);
      
      printSeasonsList(aux);
      driveSeasons(&aux, &*calification_season_list, &*calification_chapter_list,  *serie_head, user_head);

    }
    else{
      cout << "ERROR. No se encontro la serie indicada!\n";
    }
  }
}
