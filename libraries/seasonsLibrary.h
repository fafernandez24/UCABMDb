// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "seriesLibrary.h"

using namespace std;

bool findSeasonByName(Season *season_head, string season_name){
  if (season_head){
    Season *aux = season_head;
    while (aux){
      if (aux->season_name == season_name) return true;
      aux = aux->next_season;
    }
  }
  return false;
}

bool checkIntSeasonId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

/* Funcion para obtener el nombre de la temporada */
string getSeasonName(){

  string season_name;
  cin.ignore();
  cout << "\tNombre de la temporada: ";
  getline(cin, season_name);
  return season_name;
} 

/* Funcion para obtener el año de estreno de la temporada */
int getSeasonPremiere(){

  string season_premiere;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tEstreno: ";
    cin >> season_premiere;

    check_num = checkIntDataPremiere(season_premiere);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 1931 y 9999!\n";
    }
  }
  return stoi(season_premiere);
}

int getSeasonId(){

  string season_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> season_id;

    check_num = checkIntSerieId(season_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(season_id);
}

Season *createSeason(string season_name, int season_premiere, int id){

    Season *new_season = new Season;

    new_season -> season_name = season_name;
    new_season -> season_premiere = season_premiere;
    new_season -> id = id;

    new_season -> chapters_head = NULL;
    new_season -> next_season = NULL;

    return new_season;
}

Season *getSeasonNodeByName(Season *season_head, string season_name){

  if (season_head){

    Season *aux = season_head;

    while (aux){
      if (aux->season_name == season_name) return aux;
      aux = aux->next_season;
    }

  }
  return NULL;
}

void addSeason(Season **season_head, string season_name, int season_premiere, int id){

    Season *new_season = createSeason(season_name, season_premiere, id);

    if (*season_head){

        Season *aux = *season_head;

        while (aux->next_season != NULL){
            aux = aux->next_season;
        }

        aux->next_season = new_season;

    }
    else{
        *season_head = new_season;
    }
}

void deleteSeason(Season **season_head, string season_name){

  if (*season_head){

    Season *aux = *season_head;

    if (aux -> season_name != season_name){
      Season *aux2 = NULL;

      while (aux -> season_name != season_name){
        aux2 = aux;
        aux = aux -> next_season;
      }
      aux2 -> next_season = aux -> next_season;
      delete(aux);
    }
    else{
      *season_head = aux -> next_season;
      delete(aux);
    }
  }
  else{
    cout << "ERROR. Lista de temporadas vacia\n";
  }
}

void readSeasonsFile(Serie *serie_head){

  ifstream file;
  string text, season_name;
  int data_line = 0, season_premiere, season_id;

  file.open("seasonsfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de TEMPORADAS!\n";
  }

  getline(file, text);

  if (text == "SEASONS"){

    while(!file.eof()){

      getline(file,text);

      if (data_line == 1) season_name = text;

      if (data_line == 2){
        
        if (checkIntData(text) == true){
          season_premiere = stoi(text);
        }
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de temporadas!\n\n";
          file.close();
        }
      }

      if (data_line == 3){

        if (checkIntSeasonId(text) == true){

          if (findSerieById(serie_head, stoi(text))){

          season_id = stoi(text);
          Serie *serie = getSerieNodeById(serie_head, season_id);

          addSeason(&serie->season_head, season_name, season_premiere, season_id);
          }
          else{
            cout << "\nERROR. Serie no encontrada!\n";
            cout << "AVISO: No se cargaron los datos del archivo de temporadas!\n\n";
            file.close();
          }
        }
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de temporadas!\n\n";
          file.close();
        }
      }

      ++data_line;

      if (data_line == 4) data_line = 0;

    }

  }
  else{
    cout << "\nERROR. Dato invalidos en el archivo!\n";
    cout << "AVISO: No se cargaron los datos del archivo de temporadas!\n\n";
  }

  file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN PELICULAS */

void addSeasonToFile(string season_name, int season_premiere, int season_id){

    ofstream file;

    file.open("seasonsfile.txt", ios::app);

    if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
    }

    file << endl;
    file << endl << season_name;
    file << endl << season_premiere;
    file << endl << season_id;

    file.close();
}

void writeSeasonsFile(Serie *serie_head){

  ofstream file;
  file.open("seasonsfile.txt", ios::out);

  if (file.fail()){
    cout << "ERROR. No se pudo abrir el archivo\n";
    exit(1);
  }
  else{

    Serie *aux = serie_head;

    file << "SEASONS\n\n";

    while(aux){

      Season *season = aux->season_head;
      int count = 0;

      while (season){

        file << season -> season_name << endl;
        file << season -> season_premiere << endl;

        if (aux -> next_serie == NULL && season->next_season == NULL) file << aux -> id;
        else file << season -> id << endl << endl;

        count += 1;

        season = season -> next_season;
      }

      aux = aux->next_serie;

    }
  }
}


int seasonMenu(){

  string menu;

  cout << "========================================\n";
  cout << "(1) Ver temporadas\n";
  cout << "(2) Agregar temporada\n";
  cout << "(3) Eliminar temporada\n";
  cout << "(4) Buscar temporada\n";
  cout << "(5) Calificaciones de las temporada\n";
  cout << "(0) Regresar al menu de series\n";
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

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA SERIE */

string searchSeason(){

  cout << "========================================\n";
  cout << "             SEARCH SEASON              \n";
  cout << "========================================\n";
  string season_name = getSeasonName();
  cout << "========================================\n";

  return season_name;
}

/* PROCEDIMIENTO DE UN MENU PARA AGREGAR UNA SERIE */

void addSeasonMenu(Season **season_head, int season_id){

  cout << "========================================\n";
  cout << "               ADD SEASON               \n";
  cout << "========================================\n";
  string season_name = getSeasonName();
  int season_premiere = getSeasonPremiere();
  cout << "========================================\n";

  bool season_Exist = findSeasonByName(*season_head, season_name);

  if (season_Exist == false){
    addSeason(&*season_head, season_name, season_premiere, season_id);
    addSeasonToFile(season_name, season_premiere, season_id);
    cout << "AVISO: La serie se agrego correctamente!\n";
  }
  else cout << "AVISO: La serie ya se encuentra agregada!\n";
}

void printSeasonsList(Serie *serie){

  Season *season_head = serie->season_head;

  cout << "========================================\n";
  cout << "              TEMPORADAS                \n";
  cout << "========================================\n";

  if (season_head){

    Season *aux = serie->season_head;

    while (aux){

      cout << "Nombre de temporada: " << aux->season_name << endl;
      cout << "Estreno: " << aux->season_premiere << endl;
      cout << "========================================\n";

      aux = aux->next_season;

    }

  }
  else{
    cout << "Sin temporadas todavia...\n";
    cout << "========================================\n";
  }

}

void showSeason(Season *season_head){

  if (season_head){

    Season *aux = season_head;
    string season_name = searchSeason();

    bool bol = findSeasonByName(season_head, season_name);

    if (bol == true){

      while (aux->season_name != season_name) aux = aux->next_season;

        cout << "========================================\n";
        cout << "     TEMPORADA " << aux->season_name << endl;;
        cout << "========================================\n";
        cout << "Estreno: " << aux->season_premiere << endl;
        cout << "========================================\n";

    }
  }
  else{
    cout << "Sin temporadas todavia...\n"; 
  }
}

void printSeason(Season *season_head, string season_name){

  if (season_head){

    Season *aux = season_head;

    bool bol = findSeasonByName(season_head, season_name);

    if (bol == true){

      while (aux->season_name != season_name) aux = aux->next_season;

        cout << "========================================\n";
        cout << "     TEMPORADA " << aux->season_name << endl;;
        cout << "========================================\n";
        cout << "Estreno: " << aux->season_premiere << endl;
        cout << "========================================\n";

    }
  }
  else{
    cout << "Sin temporadas todavia...\n"; 
  }
}