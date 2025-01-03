#include <iostream>
#include <fstream>
#include <string>
#include "chaptersLibrary.h"

using namespace std;

bool checkIntSerieCalificationId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

bool checkFloatSerieCalification(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stof(word) >= 0 && stof(word) <= 9999999) return true;

    return false;
}

SerieCalification *getSerieCalificationNode(SerieCalification *cali_head, string serie_name, string user_email){

    if (cali_head){
        SerieCalification *aux = cali_head;
        while (aux){
            if (aux -> serie_name == serie_name && aux -> user -> email == user_email)
                return aux;
            aux = aux -> next_calification;
        }
    }
    return NULL;
}

bool findSerieCalificationBool(SerieCalification *cali_head, string serie_name , string user_email){
    if (cali_head){
        SerieCalification *aux = cali_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> user -> email == user_email)) return true;
            aux = aux -> next_calification;
        }
    }
    return false;
}

int getSerieCalificationId(){

  string cali_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> cali_id;

    check_num = checkIntSerieCalificationId(cali_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(cali_id);
}

SerieCalification *createSerieCalification(float calification, int id, Serie *serie, Users *user){

    SerieCalification *new_calification = new SerieCalification;

    new_calification -> serie_name = serie->serie_name;
    new_calification -> user_email = user->email;
    new_calification -> calification = calification;
    new_calification -> id = id;
    
    new_calification -> serie = serie;
    new_calification -> user = user;
    new_calification -> next_calification = NULL;

    return new_calification;
}

void addSerieCalification(SerieCalification **cali_head, float calification, int id, Serie *serie, Users *user){

    SerieCalification *new_calification = createSerieCalification(calification, id, serie, user);

    if (!*cali_head) *cali_head = new_calification;
    else{
        new_calification->next_calification = *cali_head;
        *cali_head = new_calification;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS CALIFICACIONES DE PELICULAS Y USUARIOS */

int countNumSerieCalificationInSerie(SerieCalification *cali_head, string serie_name){
    int count = 0;
    if (cali_head){
        SerieCalification *aux = cali_head;
        while (aux){
            if (aux->serie_name == serie_name) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countNumSerieCalificationInUser(SerieCalification *cali_head, string user_email){
    int count = 0;
    if (cali_head){
        SerieCalification *aux = cali_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countUserSerieCali(SerieCalification *cali_head, string email){
    int count = 0;
    if (cali_head){
        SerieCalification *aux = cali_head;
        while (aux){
            if (aux->user->email == email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

void deleteSerieCalification(SerieCalification **cali_head, string serie_name, string user_email){

    if (*cali_head){

        SerieCalification *aux = *cali_head;

        if (aux -> serie_name == serie_name && aux -> user_email == user_email){
            *cali_head = aux -> next_calification;
            delete(aux);
        }
        else{

            SerieCalification *aux2 = NULL;

            while (aux){

                if (aux -> serie_name == serie_name && aux -> user_email == user_email){
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

void deleteSerieCali(SerieCalification **cali_head, string serie_name){

    if (*cali_head){
        
        SerieCalification *aux = *cali_head;

        if (aux->serie_name == serie_name){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            SerieCalification *aux2;

            while (aux->serie_name != serie_name || aux != NULL){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux->serie_name == serie_name){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else
        cout << "AVISO: No se encontraron calificaciones en esta serie!\n";
}

void deleteUserSerieCali(SerieCalification **cali_head, string email){

    if (*cali_head){
        
        SerieCalification *aux = *cali_head;

        if (aux->user_email == email){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            SerieCalification *aux2 = NULL;

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
        cout << "AVISO: No se encontraron calificaciones en esta serie!\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA CALIFICACIONES */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA CALIFICACIONES */

void readSerieCaliFile(SerieCalification **cali_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text, serie_name, user_email;
  float calification;
  int data_line = 0, id;
  SerieCalification *aux = *cali_head;
  Serie *serie = NULL;
  Users *user = NULL;

  file.open("caliseriefile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de CALIFICACIONES EN SERIES!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "SERIES CALIFICATIONS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1) serie = getSerieNodeByName(serie_head, text);

            if (data_line == 2) user = getUsersNode(user_head, text);

            if (data_line == 3) calification = stof(text);

            if (data_line == 4){
                if (checkIntSerieCalificationId(text) == true){
                    id = stoi(text);
                    addSerieCalification(&aux, calification, id, serie, user);
                }
            }

            ++data_line;

            if (data_line == 5) data_line = 0;

        }

        *cali_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de calificaciones en series!\n\n";
    }

    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN CALIFICACIONES */

void addSerieCaliToFile(string serie_name, string user_email, float calification, int id){

  ofstream file;

  file.open("caliseriefile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << user_email;
  file << endl << calification;
  file << endl << id;

  file.close();
}

void writeSerieCaliFile(SerieCalification *cali_head){

    if (cali_head){

        ofstream file;
        file.open("caliseriefile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        SerieCalification *aux = cali_head;

        file << "SERIES CALIFICATIONS\n\n";

        while(aux){


            file << aux -> serie_name << endl;
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
        file.open("caliseriefile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "SERIE CALIFICATIONS\n\n";
        }
    }
}

void editSerieCalification(SerieCalification *cali_head, float calification, string serie_name, string user_email){

    if (findSerieCalificationBool(cali_head, serie_name, user_email) == true){

        SerieCalification *new_cali = getSerieCalificationNode(cali_head, serie_name, user_email);
        new_cali -> calification = calification;
        cout << "AVISO: Calificacion EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

void addSerieCalificationMenu(SerieCalification **cali_head, Serie *serie_head, Users *user_head){

    cout << "========================================\n";
    cout << "     ADD OR EDIT SERIE CALIFICATION     \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    float calification = getCalification();
    string user_email = getUsersEmail();
    int id = getSerieCalificationId();
    cout << "========================================\n";

    bool serie_exist = findSerieByName(serie_head, serie_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( serie_exist == true && user_exist == true){

        bool cali_exist = findSerieCalificationBool(*cali_head, serie_name, user_email);

        if ( cali_exist == false){

            Serie *serie = getSerieNodeByName(serie_head, serie_name);
            Users *user = getUsersNode(user_head, user_email);
            addSerieCalification(&*cali_head, calification, id, serie, user);

            cout << "AVISO: Calificacion AGREGADA con exito\n";

        }
        else editSerieCalification(*cali_head, calification, serie_name, user_email);
        
        writeSerieCaliFile(*cali_head);

    }
    else 
        cout << "ERROR. La serie o el usuario ingresados no han sido encontrados!\n";
}

void deleteSerieCalificationMenu(SerieCalification **cali_head){

    cout << "========================================\n";
    cout << "       DELETE SERIE CALIFICATION        \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool cali_exist = findSerieCalificationBool(*cali_head, serie_name, user_email);

    if (cali_exist == true){
        deleteSerieCalification(&*cali_head, serie_name, user_email);
        writeSerieCaliFile(*cali_head);
        cout << "AVISO: La calificacion ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

int calificationSerieMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "        SERIE CALIFICATION MENU         \n";
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

void printSerieCalificationInUser(SerieCalification *cali_head, string email){

    cout << "========================================\n";
    cout << "      USER CALIFICATIONS IN SERIES      \n";
    cout << "========================================\n";    

    if (countNumSerieCalificationInUser(cali_head, email) > 0){

        SerieCalification *aux = cali_head;
    
        while (aux){
            if (aux->user->email == email){
                cout << "Serie: " << aux->serie_name << endl;
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

void printSerieCalificationInSerie(SerieCalification *cali_head, string serie_name){

    cout << "========================================\n";
    cout << "             CALIFICATIONS              \n";
    cout << "========================================\n";

    if (countNumSerieCalificationInSerie(cali_head, serie_name) > 0){

        SerieCalification *aux = cali_head;
        
        while (aux){
            if (aux->serie_name == serie_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux -> calification << endl;
            }
            aux = aux->next_calification;
        }
    }
    else cout << "AVISO: Aun no hay calificaciones en la serie\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showSerieCalifications(SerieCalification *cali_head){

    cout << "========================================\n";
    cout << "          SERIES CALIFICATIONS          \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        SerieCalification *aux = cali_head;

        while (aux){

            cout << "Serie: " << aux->serie_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Calificacion: " << aux->calification << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_calification;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////