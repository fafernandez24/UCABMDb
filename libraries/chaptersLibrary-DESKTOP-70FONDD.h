// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "seasonsLibrary.h"

using namespace std;

bool findChapterByName(Chapter *chapter_head, string chapter_name){
  if (chapter_head){
    Chapter *aux = chapter_head;
    while (aux){
      if (aux->chapter_name == chapter_name) return true;
      aux = aux->next_chapter;
    }
  }
  return false;
}

bool findChapterBySerie(Serie *serie, string chapter_name){
  Season *season = serie->season_head;

  if (season){

    Chapter *aux = NULL;

    while (season){

      aux = season->chapters_head;

      while(aux){
        if (aux->chapter_name == chapter_name) return true;
        aux = aux->next_chapter;
      }

      season = season->next_season;
    }
  }
  return false;
}

bool findChapterByNum(Chapter *chapter_head, float chapter_num){
  if (chapter_head){
    Chapter *aux = chapter_head;
    while (aux){
      if (aux->chapter_num == chapter_num) return true;
      aux = aux->next_chapter;
    }
  }
  return false;
}

bool checkIntChapterId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

bool knowIfThereAreChapters(Serie *serie_head){
  if (serie_head){
    Serie *aux = serie_head;
    Season *aux2 = NULL;

    while (aux){
      aux2 = aux->season_head;
      while (aux2){
        if (aux2->chapters_head) return true;
        else aux2 = aux2->next_season;
      }
      aux = aux->next_serie;
    }
  }
  return false;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS SERIES */

/* Funcion para obtener el nombre de la serie */
string getChapterName(){

  string chapter_name;
  cin.ignore();
  cout << "\tNombre del capitulo: ";
  getline(cin, chapter_name);
  return chapter_name;
} 

/* Funcion para obtener el año de estreno de la serie */
int getChapterPremiere(){

  string chapter_premiere;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tEstreno: ";
    cin >> chapter_premiere;

    check_num = checkIntDataPremiere(chapter_premiere);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 1931 y 9999!\n";
    }
  }
  return stoi(chapter_premiere);
}

int getChapterTime(){

  string chapter_time;
  bool check_num = false;

  while (check_num == false){

    cout << "\tDuracion: ";
    cin >> chapter_time;

    check_num = checkIntDataTime(chapter_time);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 0 y 142!\n";
    }
  }
  return stoi(chapter_time);
}

float getChapterNum(){

  string chapter_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tNumero del capitulo: ";
    cin >> chapter_id;

    check_num = checkIntData(chapter_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 1 y 18000!\n";
    }
  }
  return stoi(chapter_id);
}

int getChapterId(){

  string chapter_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> chapter_id;

    check_num = checkIntSerieId(chapter_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(chapter_id);
}

Chapter *createChapter(string chapter_name, int chapter_premiere, int chapter_time, int chapter_num, int id){

    Chapter *new_chapter = new Chapter;

    new_chapter -> chapter_name = chapter_name;
    new_chapter -> chapter_premiere = chapter_premiere;
    new_chapter -> chapter_time = chapter_time;
    new_chapter -> chapter_num = chapter_num;
    new_chapter -> id = id;

    new_chapter -> next_chapter = NULL;

    return new_chapter;

}

Chapter *getChapterNodeByName(Chapter *chapter_head, string chapter_name){
  if (chapter_head){
    Chapter *aux = chapter_head;
    while (aux){
      if (aux -> chapter_name == chapter_name) return aux;
      aux = aux->next_chapter;
    }
  }
  return NULL;
}

Chapter *getChapterNodeById(Chapter *chapter_head, int id){

  if (chapter_head){

    Chapter *aux = chapter_head;

    while (aux){

      if (aux->id == id) return aux;
      aux = aux->next_chapter;

    }
  }
  return NULL;
}

Chapter *getChapterNodeBySerie(Serie *serie, string chapter_name){
  Season *season = serie->season_head;

  if (season){

    Chapter *aux = NULL;

    while (season){

      aux = season->chapters_head;

      while(aux){
        if (aux->chapter_name == chapter_name) return aux;
        aux = aux->next_chapter;
      }

      season = season->next_season;
    }
  }
  return NULL;
}

void addChapter(Chapter **chapter_head, string chapter_name, int chapter_premiere, int chapter_time, int chapter_num, int id){

    Chapter *new_chapter = createChapter(chapter_name, chapter_premiere, chapter_time, chapter_num, id);
    Chapter *aux = *chapter_head;

    if (aux){

        while (aux->next_chapter != NULL){
            aux = aux->next_chapter;
        }

        aux->next_chapter = new_chapter;

    }
    else{
        *chapter_head = new_chapter;
    }
}

void deleteChapter(Chapter **chapter_head, string chapter_name){

  Chapter *aux = *chapter_head;

  if (aux){

    if (aux->chapter_name == chapter_name){
      *chapter_head = aux->next_chapter;
      delete(aux);
    }
    else{

      Chapter *aux2 = NULL;

      while (aux->chapter_name != chapter_name){
          
          aux2 = aux;
          aux = aux->next_chapter;

      }

      if (aux->chapter_name == chapter_name){
          aux2->next_chapter = aux->next_chapter;
          delete(aux);
      }
      else{
          cout << "ERROR. No se encontro el capitulo a eliminar!\n";
      }
    }
  }
  else{
      cout << "ERROR. Lista de capitulos vacia!\n";
  }
}

void printChaptersList(Chapter *chapter_head){

  Chapter *aux = chapter_head;

  cout << "========================================\n";
  cout << "                 CAPITULOS\n";
  cout << "========================================\n";

  if (chapter_head){
    while (aux){

      cout << "              Capitulo #" << aux->chapter_num << "              \n";
      cout << "========================================\n";
      cout << "\tNombre del capitulo: " << aux->chapter_name << endl;
      cout << "\tEstreno: " << aux->chapter_premiere << endl;
      cout << "\tDuracion: " << aux->chapter_time << " min" << endl;
      cout << "\tID: " << aux -> id << endl;
      cout << "========================================\n";

      aux = aux->next_chapter;
    }
  }
  else{

    cout << "                Capitulo #0                \n";
    cout << "========================================\n";
    cout << "\tAun no hay capitulos...\n";
    cout << "========================================\n";
    cout << endl;

  }
}

void readChaptersFile(Serie *serie_head){

  ifstream file;
  string text, serie_name, season_name, chapter_name;
  int data_line = 0, chapter_premiere, chapter_time,chapter_id;
  float chapter_num;
  Serie *aux = serie_head;
  Season *aux2 = NULL;

  file.open("chaptersfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de CAPITULOS!\n";
  }

  getline(file, text);

  if (text == "CHAPTERS"){

    while(!file.eof()){

        getline(file,text);

        if (data_line == 1){

            if (findSerieByName(aux, text) == true){
                serie_name = text;
                aux = getSerieNodeByName(aux, serie_name);
                aux2 = aux->season_head;
            }
            else{
                cout << "\nERROR. Dato invalidos en el archivo!\n";
                cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
                file.close();
            }

        }

        if (data_line == 2){

            if (findSeasonByName(aux2, text) == true){
                season_name = text;
                aux2 = getSeasonNodeByName(aux->season_head, season_name);
            }
            else{
                cout << "\nERROR. Dato invalidos en el archivo!\n";
                cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
                file.close();
            }
        
        }

        if (data_line == 3) chapter_name = text;

        if (data_line == 4){
            
            if (checkIntData(text) == true) chapter_premiere = stoi(text);
            else{
              cout << "\nERROR. Dato invalidos en el archivo!\n";
              cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
              file.close();
            }
        }

        if (data_line == 5){
            
            if (checkIntData(text) == true) chapter_time = stoi(text);
            else{
                cout << "\nERROR. Dato invalidos en el archivo!\n";
                cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
                file.close();
            }
        }

        if (data_line == 6) chapter_num = stof(text);

        if (data_line == 7){

            if (checkIntChapterId(text) == true){
                chapter_id = stoi(text);
                addChapter(&aux2->chapters_head, chapter_name, chapter_premiere, chapter_time, chapter_num, chapter_id);
            }
            else{
                cout << "\nERROR. Dato invalidos en el archivo!\n";
                cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
                file.close();
            }
        }

        ++data_line;

        if (data_line == 8) data_line = 0;

        }

    }
    else{
        cout << "\nERROR. Dato invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de capitulos!\n\n";
    }

    file.close();
}

void writeChapterFile(Serie *serie_head){

  ofstream file;
  file.open("chaptersfile.txt", ios::out);

  if (file.fail()){
    cout << "ERROR. No se pudo abrir el archivo\n";
    exit(1);
  }
  else{

    Serie *serie = serie_head;

    if (knowIfThereAreChapters(serie) == false){
      file << "CHAPTERS";
    }
    else{

      file << "CHAPTERS\n\n";

      while(serie){

        Season *season = serie->season_head;

        while (season){

          Chapter *chapter = season->chapters_head;

          while (chapter){

            file << serie -> serie_name << endl;
            file << season -> season_name << endl;
            file << chapter -> chapter_name << endl;
            file << chapter -> chapter_premiere << endl;
            file << chapter -> chapter_time << endl;
            file << chapter -> chapter_num << endl;

            if ((knowIfThereAreChapters(serie -> next_serie) == false) && (chapter->next_chapter == NULL && season->next_season == NULL)) file << chapter -> id;
            else file << chapter -> id << endl << endl;
            chapter = chapter -> next_chapter;

          }

        season = season->next_season;

        }

      serie = serie->next_serie;

      }
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCIONES */

/* FUNCIONES PARA LOS MENUS*/

int chapterMenu(){

    string menu;

    cout << "========================================\n";
    cout << "(1) Ver capitulos\n";
    cout << "(2) Agregar capitulo\n";
    cout << "(3) Eliminar capitulo\n";
    cout << "(4) Buscar capitulo\n";
    cout << "(5) Calificaciones de los capitulos\n";
    cout << "(0) Regresar al menu de temporadas\n";
    cout << "========================================" << endl;
    cout << "Ingresar opcion: ";
    cin >> menu;
    cout << "========================================\n";
    
    if (menu >= "0"  && menu <= "5") return stoi(menu);

    cout << "========================================\n";
    cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
    cout << "Por favor ingresar una opcion correcta.\n";
    cout << "========================================\n";
    return -1;

}

/* PROCEDIMIENTO DE UN MENU PARA AGREGAR UNA SERIE */

void addChapterMenu(Chapter **chapter_head){

  cout << "========================================\n";
  cout << "                ADD CHAPTER              \n";
  cout << "========================================\n";
  string chapter_name = getChapterName();
  int chapter_premiere = getChapterPremiere();
  int chapter_time = getChapterTime();
  float chapter_num = getChapterNum();
  int chapter_id = getChapterId();
  cout << "========================================\n";

  bool chapter_exist = findChapterByName(*chapter_head, chapter_name);
  bool chapter_exist2 = findChapterByNum(*chapter_head, chapter_num);

  if (chapter_exist == false && chapter_exist2 == false){
    addChapter(&*chapter_head, chapter_name, chapter_premiere, chapter_time, chapter_num, chapter_id);
    cout << "AVISO: El capitulo se agrego correctamente!\n";
  }
  else cout << "AVISO: La serie ya se encuentra agregada!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA SERIE */

string searchChapter(){

  cout << "========================================\n";
  cout << "              SEARCH SERIE              \n";
  cout << "========================================\n";
  string chapter_name = getChapterName();
  cout << "========================================\n";

  return chapter_name;
}

void showChapter(Chapter *chapter_head){

  if (chapter_head){

    Chapter *aux = chapter_head;
    string chapter_name = searchChapter();

    bool bol = findChapterByName(chapter_head, chapter_name);

    if (bol == true){

      while (aux->chapter_name != chapter_name) aux = aux->next_chapter;

        cout << "========================================\n";
        cout << "     CAPITULO # " << aux->chapter_num << endl;;
        cout << "========================================\n";
        cout << "Nombre del capitulo: " << aux->chapter_name << endl;
        cout << "Estreno: " << aux->chapter_premiere << endl;
        cout << "Duracion: " << aux->chapter_time << " min" << endl;
        cout << "========================================\n";

    }
    else{
      cout << "AVISO: No se encontro el capitulo indicado!\n";
    }
  }
  else{
    cout << "Sin temporadas todavia...\n"; 
  }
}