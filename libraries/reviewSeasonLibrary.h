// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "reviewSerieLibrary.h"

using namespace std;

bool checkIntSeasonReviewId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

/* Funcion para obtener una reseña */
string getSeasonReview(){

  string review;
  cin.ignore();
  cout << "\tReview: ";
  getline(cin, review);
  return review;
} 

SeasonReview *getSeasonReviewNode(SeasonReview *review_head, string season_name, string user_email){

    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if (aux -> season_name == season_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_review;
        }
    }
    return NULL;
}

bool findSeasonReviewBool(SeasonReview *review_head,string serie_name, string season_name , string user_email){
    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if ((aux -> season_name == season_name) && (aux -> user -> email == user_email) && (aux -> serie_name == serie_name)) return true;
            aux = aux -> next_review;
        }
    }
    return false;
}

int getSeasonReviewId(){

  string cali_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> cali_id;

    check_num = checkIntSeasonReviewId(cali_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(cali_id);
}

SeasonReview *createSeasonReview(string serie_name, string review, int id, Season *season, Users *user){

    SeasonReview *new_calification = new SeasonReview;

    new_calification -> serie_name = serie_name;
    new_calification -> season_name = season->season_name;
    new_calification -> user_email = user->email;
    new_calification -> review = review;
    new_calification -> id = id;
    
    new_calification -> season = season;
    new_calification -> user = user;
    new_calification -> next_review = NULL;

    return new_calification;
}

void addSeasonReview(SeasonReview **review_head, string serie_name, string review, int id, Season *season, Users *user){

    SeasonReview *new_calification = createSeasonReview(serie_name, review, id, season, user);

    if (!*review_head) *review_head = new_calification;
    else{
        new_calification->next_review = *review_head;
        *review_head = new_calification;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS CALIFICACIONES DE PELICULAS Y USUARIOS */

int countNumSeasonReviewInSeason(SeasonReview *review_head, string season_name){
    int count = 0;
    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if (aux->season_name == season_name) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

int countNumSeasonReviewInUser(SeasonReview *review_head, string user_email){
    int count = 0;
    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

int countUserSeasonReview(SeasonReview *review_head, string email){
    int count = 0;
    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if (aux->user->email == email) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

int countNumSeasonReviewInSerie(SeasonReview *review_head, string serie_name){
    int count = 0;
    if (review_head){
        SeasonReview *aux = review_head;
        while (aux){
            if (aux->serie_name == serie_name) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

void deleteSeasonReview(SeasonReview **review_head, string season_name, string user_email){

    if (*review_head){

        SeasonReview *aux = *review_head;

        if (aux -> season_name == season_name && aux -> user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            SeasonReview *aux2 = NULL;

            while (aux){

                if (aux -> season_name == season_name && aux -> user_email == user_email){
                    aux2 -> next_review = aux -> next_review;
                    delete(aux);
                }

                aux2 = aux;
                aux = aux -> next_review;

            }
        }
    }
    else
        cout << "ERROR. Lista de reviews vacia!\n";
}

void deleteSeasonRev(SeasonReview **review_head, string serie_name, string season_name){

    if (*review_head){
        
        SeasonReview *aux = *review_head;

        if (aux->season_name == season_name && aux->serie_name == serie_name){
            *review_head = aux->next_review;
            delete(aux);
        }
        else{

            SeasonReview *aux2;

            while (aux->season_name != season_name && aux->serie_name == serie_name){

                aux2 = aux;
                aux = aux->next_review;
                if (aux == NULL) break;
            }

            if (aux->season_name == season_name && aux->serie_name == serie_name){
                aux2->next_review = aux->next_review;
                delete(aux);
            }
        }
    }
    else
        cout << "AVISO: No se encontraron reviews en esta temporada!\n";
}

void deleteSeasonRevByUser(SeasonReview **review_head, string email){

    if (*review_head){
        
        SeasonReview *aux = *review_head;

        if (aux->user_email == email){
            *review_head = aux->next_review;
            delete(aux);
        }
        else{

            SeasonReview *aux2 = NULL;

            while (aux->user_email != email){
                aux2 = aux;
                aux = aux->next_review;
            }

            if (aux->user_email == email){
                aux2->next_review = aux->next_review;
                delete(aux);
            }
        }
    }
    else{
        cout << "AVISO: No se encontraron reviews en esta temporada!\n";
    }
}

void deleteSeasonRevBySerie(SeasonReview **review_head, string serie_name){

    if (*review_head){

        SeasonReview *aux = *review_head;

        if (aux->serie_name == serie_name){
            *review_head = aux->next_review;
            delete(aux);
        }
        else{

            SeasonReview *aux2 = NULL;

            while (aux->serie_name != serie_name){
                aux2 = aux;
                aux = aux->next_review;
            }

            aux2->next_review = aux->next_review;
            delete(aux);
        }

    }
    else{
        cout << "AVISO: No se encontraron reviews en esta temporada!\n";
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA CALIFICACIONES */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA CALIFICACIONES */


void readSeasonReviewFile(SeasonReview **review_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text, review;
  int data_line = 0, id;
  SeasonReview *aux = *review_head;
  Serie *serie = serie_head;
  Season *season = NULL;
  Users *user = NULL;

  file.open("reviewseasonfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de REVIEWS EN TEMPORADAS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "SEASONS REVIEWS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1){

                if (findSerieByName(serie_head, text) == true){
                    serie = getSerieNodeByName(serie_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en temporadas!\n\n";
                    file.close();
                }
            }

            if (data_line == 2){

                if (findSeasonByName(serie->season_head, text) == true){
                    season = getSeasonNodeByName(serie->season_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en temporadas!\n\n";
                    file.close();
                }
                
            }

            if (data_line == 3){
                
                if (findUsers(user_head, text) == true){
                    user = getUsersNode(user_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en temporadas!\n\n";
                    file.close();
                }

            }

            if (data_line == 4) review = text;

            if (data_line == 5){
                if (checkIntSeasonReviewId(text) == true){
                    id = stoi(text);
                    addSeasonReview(&aux, serie->serie_name, review, id, season, user);
                }
            }

            ++data_line;

            if (data_line == 6) data_line = 0;

        }

        *review_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de reviews en temporadas!\n\n";
    }

    file.close();
}

 /* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN CALIFICACIONES */

void addSeasonReviewToFile(string serie_name, string season_name, string user_email, string review, int id){

  ofstream file;

  file.open("reviewseasonfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << season_name;
  file << endl << user_email;
  file << endl << review;
  file << endl << id;

  file.close();
}

void writeSeasonReviewFile(SeasonReview *review_head){

    if (review_head){

        ofstream file;
        file.open("reviewseasonfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        SeasonReview *aux = review_head;

        file << "SEASONS REVIEWS\n\n";

        while(aux){

            file << aux -> serie_name << endl;
            file << aux -> season_name << endl;
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
        file.open("reviewseasonfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "SEASONS REVIEWS\n\n";
        }
    }
}

void editSeasonReview(SeasonReview *review_head, string review,string serie_name, string season_name, string user_email){

    if (findSeasonReviewBool(review_head, serie_name, season_name, user_email) == true){

        SeasonReview *new_cali = getSeasonReviewNode(review_head, season_name, user_email);
        new_cali -> review = review;
        cout << "AVISO: Review EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}

void addSeasonReviewMenu(SeasonReview **review_head, Season *season_head, Users *user_head, string serie_name){

    cout << "========================================\n";
    cout << "       ADD OR EDIT SEASON REVIEW        \n";
    cout << "========================================\n";
    string season_name = getSeasonName();
    string review = getSeasonReview();
    string user_email = getUsersEmail();
    int id = getSeasonReviewId();
    cout << "========================================\n";

    bool season_exist = findSeasonByName(season_head, season_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( season_exist == true && user_exist == true){

        bool review_exist = findSeasonReviewBool(*review_head, serie_name, season_name, user_email);

        if ( review_exist == false){

            Season *season = getSeasonNodeByName(season_head, season_name);
            Users *user = getUsersNode(user_head, user_email);
            addSeasonReview(&*review_head, serie_name, review, id, season, user);

            cout << "AVISO: Review AGREGADA con exito\n";

        }
        else {
            editSeasonReview(*review_head, review, serie_name, season_name, user_email);
        }

        writeSeasonReviewFile(*review_head);

    }
    else 
        cout << "ERROR. La temporada o el usuario ingresados no han sido encontrados!\n";
}

void deleteSeasonReviewMenu(SeasonReview **review_head){

    cout << "========================================\n";
    cout << "         DELETE SEASON REVIEW           \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string season_name = getSeasonName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool cali_exist = findSeasonReviewBool(*review_head, serie_name, season_name, user_email);

    if (cali_exist == true){
        deleteSeasonReview(&*review_head, season_name, user_email);
        writeSeasonReviewFile(*review_head);
        cout << "AVISO: La review ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La review ingresada no ha sido encontrada!\n";
}

int reviewSeasonMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "           SEASON REVIEW MENU           \n";
        cout << "========================================\n";
        cout << "(1) Mostrar reviews\n";
        cout << "(2) Agregar review\n";
        cout << "(3) Borrar review\n";
        cout << "(0) Volver a series\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        cin >> menu;

        if (menu < "0" || menu > "3"){
            cout << "ERROR. Ingresaste " << menu << endl;
            cout << "Ingresa una opcion valida.\n";
        }

    } while (menu < "0" || menu > "3");

    return stoi(menu);
}

void printSeasonReviewInUser(SeasonReview *review_head, string email){

    cout << "========================================\n";
    cout << "        USER REVIEWS IN SEASONS         \n";
    cout << "========================================\n";    

    if (countNumSeasonReviewInUser(review_head, email) > 0){

        SeasonReview *aux = review_head;
    
        while (aux){
            if (aux->user->email == email){
                cout << "Serie: " << aux->serie_name << endl;
                cout << "Temporada: " << aux->season_name << endl;
                cout << "Review: " << aux->review << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
            }
            aux = aux->next_review;
        }
    }
    else{
        cout << "AVISO: El usuario aun no tiene reviews.\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSeasonReviewInSeason(SeasonReview *review_head, string season_name){

    cout << "========================================\n";
    cout << "                REVIEWS                 \n";
    cout << "========================================\n";

    if (countNumSeasonReviewInSeason(review_head, season_name) > 0){

        SeasonReview *aux = review_head;
        
        while (aux){
            if (aux->season_name == season_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux -> review << endl;
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews en la temporada\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showSeasonCalifications(SeasonReview *review_head){

    cout << "========================================\n";
    cout << "            SEASONS REVIEWS             \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        SeasonReview *aux = review_head;

        while (aux){

            cout << "Temporada: " << aux->season_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Review: " << aux->review << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_review;
        }
    }
}

void showSeasonReviewBySerie(SeasonReview *review_head, string serie_name){

    cout << "========================================\n";
    cout << "            SEASONS REVIEWS             \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        SeasonReview *aux = review_head;
        int count = 0;

        while (aux){

            if (aux->serie_name == serie_name){

                cout << "Temporada: " << aux->season_name << endl;
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux->review << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
                ++count;
            }

            aux = aux -> next_review;

        }
        
        if (count == 0) cout << "AVISO. Las temporadas aun no tienen reviews!\n";

    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////