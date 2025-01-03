#include <iostream>
#include <fstream>
#include <string>
#include "calificationSeasonLibrary.h"

using namespace std;

bool checkIntChapterCalificationId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

bool checkFloatChapterCalification(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stof(word) >= 0 && stof(word) <= 9999999) return true;

    return false;
}

ChapterCalification *getChapterCalificationNode(ChapterCalification *cali_head,string serie_name, string chapter_name, string user_email){

    if (cali_head){
        ChapterCalification *aux = cali_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> chapter_name == chapter_name && aux -> user -> email == user_email))
                return aux;
            aux = aux -> next_calification;
        }
    }
    return NULL;
}

bool findChapterCalificationBool(ChapterCalification *cali_head,string serie_name, string chapter_name, string user_email){
    if (cali_head){
        ChapterCalification *aux = cali_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> chapter_name == chapter_name && aux -> user -> email == user_email)) return true;
            aux = aux -> next_calification;
        }
    }
    return false;
}

int getChapterCalificationId(){

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

ChapterCalification *createChapterCalification(string serie_name, float calification, int id, Chapter *chapter, Users *user){

    ChapterCalification *new_calification = new ChapterCalification;

    new_calification -> serie_name = serie_name;
    new_calification -> chapter_name = chapter->chapter_name;
    new_calification -> user_email = user->email;
    new_calification -> calification = calification;
    new_calification -> id = id;
    
    new_calification -> chapter = chapter;
    new_calification -> user = user;
    new_calification -> next_calification = NULL;

    return new_calification;
}

void addChapterCalification(ChapterCalification **cali_head, string serie_name, float calification, int id, Chapter *chapter, Users *user){

    ChapterCalification *new_calification = createChapterCalification(serie_name, calification, id, chapter, user);

    if (!*cali_head) *cali_head = new_calification;
    else{
        new_calification->next_calification = *cali_head;
        *cali_head = new_calification;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS CALIFICACIONES DE PELICULAS Y USUARIOS */

int countNumChapterCalificationInSerie(ChapterCalification *cali_head, string chapter_name){
    int count = 0;
    if (cali_head){
        ChapterCalification *aux = cali_head;
        while (aux){
            if (aux->chapter_name == chapter_name) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countNumChapterCalificationInUser(ChapterCalification *cali_head, string user_email){
    int count = 0;
    if (cali_head){
        ChapterCalification *aux = cali_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

int countUserChapterCali(ChapterCalification *cali_head, string email){
    int count = 0;
    if (cali_head){
        ChapterCalification *aux = cali_head;
        while (aux){
            if (aux->user->email == email) ++count;
            aux = aux->next_calification;
        }
    }
    return count;
}

void deleteChapterCalification(ChapterCalification **cali_head, string serie_name, string chapter_name, string user_email){

    if (*cali_head){

        ChapterCalification *aux = *cali_head;

        if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name && aux -> user_email == user_email){
            *cali_head = aux -> next_calification;
            delete(aux);
        }
        else{

            ChapterCalification *aux2 = NULL;

            while (aux){

                if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name && aux -> user_email == user_email){
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

void deleteChapterCali(ChapterCalification **cali_head, string serie_name, string chapter_name){

    if (*cali_head){
        
        ChapterCalification *aux = *cali_head;

        if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            ChapterCalification *aux2;

            while ((aux -> serie_name == serie_name && aux -> chapter_name == chapter_name) || (aux != NULL)){
                aux2 = aux;
                aux = aux->next_calification;
            }

            if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name){
                aux2->next_calification = aux->next_calification;
                delete(aux);
            }
        }
    }
    else
        cout << "AVISO: No se encontraron calificaciones en este capitulo!\n";
}

void deleteUserChapterCali(ChapterCalification **cali_head, string email){

    if (*cali_head){
        
        ChapterCalification *aux = *cali_head;

        if (aux->user_email == email){
            *cali_head = aux->next_calification;
            delete(aux);
        }
        else{

            ChapterCalification *aux2 = NULL;

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
        cout << "AVISO: No se encontraron calificaciones en este capitulo!\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA CALIFICACIONES */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA CALIFICACIONES */

void readChapterCaliFile(ChapterCalification **cali_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text;
  float calification;
  int data_line = 0, id;
  ChapterCalification *aux = *cali_head;
  Serie *serie = serie_head;
  Chapter *chapter = NULL;
  Users *user = NULL;

  file.open("calichapterfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de CALIFICACIONES EN CAPITULOS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "CHAPTER CALIFICATIONS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1){

                if (findSerieByName(serie_head, text) == true){
                    serie = getSerieNodeByName(serie_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en capitulos!\n\n";
                    file.close();
                }
            }

            if (data_line == 2){

                if (findChapterBySerie(serie, text) == true){
                    chapter = getChapterNodeBySerie(serie, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en capitulos!\n\n";
                    file.close();
                }
                
            }

            if (data_line == 3){
                
                if (findUsers(user_head, text) == true){
                    user = getUsersNode(user_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de calificaciones en capitulos!\n\n";
                    file.close();
                }

            }

            if (data_line == 4) calification = stof(text);

            if (data_line == 5){
                if (checkIntChapterCalificationId(text) == true){
                    id = stoi(text);
                    addChapterCalification(&aux, serie->serie_name, calification, id, chapter, user);
                }
            }

            ++data_line;

            if (data_line == 6) data_line = 0;

        }

        *cali_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de calificaciones en capitulos!\n\n";
    }

    file.close();
}

void addChaptersCaliToFile(string serie_name, string chapter_name, string user_email, float calification, int id){

  ofstream file;

  file.open("calichapterfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << chapter_name;
  file << endl << user_email;
  file << endl << calification;
  file << endl << id;

  file.close();
}

void writeChapterCaliFile(ChapterCalification *cali_head){

    if (cali_head){

        ofstream file;
        file.open("calichapterfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        ChapterCalification *aux = cali_head;

        file << "CHAPTER CALIFICATIONS\n\n";

        while(aux){

            file << aux -> serie_name << endl;
            file << aux -> chapter_name << endl;
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
        file.open("calichapterfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "CHAPTER CALIFICATIONS\n\n";
        }
    }
}

void editChapterCalification(ChapterCalification *cali_head, float calification, string serie_name, string chapter_name, string user_email){

    if (findChapterCalificationBool(cali_head, serie_name, chapter_name, user_email) == true){

        ChapterCalification *new_cali = getChapterCalificationNode(cali_head, serie_name, chapter_name, user_email);
        new_cali -> calification = calification;
        cout << "AVISO: Calificacion EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

void addChapterCalificationMenu(ChapterCalification **cali_head, Chapter *chapter_head, Users *user_head, string serie_name){

    cout << "========================================\n";
    cout << "    ADD OR EDIT CHAPTER CALIFICATION    \n";
    cout << "========================================\n";
    string chapter_name = getChapterName();
    float calification = getCalification();
    string user_email = getUsersEmail();
    int id = getSerieCalificationId();
    cout << "========================================\n";

    bool serie_exist = findChapterByName(chapter_head, serie_name);
    bool user_exist = findUsers(user_head, user_email);

    if ( serie_exist == true && user_exist == true){

        bool cali_exist = findChapterCalificationBool(*cali_head, serie_name, chapter_name, user_email);

        if ( cali_exist == false){

            Chapter *chapter = getChapterNodeByName(chapter_head, chapter_name);
            Users *user = getUsersNode(user_head, user_email);
            addChapterCalification(&*cali_head, serie_name, calification, id, chapter, user);

            cout << "AVISO: Calificacion AGREGADA con exito\n";

        }
        else editChapterCalification(*cali_head, calification, serie_name, chapter_name, user_email);
        
        //writeSerieCaliFile(*cali_head);

    }
    else 
        cout << "ERROR. La serie o el usuario ingresados no han sido encontrados!\n";
}

void deleteChapterCalificationMenu(ChapterCalification **cali_head){

    cout << "========================================\n";
    cout << "       DELETE SERIE CALIFICATION        \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string chapter_name = getChapterName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool cali_exist = findChapterCalificationBool(*cali_head, serie_name, chapter_name, user_email);

    if (cali_exist == true){
        deleteChapterCalification(&*cali_head, serie_name, chapter_name, user_email);
        // writeSerieCaliFile(*cali_head);
        cout << "AVISO: La calificacion ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La calificacion ingresada no ha sido encontrada!\n";
}

int calificationChapterMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "       CHAPTER CALIFICATION MENU        \n";
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

void printChapterCalificationInUser(ChapterCalification *cali_head, string email){

    cout << "========================================\n";
    cout << "      USER CALIFICATIONS IN SERIES      \n";
    cout << "========================================\n";    

    if (countNumChapterCalificationInUser(cali_head, email) > 0){

        ChapterCalification *aux = cali_head;
    
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

void printChapterCalificationInChapter(ChapterCalification *cali_head, string chapter_name){

    cout << "========================================\n";
    cout << "             CALIFICATIONS              \n";
    cout << "========================================\n";

    if (countNumChapterCalificationInSerie(cali_head, chapter_name) > 0){

        ChapterCalification *aux = cali_head;
        
        while (aux){
            if (aux->chapter_name == chapter_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux -> calification << endl;
            }
            aux = aux->next_calification;
        }
    }
    else cout << "AVISO: Aun no hay calificaciones en el capitulo\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showChapterCalifications(ChapterCalification *cali_head){

    cout << "========================================\n";
    cout << "         CHAPTER CALIFICATIONS          \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        ChapterCalification *aux = cali_head;

        while (aux){

            cout << "Capitulo: " << aux->chapter_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Calificacion: " << aux->calification << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_calification;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showChapterCalificationsBySerie(ChapterCalification *cali_head, string serie_name){

    cout << "========================================\n";
    cout << "  CHAPTERS CALIFICATIONS OF THIS SERIE  \n";
    cout << "========================================\n";

    if (!cali_head)
        cout << "ERROR. Lista de calificaciones vacia!\n";
    else{

        ChapterCalification *aux = cali_head;
        int count = 0;

        while (aux){

            if (aux->serie_name == serie_name){

                cout << "Capitulo: " << aux->chapter_name << endl;
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Calificacion: " << aux->calification << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
                ++count;
            }

            aux = aux -> next_calification;

        }
        
        if (count == 0) cout << "AVISO. Los capitulos aun no tienen calificaciones!\n";

    }
}