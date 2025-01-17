// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "calificationSerieLibrary.h"

using namespace std;

SerieReview *getSerieReviewNode(SerieReview *review_head, string serie_name, string user_email){

    if (review_head){
        SerieReview *aux = review_head;
        while (aux){
            if (aux -> serie_name == serie_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_review;
        }
    }
    return NULL;

}

bool findSerieReviewBool(SerieReview *review_head, string serie_name , string user_email){
    if (review_head){
        SerieReview *aux = review_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> user -> email == user_email)) return true;
            aux = aux -> next_review;
        }
    }
    return false;
}

/*
    Funcion que retorna la cantidad de reseñas que tenga una serie.

    @param *review_head Es un puntero de la estructura SerieReview que señala a la cabeza de la lista de reseñas designadas a series.
    @param serie_name Es un dato de tipo cadena que maneja como contenido el nombre de la serie a la que se hizo reseña.

    @return La funcion retorna la variable count que segun tal condicion puede retornar 0 o un numero mayor.
*/
int countNumSerieReviewInSerie(SerieReview *review_head, string serie_name){
    int count = 0;
    if (review_head){
        SerieReview *aux = review_head;
        while (aux){
            if (aux->serie_name == serie_name) ++count;
            aux = aux -> next_review;
        }
    }
    return count;
}

/*
    Funcion que retorna la cantidad de reseñas que tenga una serie.

    @param *review_head Es un puntero de la estructura SerieReview que señala a la cabeza de la lista de reseñas designadas a series.
    @param user_email Es un dato de tipo cadena que maneja como contenido el email del usuario que hizo la reseña.

    @return La funcion retorna una variable de tipo entero llamada count que segun tal condicion puede retornar 0 o un numero mayor.
*/
int countNumSerieReviewInUser(SerieReview *review_head, string user_email){
    int count = 0;
    if (review_head){
        SerieReview *aux = review_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux -> next_review;
        }
    }
    return count;
}

/* Funcion para obtener una reseña */
string getSerieReview(){

    string review;
    bool bol = false;
    
    while (bol == false){

        cin.ignore();
        cout << "\tReview: ";
        getline(cin, review);

        bol = checkReviewLength(review);
        
        if (bol == false) cout << "ERROR. Ingresar un maximo de 250 caracteres!\n";
    }
    return review;
} 

SerieReview *createSerieReview(string review, int id, Serie *serie, Users *user){

    SerieReview *new_review = new SerieReview;

    new_review -> serie_name = serie->serie_name;
    new_review -> user_email = user -> email;
    new_review -> review = review;
    new_review -> id = id;

    new_review -> serie = serie;
    new_review -> user = user;

    new_review -> next_review = NULL;

    return new_review;
}

void addSerieReview(SerieReview **review_head, string review, int id, Serie *serie, Users *user){
    SerieReview *new_review =  createSerieReview(review, id, serie, user);
    if (review_head){
        new_review -> next_review = *review_head;
        *review_head = new_review;
    }
    else *review_head = new_review;
}

void deleteSerieReview(SerieReview **review_head, string serie_name, string user_email){

    if (*review_head){

        SerieReview *aux = *review_head;

        if (aux->serie_name == serie_name && aux->user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            SerieReview *aux2 = NULL;

            while (aux){
                aux2 = aux;
                aux = aux->next_review;
                if (aux->serie_name == serie_name && aux->user_email == user_email) break;
            }

            if (aux->serie_name == serie_name && aux->user_email == user_email){
                aux2 -> next_review = aux -> next_review;
                delete(aux);
            }
            else{
                cout << "ERROR. No se pudo encontrar la review.\n";
            }

        }
    }
    else{
        cout << "ERROR. Lista de reviews vacia!\n";
    }
}

void deleteSerieReviewBySerie(SerieReview **review_head, string serie_name){

    if (*review_head){

        SerieReview *aux = *review_head;

        if (aux->serie_name == serie_name){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            SerieReview *aux2 = NULL;

            while (aux){
                aux2 = aux;
                aux = aux -> next_review;
                if (aux->serie_name == serie_name) break;
            }

            if (aux->serie_name == serie_name){
                aux2 -> next_review = aux -> next_review;
                delete(aux);
            }
            else{
                cout << "ERROR. No se pudo encontrar la review.\n";
            }            
        }
    }
    else cout << "ERROR. Lista de reviews vacia!\n";
}

void deleteSerieReviewByUser(SerieReview **review_head, string user_email){

    SerieReview *aux = *review_head;

    if (aux){

        if (aux->user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            SerieReview *aux2 = NULL;

            while (aux->user_email != user_email){
                aux2 = aux;
                aux = aux -> next_review;
            }

            aux2 -> next_review = aux -> next_review;
            delete(aux);
        
        }
    }
    else{
        cout << "ERROR. Lista de reviews vacia!\n";
    }
}

void editSerieReview(SerieReview *review_head, string review, string serie_name, string user_email){

    if (findSerieReviewBool(review_head, serie_name, user_email) == true){

        SerieReview *new_review = getSerieReviewNode(review_head, serie_name, user_email);
        new_review -> review = review;
        cout << "AVISO: Review EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}

int reviewSerieMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "           SERIE REVIEWS MENU           \n";
        cout << "========================================\n";
        cout << "(1) Mostrar reviews \n";
        cout << "(2) Agregar review\n";
        cout << "(3) Borrar review\n";
        cout << "(0) Volver a series\n";
        cout << "========================================\n";
        cout << " Opcion: ";
        cin >> menu;

        if (menu < "0" || menu > "3"){
            cout << "ERROR. Ingresaste " << menu << endl;
            cout << "Ingresa una opcion valida.\n";
        }

    } while (menu < "0" || menu > "3");

    return stoi(menu);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSerieReviewsInSerie(SerieReview *review_head, string serie_name){

    cout << "========================================\n";
    cout << "              SERIE REVIEWS             \n";
    cout << "========================================\n";

    if (countNumSerieReviewInSerie(review_head, serie_name) > 0){

        SerieReview *aux = review_head;
        
        while (aux){
            if (aux->serie_name == serie_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux -> review  << endl;
                cout << "========================================\n";
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews en la serie\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSerieReviewsInUser(SerieReview *review_head, string user_email){

    cout << "========================================\n";
    cout << "              USER REVIEWS              \n";
    cout << "========================================\n";

    if (countNumSerieReviewInUser(review_head, user_email) > 0){

        SerieReview *aux = review_head;
        
        while (aux){
            if (aux->user_email == user_email){
                cout << "Serie: " << aux -> serie_name << endl;
                cout << "Review: " << aux -> review  << endl;
                cout << "========================================\n";
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews del usuario\n";
}

void showSerieReview(SerieReview *review_head){

    cout << "========================================\n";
    cout << "             SERIE REVIEWS             \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        SerieReview *aux = review_head;

        while (aux){

            cout << "Serie: " << aux->serie_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Review: " << aux->review << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_review;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA REVIEWS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA REVIEWS */

void readSerieReviewFile(SerieReview **review_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text, serie_name, user_email, review;
  int data_line = 0, id;
  SerieReview *aux = *review_head;
  Serie *serie = NULL;
  Users *user = NULL;

  file.open("reviewseriefile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de REVIEWS EN serieS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "SERIES REVIEWS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1) serie = getSerieNodeByName(serie_head, text);

            if (data_line == 2) user = getUsersNode(user_head, text);

            if (data_line == 3) review = text;

            if (data_line == 4){
                if (checkIntSerieCalificationId(text) == true){
                    id = stoi(text);
                    addSerieReview(&aux, review, id, serie, user);
                }
            }

            ++data_line;

            if (data_line == 5) data_line = 0;

        }

        *review_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de reviews en series!\n\n";
    }

    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN REVIEWS */

void addSerieReviewToFile(string serie_name, string user_email, string review, int id){

  ofstream file;

  file.open("reviewseriefile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << user_email;
  file << endl << review;
  file << endl << id;

  file.close();
}

void writeSerieReviewFile(SerieReview *reviews_head){

    if (reviews_head){

        ofstream file;
        file.open("reviewseriefile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

            SerieReview *aux = reviews_head;

            file << "SERIES REVIEWS\n\n";

            while(aux){

                file << aux -> serie_name << endl;
                file << aux -> user_email << endl;
                file << aux -> review << endl;

                if (aux -> next_review == NULL) file << aux -> id;
                else file << aux -> id << endl << endl;

                aux = aux -> next_review;
            }
        }
    }
    else{

        ofstream file;
        file.open("reviewsfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else file << "REVIEWS\n\n";
    
    }
}

void addSerieReviewMenu(SerieReview **review_head, Serie *serie_head, Users *user_head){

    cout << "========================================\n";
    cout << "        ADD OR EDIT SERIE REVIEW        \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string user_email = getUsersEmail();
    string review = getSerieReview();
    int id = getSerieCalificationId();
    cout << "========================================\n";

    bool serie_exist = findSerieByName(serie_head, serie_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( serie_exist == true && user_exist == true){

        bool review_exist = findSerieReviewBool(*review_head, serie_name, user_email);

        if ( review_exist == false){

            Serie *serie = getSerieNodeByName(serie_head, serie_name);
            Users *user = getUsersNode(user_head, user_email);
            addSerieReview(&*review_head, review, id, serie, user);

            cout << "AVISO: review AGREGADA con exito\n";

        }
        else editSerieReview(*review_head, review, serie_name, user_email);
        
        writeSerieReviewFile(*review_head);

    }
    else 
        cout << "ERROR. La serie o el usuario ingresado no han sido encontrados!\n";
}

void deleteSerieReviewMenu(SerieReview **review_head){

    cout << "========================================\n";
    cout << "           DELETE SERIE REVIEW          \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string user_email = getUsersEmail();
    cout << "\n";
    cout << "========================================\n";

    bool review_exist = findSerieReviewBool(*review_head, serie_name, user_email);

    if (review_exist == true){
        deleteSerieReview(&*review_head, serie_name, user_email);
        writeSerieReviewFile(*review_head);
        cout << "AVISO: La review ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}