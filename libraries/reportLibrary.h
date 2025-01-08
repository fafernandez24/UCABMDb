// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "reviewChapterLibrary.h"

using namespace std;

/*
  @brief Imprime el menu de destacados.
  @return int Entrada de tipo entero ingresada por el usuario.
*/
int outstandingMenu(){

  string menu;

  cout << "========================================\n";
  cout << "            DESTACADOS MENU             \n";
  cout << "========================================\n";
  cout << "(1) Tops de peliculas\n";
  cout << "(2) Tops de series\n";
  cout << "(3) Tops de temporadas\n";
  cout << "(4) Tops de capitulos\n";
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

int outstandingMovieMenu(){

  string menu;

  cout << "========================================\n";
  cout << "         DESTACADOS DE PELICULAS        \n";
  cout << "========================================\n";
  cout << "(1) Tops de peliculas por pais\n";
  cout << "(2) Tops de peliculas por genero\n";
  cout << "(3) Tops de peliculas en general\n";
  cout << "(4) Peliculas con mas reviews por pais\n";
  cout << "(5) Peliculas con mas reviews en general\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "5") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

int outstandingSerieMenu(){

  string menu;

  cout << "========================================\n";
  cout << "          DESTACADOS DE SERIES          \n";
  cout << "========================================\n";
  cout << "(1) Tops de series por pais\n";
  cout << "(2) Tops de series por genero\n";
  cout << "(3) Tops de series en general\n";
  cout << "(4) Series con mas reviews por pais\n";
  cout << "(5) Series con mas reviews en general\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "5") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

int outstandingSeasonMenu(){

  string menu;

  cout << "========================================\n";
  cout << "        DESTACADOS DE TEMPORADAS        \n";
  cout << "========================================\n";
  cout << "(1) Temporadas con mas reviews por pais\n";
  cout << "(2) Temporadas con mas reviews en general\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "2") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

int outstandingChapterMenu(){

  string menu;

  cout << "========================================\n";
  cout << "         DESTACADOS DE CAPITULOS        \n";
  cout << "========================================\n";
  cout << "(1) Capitulos con mas reviews por pais\n";
  cout << "(2) Capitulos con mas reviews en general\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << ">> ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "2") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

string searchCountryMenu(){

  cout << "========================================\n";
  cout << "             SEARCH COUNTRY             \n";
  cout << "========================================\n";
  string country = getUsersCountry();
  cout << "========================================\n";

  return country;
}

string searchTypeMenu(){

  cout << "========================================\n";
  cout << "             SEARCH TYPE             \n";
  cout << "========================================\n";
  string type = getMovieType();
  cout << "========================================\n";

  return type;
}

bool findNameTopCali(TopCali *top_head, string name){
    if (top_head){
        TopCali *aux = top_head;
        while (aux){
            if (aux->name == name) return true;
            aux = aux->next_top;
        }
    }
    return false;
}

bool findNameTopRev(TopRev *top_head, string name){
    if (top_head){
        TopRev *aux = top_head;
        while (aux){
            if (aux->name == name) return true;
            aux = aux->next_top;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

TopCali *createTopCali(string name, float average){

    TopCali *new_top = new TopCali;

    new_top -> name = name;
    new_top -> average = average;

    new_top -> next_top = NULL;

    return new_top;
}

TopRev *createTopRev(string name, int num_rev){

    TopRev *new_top = new TopRev;

    new_top -> name = name;
    new_top -> num_rev = num_rev;

    new_top -> next_top = NULL;

    return new_top;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printMovieGeneralTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "    TOP MEJORES PELICULAS EN GENERAL    \n";
        cout << "========================================\n";

        while (aux){
            

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printMovieCountryTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "     TOP MEJORES PELICULAS POR PAIS     \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones de este pais!\n";
    }

}

void printMovieTypeTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "    TOP MEJORES PELICULAS POR GENERO    \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;
            
            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones de este genero!\n";
    }

}

void printMovieGeneralTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "  PELICULAS CON MAS REVIEWS EN GENERAL  \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printMovieCountryTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "   PELICULAS CON MAS REVIEWS POR PAIS   \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSerieGeneralTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "      TOP MEJORES SERIES EN GENERAL     \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printSerieCountryTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "      TOP MEJORES SERIES POR PAIS       \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones de este pais!\n";
    }

}

void printSerieTypeTopCali(TopCali *top_head){

    if (top_head){

        TopCali *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "      TOP MEJORES SERIES POR GENERO     \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Promedio: " << aux->average << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones de este genero!\n";
    }

}

void printSerieGeneralTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "    SERIES CON MAS REVIEWS EN GENERAL   \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printSerieCountryTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "     SERIES CON MAS REVIEWS POR PAIS    \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSeasonGeneralTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << " TEMPORADAS CON MAS REVIEWS EN GENERAL  \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printSeasonCountryTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "   TEMPORADAS CON MAS REVIEWS POR PAIS  \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printChapterGeneralTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "  CAPITULOS CON MAS REVIEWS EN GENERAL  \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;

            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

void printChapterCountryTopRev(TopRev *top_head){

    if (top_head){

        TopRev *aux = top_head;
        int num = 1;

        cout << "========================================\n";
        cout << "   CAPITULOS CON MAS REVIEWS POR PAIS   \n";
        cout << "========================================\n";

        while (aux){

            cout << num << ". " << aux->name << " --- Num. de reviews: " << aux->num_rev << endl; 
            cout << "========================================\n";

            if (num != 5) ++num;
            else break;
            
            aux = aux->next_top;

        }

    }
    else{
        cout << "AVISO: No se encontraron calificaciones!\n";
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void addTopCali(TopCali **top_head, string name, float average){

    TopCali *new_top = createTopCali(name, average);

    if (!*top_head){
        *top_head = new_top;
    }
    else{

        TopCali *aux = *top_head;

        if (aux->average <= new_top->average){
            new_top -> next_top = aux;
            *top_head = new_top;
        }
        else{
            
            TopCali *aux2 = NULL;

            while (aux->average > new_top->average){
                aux2 = aux;
                aux = aux->next_top;
                if (aux == NULL) break;
            }

            aux2->next_top = new_top;
            new_top->next_top = aux;

        }
    }
}

void addTopRev(TopRev **top_head, string name, int num_rev){

    TopRev *new_top = createTopRev(name, num_rev);

    if (!*top_head){
        *top_head = new_top;
    }
    else{

        TopRev *aux = *top_head;

        if (aux->num_rev <= new_top->num_rev){
            new_top -> next_top = aux;
            *top_head = new_top;
        }
        else{
            
            TopRev *aux2 = NULL;

            while (aux->num_rev > new_top->num_rev){
                aux2 = aux;
                aux = aux->next_top;
                if (aux == NULL) break;
            }

            aux2->next_top = new_top;
            new_top->next_top = aux;

        }
    }
}

float caliAverage(float total_sum, float num_cali){
    float average = 0;
    average = total_sum / num_cali;
    return average;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void topMoviesByGeneral(MovieCalification *movie_cali_head){

    TopCali *movie_top = NULL;

    if (movie_cali_head){

        MovieCalification *aux = movie_cali_head;
        MovieCalification *movie = aux;

        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (movie){
                
                if (aux->movie_name == movie->movie_name){
                    total_sum += movie->calification;
                    ++count_cali;
                }

                movie = movie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);

            total_sum = 0;
            count_cali = 0;

            if (findNameTopCali(movie_top, aux->movie_name) == false) addTopCali(&movie_top, aux->movie_name, average);

            aux = aux->next_calification; 
            movie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en peliculas vacia!\n";
    }
    printMovieGeneralTopCali(movie_top);
}

void topMoviesByCountry(MovieCalification *movie_cali_head){

    TopCali *movie_top = NULL;

    if (movie_cali_head){

        MovieCalification *aux = movie_cali_head;
        MovieCalification *movie = aux;

        string country = searchCountryMenu();
        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (movie){
                
                if ((aux->movie_name == movie->movie_name) && (movie->user->country == country)){
                    total_sum += movie->calification;
                    ++count_cali;
                }

                movie = movie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);
            total_sum = 0;
            count_cali = 0;

            if ((findNameTopCali(movie_top, aux->movie_name) == false) && (aux->user->country == country)) addTopCali(&movie_top, aux->movie_name, average);

            aux = aux->next_calification; 
            movie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en peliculas vacia!\n";
    }
    printMovieCountryTopCali(movie_top);
}

void topMoviesByType(MovieCalification *movie_cali_head){

    TopCali *movie_top = NULL;

    if (movie_cali_head){

        MovieCalification *aux = movie_cali_head;
        MovieCalification *movie = aux;

        string type = searchTypeMenu();
        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (movie){
                
                if ((aux->movie_name == movie->movie_name) && (movie->movie->movie_type == type)){
                    total_sum += movie->calification;
                    ++count_cali;
                }

                movie = movie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);
            total_sum = 0;
            count_cali = 0;

            if ((findNameTopCali(movie_top, aux->movie_name) == false) && (aux->movie->movie_type == type)) addTopCali(&movie_top, aux->movie_name, average);

            aux = aux->next_calification; 
            movie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en peliculas vacia!\n";
    }
    printMovieTypeTopCali(movie_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void topSeriesByGeneral(SerieCalification *serie_cali_head){

    TopCali *serie_top = NULL;

    if (serie_cali_head){

        SerieCalification *aux = serie_cali_head;
        SerieCalification *serie = aux;

        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (serie){
                
                if (aux->serie_name == serie->serie_name){
                    total_sum += serie->calification;
                    ++count_cali;
                }

                serie = serie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);
            total_sum = 0;
            count_cali = 0;

            if (findNameTopCali(serie_top, aux->serie_name) == false) addTopCali(&serie_top, aux->serie_name, average);

            aux = aux->next_calification; 
            serie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en series vacia!\n";
    }
    printMovieGeneralTopCali(serie_top);
}

void topSeriesByCountry(SerieCalification *serie_cali_head){

    TopCali *serie_top = NULL;

    if (serie_cali_head){

        SerieCalification *aux = serie_cali_head;
        SerieCalification *serie = aux;

        string country = searchCountryMenu();
        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (serie){
                
                if ((aux->serie_name == serie->serie_name) && (serie->user->country == country)){
                    total_sum += serie->calification;
                    ++count_cali;
                }

                serie = serie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);
            total_sum = 0;
            count_cali = 0;

            if ((findNameTopCali(serie_top, aux->serie_name) == false) && (aux->user->country == country)) addTopCali(&serie_top, aux->serie_name, average);

            aux = aux->next_calification; 
            serie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en series vacia!\n";
    }
    printMovieCountryTopCali(serie_top);
}

void topSeriesByType(SerieCalification *serie_cali_head){

    TopCali *serie_top = NULL;

    if (serie_cali_head){

        SerieCalification *aux = serie_cali_head;
        SerieCalification *serie = aux;

        string country = searchTypeMenu();
        float total_sum = 0;
        float average = 0;
        int count_cali = 0;

        while (aux){

            while (serie){
                
                if ((aux->serie_name == serie->serie_name) && (serie->serie->type == country)){
                    total_sum += serie->calification;
                    ++count_cali;
                }

                serie = serie->next_calification;

            }

            average = caliAverage(total_sum, count_cali);
            total_sum = 0;
            count_cali = 0;

            if ((findNameTopCali(serie_top, aux->serie_name) == false) && (aux->serie->type == country)) addTopCali(&serie_top, aux->serie_name, average);

            aux = aux->next_calification; 
            serie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de calificaciones en series vacia!\n";
    }
    printMovieCountryTopCali(serie_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void moreRevMoviesByGeneral(MovieReview *movie_rev_head){

    TopRev *movie_top = NULL;

    if (movie_rev_head){

        MovieReview *aux = movie_rev_head;
        MovieReview *movie = aux;

        int count_rev = 0;

        while (aux){

            while (movie){
                
                if (aux->movie_name == movie->movie_name){
                    ++count_rev;
                }

                movie = movie->next_review;

            }

            if (findNameTopRev(movie_top, aux->movie_name) == false) addTopRev(&movie_top, aux->movie_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            movie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en peliculas vacia!\n";
    }
    printMovieGeneralTopRev(movie_top);
}

void moreRevMoviesByCountry(MovieReview *movie_rev_head){

    TopRev *movie_top = NULL;

    if (movie_rev_head){

        MovieReview *aux = movie_rev_head;
        MovieReview *movie = aux;

        string country = searchCountryMenu();
        int count_rev = 0;

        while (aux){

            while (movie){
                
                if ((aux->movie_name == movie->movie_name) && (aux->user->country == country)){
                    ++count_rev;
                }

                movie = movie->next_review;

            }

            if ((findNameTopRev(movie_top, aux->movie_name) == false) && aux->user->country == country) addTopRev(&movie_top, aux->movie_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            movie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en peliculas vacia!\n";
    }
    printMovieCountryTopRev(movie_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void moreRevSeriesByGeneral(SerieReview *serie_rev_head){

    TopRev *serie_top = NULL;

    if (serie_rev_head){

        SerieReview *aux = serie_rev_head;
        SerieReview *serie = aux;

        int count_rev = 0;

        while (aux){

            while (serie){
                
                if (aux->serie_name == serie->serie_name){
                    ++count_rev;
                }

                serie = serie->next_review;

            }

            if (findNameTopRev(serie_top, aux->serie_name) == false) addTopRev(&serie_top, aux->serie_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            serie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en series vacia!\n";
    }
    printSerieGeneralTopRev(serie_top);
}

void moreRevSeriesByCountry(SerieReview *serie_rev_head){

    TopRev *serie_top = NULL;

    if (serie_rev_head){

        SerieReview *aux = serie_rev_head;
        SerieReview *serie = aux;

        string country = searchCountryMenu();
        int count_rev = 0;

        while (aux){

            while (serie){
                
                if ((aux->serie_name == serie->serie_name) && (aux->user->country == country)){
                    ++count_rev;
                }

                serie = serie->next_review;

            }

            if ((findNameTopRev(serie_top, aux->serie_name) == false) && aux->user->country == country) addTopRev(&serie_top, aux->serie_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            serie = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en series vacia!\n";
    }
    printSerieCountryTopRev(serie_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void moreRevSeasonsByGeneral(SeasonReview *season_rev_head){

    TopRev *season_top = NULL;

    if (season_rev_head){

        SeasonReview *aux = season_rev_head;
        SeasonReview *season = aux;

        int count_rev = 0;

        while (aux){

            while (season){
                
                if (aux->season_name == season->season_name){
                    ++count_rev;
                }

                season = season->next_review;

            }

            if (findNameTopRev(season_top, aux->season_name) == false) addTopRev(&season_top, aux->season_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            season = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en temporadas vacia!\n";
    }
    printSeasonGeneralTopRev(season_top);
}

void moreRevSeasonsByCountry(SeasonReview *season_rev_head){

    TopRev *season_top = NULL;

    if (season_rev_head){

        SeasonReview *aux = season_rev_head;
        SeasonReview *season = aux;

        string country = searchCountryMenu();
        int count_rev = 0;

        while (aux){

            while (season){
                
                if ((aux->season_name == season->season_name) && (aux->user->country == country)){
                    ++count_rev;
                }

                season = season->next_review;

            }

            if (findNameTopRev(season_top, aux->season_name) == false) addTopRev(&season_top, aux->season_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            season = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en temporadas vacia!\n";
    }
    printSeasonCountryTopRev(season_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void moreRevChaptersByGeneral(ChapterReview *chapter_rev_head){

    TopRev *chapter_top = NULL;

    if (chapter_rev_head){

        ChapterReview *aux = chapter_rev_head;
        ChapterReview *chapter = aux;

        int count_rev = 0;

        while (aux){

            while (chapter){
                
                if (aux->chapter_name == chapter->chapter_name){
                    ++count_rev;
                }

                chapter = chapter->next_review;

            }

            if (findNameTopRev(chapter_top, aux->chapter_name) == false) addTopRev(&chapter_top, aux->chapter_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            chapter = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en capitulos vacia!\n";
    }
    printChapterGeneralTopRev(chapter_top);
}

void moreRevChaptersByCountry(ChapterReview *chapter_rev_head){

    TopRev *chapter_top = NULL;

    if (chapter_rev_head){

        ChapterReview *aux = chapter_rev_head;
        ChapterReview *chapter = aux;

        string country = searchCountryMenu();
        int count_rev = 0;

        while (aux){

            while (chapter){
                
                if ((aux->chapter_name == chapter->chapter_name) && (aux->user->country == country)){
                    ++count_rev;
                }

                chapter = chapter->next_review;

            }

            if (findNameTopRev(chapter_top, aux->chapter_name) == false) addTopRev(&chapter_top, aux->chapter_name, count_rev);
            count_rev = 0;

            aux = aux->next_review; 
            chapter = aux;

        }

    }
    else{
        cout << "AVISO: Lista de reviews en capitulos vacia!\n";
    }
    printChapterCountryTopRev(chapter_top);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void driveOustandingMovie(MovieCalification *movie_cali_head, MovieReview *movie_review_head){
    int menu = 0;
    do{
        menu = outstandingMovieMenu();
        switch(menu){
            case 1:{
                topMoviesByCountry(movie_cali_head);
                break;
            }
            case 2:
            {
                topMoviesByType(movie_cali_head);
                break;
            }
            case 3:
            {
                topMoviesByGeneral(movie_cali_head);  
                break;
            }
            case 4:
            {
                moreRevMoviesByCountry(movie_review_head);
                break;
            }
            case 5:
            {
                moreRevMoviesByGeneral(movie_review_head);
                break;
            }
            default:
            {
                if (menu == 0){
                    cout << "Regresando al menu de destacados...\n";
                    system("cls");
                }
                else cout << "VUELVE A INTENTAR\n"; 
                break;
            }
        }
    }while (menu != 0);
}

void driveOustandingSerie(SerieCalification *serie_cali_head, SerieReview *serie_review_head){
    int menu = 0;
    do{
        menu = outstandingSerieMenu();
        switch(menu){
            case 1:{
                topSeriesByCountry(serie_cali_head);
                break;
            }
            case 2:
            {
                topSeriesByType(serie_cali_head);
                break;
            }
            case 3:
            {
                topSeriesByGeneral(serie_cali_head);
                break;
            }
            case 4:
            {
                moreRevSeriesByCountry(serie_review_head);
                break;
            }
            case 5:
            {
                moreRevSeriesByGeneral(serie_review_head);
                break;
            }
            default:
            {
                if (menu == 0){
                    cout << "Regresando al menu de destacados...\n";
                    system("cls");
                }
                else cout << "VUELVE A INTENTAR\n"; 
                break;
            }
        }
    }while (menu != 0);
}

void driveOustandingSeason(SeasonReview *season_review_head){
    int menu = 0;
    do{
        menu = outstandingSeasonMenu();
        switch(menu){
            case 1:{
                moreRevSeasonsByCountry(season_review_head);
                break;
            }
            case 2:
            {
                moreRevSeasonsByGeneral(season_review_head);
                break;
            }
            default:
            {
                if (menu == 0){
                    cout << "Regresando al menu de destacados...\n";
                    system("cls");
                }
                else cout << "VUELVE A INTENTAR\n"; 
                break;
            }
        }
    }while (menu != 0);
}

void driveOustandingChapter(ChapterReview *chapter_review_head){
    int menu = 0;
    do{
        menu = outstandingSeasonMenu();
        switch(menu){
            case 1:{
                moreRevChaptersByCountry(chapter_review_head);
                break;
            }
            case 2:
            {
                moreRevChaptersByGeneral(chapter_review_head);
                break;
            }
            default:
            {
                if (menu == 0){
                    cout << "Regresando al menu de destacados...\n";
                    system("cls");
                }
                else cout << "VUELVE A INTENTAR\n"; 
                break;
            }
        }
    }while (menu != 0);
}