#include <iostream>
#include "getCinLibrary.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

// STRUCT

/*El siguiente struct sirve para almacenar el conjunto de elementos de los usuarios
  como el correo, la edad, el pais, la calificaciones y las reseñas.*/

struct Users{
    string email;
    int years_old;
    string country;
    int id;

    Users *next_user;
};

/////////////////////////////////////////////////////////////////////////////////////////////

/*El siguiente struct sirve para almacenar el conjunto de elementos de las peliculas
  como el nombre, la fecha de estreno, el genero, la duracion y el pais.*/
  
struct Movie{
    string movie_name;
    int movie_premiere;
    string movie_type;
    int movie_time;
    int movie_id;

    Movie *next_movie;
};

/////////////////////////////////////////////////////////////////////////////////////////////

struct Chapter{

    string chapter_name;
    int chapter_premiere;
    int chapter_time;
    int chapter_num;
    int id;

    Chapter *next_chapter;

};

struct Season{

    string season_name;
    int season_premiere;
    int id;

    Chapter *chapters_head;
    Season *next_season;

};

struct Serie{

    string serie_name;
    int serie_premiere;
    string type;
    int id;

    Season *season_head;
    Serie *next_serie;

};

/////////////////////////////////////////////////////////////////////////////////////////////

struct MovieCalification{

    string movie_name;
    string user_email;
    float calification;
    int id;

    Movie *movie;
    Users *user;
    MovieCalification *next_calification;

};

struct MovieReview{

    string movie_name;
    string user_email;
    string review;
    int id;

    Movie *movie;
    Users *user;

    MovieReview *next_review;

};

/////////////////////////////////////////////////////////////////////////////////////////////