// @author Freddy Fernández

#include <iostream>
#include "getCinLibrary.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

// STRUCTS

// @brief Define los elementos de la estructura usuario.
struct Users{
    string email;
    int years_old;
    string country;
    int id;

    Users *next_user;
};

/////////////////////////////////////////////////////////////////////////////////////////////

// @brief Define los elementos de la estructura pelicula.  
struct Movie{
    string movie_name;
    int movie_premiere;
    string movie_type;
    int movie_time;
    int movie_id;

    Movie *next_movie;
};

/////////////////////////////////////////////////////////////////////////////////////////////


// @brief Define los elementos de la estructura capitulo.
struct Chapter{

    string chapter_name;
    int chapter_premiere;
    int chapter_time;
    int chapter_num;
    int id;

    Chapter *next_chapter;

};

// @brief Define los elementos de la estructura temporada.
struct Season{

    string season_name;
    int season_premiere;
    int id;

    Chapter *chapters_head;
    Season *next_season;

};

// @brief Define los elementos de la estructura serie.
struct Serie{

    string serie_name;
    int serie_premiere;
    string type;
    int id;

    Season *season_head;
    Serie *next_serie;

};

/////////////////////////////////////////////////////////////////////////////////////////////

// @brief Define los elementos de la estructura calificacion en pelicula.
struct MovieCalification{

    string movie_name;
    string user_email;
    float calification;
    int id;

    Movie *movie;
    Users *user;
    MovieCalification *next_calification;

};

// @brief Define los elementos de la estructura reseña en pelicula.
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

// @brief Define los elementos de la estructura calificacion en serie.
struct SerieCalification{

    string serie_name;
    string user_email;
    float calification;
    int id;

    Serie *serie;
    Users *user;
    SerieCalification *next_calification;

};

// @brief Define los elementos de la estructura reseña en serie.
struct SerieReview{

    string serie_name;
    string user_email;
    string review;
    int id;

    Serie *serie;
    Users *user;

    SerieReview *next_review;

};

// @brief Define los elementos de la estructura reseña en una temporada.
struct SeasonReview{

    string serie_name;
    string season_name;
    string user_email;
    string review;
    int id;

    Season *season;
    Users *user;
    SeasonReview *next_review;

};

// @brief Define los elementos de la estructura reseña en un capitulo.
struct ChapterReview{

    string serie_name;
    string chapter_name;
    string user_email;
    string review;
    int id;

    Chapter *chapter;
    Users *user;
    ChapterReview *next_review;

};
