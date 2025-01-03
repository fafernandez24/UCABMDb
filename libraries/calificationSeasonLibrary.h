#include <iostream>
#include <fstream>
#include <string>
#include "reviewSerieLibrary.h"

using namespace std;

bool checkIntSeasonCalificationId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

bool checkFloatSeasonCalification(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stof(word) >= 0 && stof(word) <= 9999999) return true;

    return false;
}

SeasonCalification *getSeasonCalificationNode(SeasonCalification *cali_head, string season_name, string user_email){

    if (cali_head){
        SeasonCalification *aux = cali_head;
        while (aux){
            if (aux -> season_name == season_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_calification;
        }
    }
    return NULL;
}

bool findSeasonCalificationBool(SeasonCalification *cali_head,string serie_name, string season_name , string user_email){
    if (cali_head){
        SeasonCalification *aux = cali_head;
        while (aux){
            if ((aux -> season_name == season_name) && (aux -> user -> email == user_email) && (aux -> serie_name == serie_name)) return true;
            aux = aux -> next_calification;
        }
    }
    return false;
}

int getSeasonCalificationId(){

  string cali_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> cali_id;

    check_num = checkIntSeasonCalificationId(cali_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(cali_id);
}

SeasonCalification *createSeasonCalification(string serie_name, float calification, int id, Season *season, Users *user){

    SeasonCalification *new_calification = new SeasonCalification;

    new_calification -> serie_name = serie_name;
    new_calification -> season_name = season->season_name;
    new_calification -> user_email = user->email;
    new_calification -> calification = calification;
    new_calification -> id = id;
    
    new_calification -> season = season;
    new_calification -> user = user;
    new_calification -> next_calification = NULL;

    return new_calification;
}

void addSeasonCalification(SeasonCalification **cali_head, string serie_name, float calification, int id, Season *season, Users *user){

    SeasonCalification *new_calification = createSeasonCalification(serie_name, calification, id, season, user);

    if (!*cali_head) *cali_head = new_calification;
    else{
        new_calification->next_calification = *cali_head;
        *cali_head = new_calification;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS CALIFICACIONES DE PELICULAS Y USUARIOS */

int countNumSeasonCalificationInSeason(SeasonCalification *cali_head, string season_name){
    int count = 0;
    if (cali_head){
        SeasonCalification *aux = cali_head;
        while (aux){
            if (aux->season_name == season_name) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countNumSeasonCalificationInUser(SeasonCalification *cali_head, string user_email){
    int count = 0;
    if (cali_head){
        SeasonCalification *aux = cali_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countUserSeasonCali(SeasonCalification *cali_head, string email){
    int count = 0;
    if (cali_head){
        SeasonCalification *aux = cali_head;
        while (aux){
            if (aux->user->email == email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

void deleteSeasonCalification(SeasonCalification **cali_head, string season_name, string user_email){

    if (*cali_head){

        SeasonCalification *aux = *cali_head;

        if (aux -> season_name == season_name && aux -> user_email == user_email){
            *cali_head = aux -> next_calification;
            delete(aux);
        }
        else{

            SeasonCalification *aux2 = NULL;

            while (aux){

                if (aux -> season_name == season_name && aux -> user_email == user_email){
                    aux2 -> next_calification = aux -> next_calification;
                    delete(aux);
                }

                aux2 = aux;
                aux = aux -> next_calification;

            }
        }
    }
    else
        cout << "ERROR. Lista de calificaciones vacia!\n";
}

void deleteSeasonCali(SeasonCalification **cali_head, string serie_name, string season_name){

    if (*cali_head){
        
        SeasonCalification *aux = *cali_head;

        if (aux->season_name == season_name && aux->serie_name == serie_name){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            SeasonCalification *aux2;

            while ((aux->season_name != season_name && aux->serie_name == serie_name)|| (aux != NULL)){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux->season_name == season_name && aux->serie_name == serie_name){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else
        cout << "AVISO: No se encontraron calificaciones en esta temporada!\n";
}

void deleteUserSeasonCali(SeasonCalification **cali_head, string email){

    if (*cali_head){
        
        SeasonCalification *aux = *cali_head;

        if (aux->user_email == email){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            SeasonCalification *aux2 = NULL;

            while (aux->user_email != email){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux->user_email == email){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else{
        cout << "AVISO: No se encontraron calificaciones en esta temporada!\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA CALIFICACIONES */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA CALIFICACIONES */


void readSeasonCaliFile(SeasonCalification **cali_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text;
  float calification = 0;
  int data_line = 0, id;
  SeasonCalification *aux = *cali_head;
  Serie *serie = serie_head;
  Season *season = NULL;
  Users *user = NULL;

  file.open("caliseasonfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de CALIFICACIONES EN TEMPORADAS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "SEASONS CALIFICATIONS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1){

                if (findSerieByName(serie_head, text) == true){
                    serie = getSerieNodeByName(serie_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en temporadas!\n\n";
                    file.close();
                }
            }

            if (data_line == 2){

                if (findSeasonByName(serie->season_head, text) == true){
                    season = getSeasonNodeByName(serie->season_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en temporadas!\n\n";
                    file.close();
                }
                
            }

            if (data_line == 3){
                
                if (findUsers(user_head, text) == true){
                    user = getUsersNode(user_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en temporadas!\n\n";
                    file.close();
                }

            }

            if (data_line == 4) calification = stof(text);

            if (data_line == 5){
                if (checkIntSeasonCalificationId(text) == true){
                    id = stoi(text);
                    addSeasonCalification(&aux, serie->serie_name, calification, id, season, user);
                }
            }

            ++data_line;

            if (data_line == 6) data_line = 0;

        }

        *cali_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de calificaciones en temporadas!\n\n";
    }

    file.close();
}

 /* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN CALIFICACIONES */

void addSeasonCaliToFile(string serie_name, string season_name, string user_email, float calification, int id){

  ofstream file;

  file.open("caliseasonfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << season_name;
  file << endl << user_email;
  file << endl << calification;
  file << endl << id;

  file.close();
}

void writeSeasonCaliFile(SeasonCalification *cali_head){

    if (cali_head){

        ofstream file;
        file.open("caliseasonfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        SeasonCalification *aux = cali_head;

        file << "SEASONS CALIFICATIONS\n\n";

        while(aux){

            file << aux -> serie_name << endl;
            file << aux -> season_name << endl;
            file << aux -> user_email << endl;
            file << aux -> calification << endl;

            if (aux -> next_calification == NULL) file << aux -> id;
            else file << aux -> id << endl << endl;

            aux = aux -> next_calification;
        }
        }
    }
    else{
        ofstream file;
        file.open("caliseasonfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "SEASONS CALIFICATIONS\n\n";
        }
    }
}

void editSeasonCalification(SeasonCalification *cali_head, float calification,string serie_name, string season_name, string user_email){

    if (findSeasonCalificationBool(cali_head, serie_name, season_name, user_email) == true){

        SeasonCalification *new_cali = getSeasonCalificationNode(cali_head, season_name, user_email);
        new_cali -> calification = calification;
        cout << "AVISO: Calificacion EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

void addSeasonCalificationMenu(SeasonCalification **cali_head, Season *season_head, Users *user_head, string serie_name){

    cout << "========================================\n";
    cout << "    ADD OR EDIT SEASON CALIFICATION     \n";
    cout << "========================================\n";
    string season_name = getSeasonName();
    float calification = getCalification();
    string user_email = getUsersEmail();
    int id = getSeasonCalificationId();
    cout << "========================================\n";

    bool season_exist = findSeasonByName(season_head, season_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( season_exist == true && user_exist == true){

        bool cali_exist = findSeasonCalificationBool(*cali_head, serie_name, season_name, user_email);

        if ( cali_exist == false){

            Season *season = getSeasonNodeByName(season_head, season_name);
            Users *user = getUsersNode(user_head, user_email);
            addSeasonCalification(&*cali_head, serie_name, calification, id, season, user);

            cout << "AVISO: Calificacion AGREGADA con exito\n";

        }
        else {
            editSeasonCalification(*cali_head, calification, serie_name, season_name, user_email);
        }

        writeSeasonCaliFile(*cali_head);

    }
    else 
        cout << "ERROR. La serie o el usuario ingresados no han sido encontrados!\n";
}

void deleteSeasonCalificationMenu(SeasonCalification **cali_head){

    cout << "========================================\n";
    cout << "      DELETE SEASON CALIFICATION        \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string season_name = getSeasonName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool cali_exist = findSeasonCalificationBool(*cali_head, serie_name, season_name, user_email);

    if (cali_exist == true){
        deleteSeasonCalification(&*cali_head, season_name, user_email);
        writeSeasonCaliFile(*cali_head);
        cout << "AVISO: La calificacion ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

int calificationSeasonMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "       SEASON CALIFICATION MENU         \n";
        cout << "========================================\n";
        cout << "(1) Mostrar calificaciones\n";
        cout << "(2) Agregar calificacion\n";
        cout << "(3) Borrar calificacion\n";
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

void printSeasonCalificationInUser(SeasonCalification *cali_head, string email){

    cout << "========================================\n";
    cout << "     USER CALIFICATIONS IN SEASONS      \n";
    cout << "========================================\n";    

    if (countNumSeasonCalificationInUser(cali_head, email) > 0){

        SeasonCalification *aux = cali_head;
    
        while (aux){
            if (aux->user->email == email){
                cout << "Serie: " << aux->serie_name << endl;
                cout << "Temporada: " << aux->season_name << endl;
                cout << "Calificacion: " << aux->calification << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
            }
            aux = aux->next_calification;
        }
    }
    else{
        cout << "AVISO: El usuario aun no tiene calificaciones.\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void printSeasonCalificationInSeason(SeasonCalification *cali_head, string season_name){

    cout << "========================================\n";
    cout << "             CALIFICATIONS              \n";
    cout << "========================================\n";

    if (countNumSeasonCalificationInSeason(cali_head, season_name) > 0){

        SeasonCalification *aux = cali_head;
        
        while (aux){
            if (aux->season_name == season_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux -> calification << endl;
            }
            aux = aux->next_calification;
        }
    }
    else cout << "AVISO: Aun no hay calificaciones en la temporada\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showSeasonCalifications(SeasonCalification *cali_head){

    cout << "========================================\n";
    cout << "          SEASONS CALIFICATIONS          \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        SeasonCalification *aux = cali_head;

        while (aux){

            cout << "Temporada: " << aux->season_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Calificacion: " << aux->calification << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_calification;
        }
    }
}

void showSeasonCalificationsBySerie(SeasonCalification *cali_head, string serie_name){

    cout << "========================================\n";
    cout << "          SEASONS CALIFICATIONS         \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        SeasonCalification *aux = cali_head;
        int count = 0;

        while (aux){

            if (aux->serie_name == serie_name){

                cout << "Temporada: " << aux->season_name << endl;
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux->calification << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
                ++count;
            }

            aux = aux -> next_calification;

        }
        
        if (count == 0) cout << "AVISO. Las temporadas aun no tienen calificaciones!\n";

    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////