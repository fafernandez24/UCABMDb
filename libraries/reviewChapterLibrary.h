// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "reviewSeasonLibrary.h"

using namespace std;

bool checkIntChapterReviewId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

/* Funcion para obtener una reseña */
string getChapterReview(){

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

ChapterReview *getChapterReviewNode(ChapterReview *review_head, string serie_name, string chapter_name, string user_email){

    if (review_head){
        ChapterReview *aux = review_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> chapter_name == chapter_name && aux -> user -> email == user_email))
                return aux;
            aux = aux -> next_review;
        }
    }
    return NULL;
}

bool findChapterReviewBool(ChapterReview *review_head,string serie_name, string chapter_name, string user_email){
    if (review_head){
        ChapterReview *aux = review_head;
        while (aux){
            if ((aux -> serie_name == serie_name) && (aux -> chapter_name == chapter_name && aux -> user -> email == user_email)) return true;
            aux = aux -> next_review;
        }
    }
    return false;
}

int getChapterReviewId(){

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

ChapterReview *createChapterReview(string serie_name, string review, int id, Chapter *chapter, Users *user){

    ChapterReview *new_review = new ChapterReview;

    new_review -> serie_name = serie_name;
    new_review -> chapter_name = chapter->chapter_name;
    new_review -> user_email = user->email;
    new_review -> review = review;
    new_review -> id = id;
    
    new_review -> chapter = chapter;
    new_review -> user = user;
    new_review -> next_review = NULL;

    return new_review;
}

void addChapterCalification(ChapterReview **review_head, string serie_name, string review, int id, Chapter *chapter, Users *user){

    ChapterReview *new_review = createChapterReview(serie_name, review, id, chapter, user);

    if (!*review_head) *review_head = new_review;
    else{
        new_review->next_review = *review_head;
        *review_head = new_review;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS Y PROCEDIMIENTOS PARA BORRAR LAS reviews DE PELICULAS Y USUARIOS */

int countNumChapterReviewInSerie(ChapterReview *review_head, string serie_name){
    int count = 0;
    if (review_head){
        ChapterReview *aux = review_head;
        while (aux){
            if (aux->serie_name == serie_name) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

int countNumChapterReviewInChapter(ChapterReview *review_head, string chapter_name){
    int count = 0;
    if (review_head){
        ChapterReview *aux = review_head;
        while (aux){
            if (aux->chapter_name == chapter_name) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

int countNumChapterReviewInUser(ChapterReview *review_head, string user_email){
    int count = 0;
    if (review_head){
        ChapterReview *aux = review_head;
        while (aux){
            if (aux->user_email == user_email) ++count;
            aux = aux->next_review;
        }
    }
    return count;
}

void deleteChapterReview(ChapterReview **review_head, string serie_name, string chapter_name, string user_email){

    if (*review_head){

        ChapterReview *aux = *review_head;

        if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name && aux -> user_email == user_email){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            ChapterReview *aux2 = NULL;

            while (aux){

                if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name && aux -> user_email == user_email){
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

void deleteChapterRev(ChapterReview **review_head, string serie_name, string chapter_name){

    if (*review_head){
        
        ChapterReview *aux = *review_head;

        if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name){
            *review_head = aux -> next_review;
            delete(aux);
        }
        else{

            ChapterReview *aux2 = NULL;

            while (aux){

                if (aux -> serie_name == serie_name && aux -> chapter_name == chapter_name){
                    aux2 -> next_review = aux -> next_review;
                    delete(aux);
                }

                aux2 = aux;
                aux = aux -> next_review;

            }
        }
    }
    else
        cout << "AVISO: No se encontraron reviews en este capitulo!\n";
}

void deleteChapterRevBySerie(ChapterReview **review_head, string serie_name){

    if (*review_head){

        ChapterReview *aux = *review_head;

        if (aux->serie_name == serie_name){
            *review_head = aux->next_review;
            delete(aux);
        }
        else{

            ChapterReview *aux2 = NULL;

            while (aux->serie_name != serie_name){
                aux2 = aux;
                aux = aux->next_review;
            }

            aux2->next_review = aux->next_review;
            delete(aux);
        }

    }
    else{
        cout << "AVISO: No se encontraron reviews en este capitulo!\n";
    }

}

void deleteChapterRevByUser(ChapterReview **review_head, string email){

    if (*review_head){
        
        ChapterReview *aux = *review_head;

        if (aux->user_email == email){
            *review_head = aux->next_review;
            delete(aux);
        }
        else{

            ChapterReview *aux2 = NULL;

            while (aux->user_email != email){
                aux2 = aux;
                aux = aux->next_review;
            }

            aux2->next_review = aux->next_review;
            delete(aux);

        }
    }
    else{
        cout << "AVISO: No se encontraron reviews en este capitulo!\n";
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA reviews */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA reviews */

void readChapterReviewFile(ChapterReview **review_head, Serie *serie_head, Users *user_head){

  ifstream file;
  string text;
  string review;
  int data_line = 0, id;
  ChapterReview *aux = *review_head;
  Serie *serie = serie_head;
  Chapter *chapter = NULL;
  Users *user = NULL;

  file.open("revchapterfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de reviews EN CAPITULOS!\n";
      exit(1);
  }

  getline(file, text);

    if (text == "CHAPTER REVIEWS"){

        while(!file.eof()){

            getline(file,text);

            if (data_line == 1){

                if (findSerieByName(serie_head, text) == true){
                    serie = getSerieNodeByName(serie_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en capitulos!\n\n";
                    file.close();
                }
            }

            if (data_line == 2){

                if (findChapterBySerie(serie, text) == true){
                    chapter = getChapterNodeBySerie(serie, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en capitulos!\n\n";
                    file.close();
                }
                
            }

            if (data_line == 3){
                
                if (findUsers(user_head, text) == true){
                    user = getUsersNode(user_head, text);
                }
                else{
                    cout << "\nERROR. Dato invalidos en el archivo!\n";
                    cout << "AVISO: No se cargaron los datos del archivo de reviews en capitulos!\n\n";
                    file.close();
                }

            }

            if (data_line == 4) review = text;

            if (data_line == 5){
                if (checkIntChapterReviewId(text) == true){
                    id = stoi(text);
                    addChapterCalification(&aux, serie->serie_name, review, id, chapter, user);
                }
            }

            ++data_line;

            if (data_line == 6) data_line = 0;

        }

        *review_head = aux;

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de reviews en capitulos!\n\n";
    }

    file.close();
}

void addChaptersReviewToFile(string serie_name, string chapter_name, string user_email, string review, int id){

  ofstream file;

  file.open("revchapterfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << serie_name;
  file << endl << chapter_name;
  file << endl << user_email;
  file << endl << review;
  file << endl << id;

  file.close();
}

void writeChapterReviewFile(ChapterReview *review_head){

    if (review_head){

        ofstream file;
        file.open("revchapterfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{

        ChapterReview *aux = review_head;

        file << "CHAPTER REVIEWS\n\n";

        while(aux){

            file << aux -> serie_name << endl;
            file << aux -> chapter_name << endl;
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
        file.open("revchapterfile.txt", ios::out);

        if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
        }
        else{
        file << "CHAPTER REVIEWS";
        }
    }
}

void editChapterReview(ChapterReview *review_head, string review, string serie_name, string chapter_name, string user_email){

    if (findChapterReviewBool(review_head, serie_name, chapter_name, user_email) == true){

        ChapterReview *new_cali = getChapterReviewNode(review_head, serie_name, chapter_name, user_email);
        new_cali -> review = review;
        cout << "AVISO: Review EDITADA con exito!\n";
    }
    else 
        cout << "ERROR. La Review ingresada no ha sido encontrada!\n";
}

void addChapterReviewMenu(ChapterReview **review_head, Chapter *chapter_head, Users *user_head, string serie_name){

    cout << "========================================\n";
    cout << "      ADD OR EDIT CHAPTER REVIEW        \n";
    cout << "========================================\n";
    string chapter_name = getChapterName();
    string review = getChapterReview();
    string user_email = getUsersEmail();
    int id = getSerieCalificationId();
    cout << "========================================\n";

    bool chapter_exist = findChapterByName(chapter_head, chapter_name);
    bool user_exist = findUsers(user_head, user_email);

    if (chapter_exist == true && user_exist == true){

        bool review_exist = findChapterReviewBool(*review_head, serie_name, chapter_name, user_email);

        if ( review_exist == false){

            Chapter *chapter = getChapterNodeByName(chapter_head, chapter_name);
            Users *user = getUsersNode(user_head, user_email);
            addChapterCalification(&*review_head, serie_name, review, id, chapter, user);

            cout << "AVISO: Review AGREGADA con exito\n";

        }
        else editChapterReview(*review_head, review, serie_name, chapter_name, user_email);
        writeChapterReviewFile(*review_head);

    }
    else{
        cout << "ERROR. El capitulo o el usuario ingresados no han sido encontrados!\n";
    }
}

void deleteChapterReviewMenu(ChapterReview **review_head){

    cout << "========================================\n";
    cout << "         DELETE CHAPTER REVIEW          \n";
    cout << "========================================\n";
    string serie_name = getSerieName();
    string chapter_name = getChapterName();
    string user_email = getUsersEmail();
    cout << "========================================\n";

    bool review_exist = findChapterReviewBool(*review_head, serie_name, chapter_name, user_email);

    if (review_exist == true){
        deleteChapterReview(&*review_head, serie_name, chapter_name, user_email);
        // writeSerieCaliFile(*review_head);
        cout << "AVISO: La Review ha sido borrada con exito!\n";
    }
    else 
        cout << "ERROR. La Review ingresada no ha sido encontrada!\n";
}

int reviewChapterMenu(){

    string menu = " ";

    do{
        cout << "========================================\n";
        cout << "           CHAPTER REVIEW MENU          \n";
        cout << "========================================\n";
        cout << "(1) Mostrar reviews\n";
        cout << "(2) Agregar review\n";
        cout << "(3) Borrar review\n";
        cout << "(0) Volver a capitulos\n";
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

void printChapterReviewInUser(ChapterReview *review_head, string email){

    cout << "========================================\n";
    cout << "        USER REVIEWS IN CHAPTERS        \n";
    cout << "========================================\n";    

    if (countNumChapterReviewInUser(review_head, email) > 0){

        ChapterReview *aux = review_head;
    
        while (aux){
            if (aux->user->email == email){
                cout << "Serie: " << aux->serie_name << endl;
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

void printChapterReviewInChapter(ChapterReview *review_head, string chapter_name){

    cout << "========================================\n";
    cout << "                   REVIEWS              \n";
    cout << "========================================\n";

    if (countNumChapterReviewInSerie(review_head, chapter_name) > 0){

        ChapterReview *aux = review_head;
        
        while (aux){
            if (aux->chapter_name == chapter_name){
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux -> review << endl;
            }
            aux = aux->next_review;
        }
    }
    else cout << "AVISO: Aun no hay reviews en el capitulo\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showChapterReview(ChapterReview *review_head){

    cout << "========================================\n";
    cout << "             CHAPTER REVIEWS            \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        ChapterReview *aux = review_head;

        while (aux){

            cout << "Capitulo: " << aux->chapter_name << endl;
            cout << "Usuario: " << aux -> user -> email << endl;
            cout << "Review: " << aux->review << endl;
            cout << "ID: " << aux->id << endl;
            cout << "========================================\n";

            aux = aux -> next_review;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void showChapterReviewBySerie(ChapterReview *review_head, string serie_name){

    cout << "========================================\n";
    cout << "     CHAPTERS REVIEWS OF THIS SERIE     \n";
    cout << "========================================\n";

    if (!review_head)
        cout << "ERROR. Lista de reviews vacia!\n";
    else{

        ChapterReview *aux = review_head;
        int count = 0;

        while (aux){

            if (aux->serie_name == serie_name){

                cout << "Capitulo: " << aux->chapter_name << endl;
                cout << "Usuario: " << aux -> user -> email << endl;
                cout << "Review: " << aux->review << endl;
                cout << "ID: " << aux->id << endl;
                cout << "========================================\n";
                ++count;
            }

            aux = aux -> next_review;

        }
        
        if (count == 0) cout << "AVISO. Los capitulos aun no tienen reviews!\n";

    }
}
