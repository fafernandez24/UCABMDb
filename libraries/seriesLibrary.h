// @author Freddy Fernández

#include <iostream>
#include <fstream>
#include <string>
#include "reviewMovieLibrary.h"

using namespace std;

bool findSerieByName(Serie *serie_head, string serie_name){
  if (serie_head){
    Serie *aux = serie_head;
    while (aux){
      if (aux->serie_name == serie_name) return true;
      aux = aux->next_serie;
    }
  }
  return false;
}

bool checkIntSerieId(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 9999999) return true;

    return false;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS SERIES */

/* Funcion para obtener el nombre de la serie */
string getSerieName(){

  string serie_name;
  cin.ignore();
  cout << "\tNombre de la serie: ";
  getline(cin, serie_name);
  return serie_name;
} 

/* Funcion para obtener el año de estreno de la serie */
int getSeriePremiere(){

  string serie_premiere;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tEstreno: ";
    cin >> serie_premiere;

    check_num = checkIntDataPremiere(serie_premiere);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 1931 y 9999!\n";
    }
  }
  return stoi(serie_premiere);
}

/* Funcion para obtener el genero de la serie */
string getSerieType(){

  string serie_type;
  cin.ignore();
  cout << "\tGenero: ";
  getline(cin, serie_type);
  return serie_type;
}

int getSerieId(){

  string serie_id;
  bool check_num = false;
  
  while (check_num == false){
    cout << "\tID: ";
    cin >> serie_id;

    check_num = checkIntSerieId(serie_id);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 10000 y 99999!\n";
    }
  }
  return stoi(serie_id);
}

Serie *createSerie(string serie_name, int serie_premiere, string type, int id){

    Serie *new_serie = new Serie;

    new_serie -> serie_name = serie_name;
    new_serie -> serie_premiere = serie_premiere;
    new_serie -> type = type;
    new_serie -> id = id;

    new_serie -> season_head = NULL;
    new_serie -> next_serie = NULL;

    return new_serie;

}

Serie *getSerieNodeByName(Serie *serie_head, string serie_name){
  if (serie_head){
    Serie *aux = serie_head;
    while (aux){
      if (aux -> serie_name == serie_name) return aux;
      aux = aux->next_serie;
    }
  }
  return NULL;
}

Serie *getSerieNodeById(Serie *serie_head, int id){

  if (serie_head){

    Serie *aux = serie_head;

    while (aux){

      if (aux->id == id) return aux;
      aux = aux->next_serie;

    }
  }
  return NULL;
}

void addSerie(Serie **serie_head, string serie_name, int serie_premiere, string type, int id){

    Serie *new_serie = createSerie(serie_name, serie_premiere, type, id);

    if (*serie_head){

        Serie *aux = *serie_head;

        while (aux->next_serie != NULL){
            aux = aux->next_serie;
        }

        aux->next_serie = new_serie;

    }
    else{
        *serie_head = new_serie;
    }
}

void deleteSerie(Serie **serie_head, string serie_name){

    if (*serie_head){

      Serie *aux = *serie_head, *aux2 = NULL;

      if (aux->serie_name == serie_name){
        *serie_head = aux->next_serie;
        delete(aux);
      }

      while (aux->serie_name != serie_name){
          aux2 = aux;
          aux = aux->next_serie;
      }

        aux2->next_serie = aux->next_serie;
        delete(aux);

    }
    else{
        cout << "ERROR. Lista de series vacia!\n";
    }
}

void printSerieList(Serie *serie_head){

  Serie *aux = serie_head;
  int serie_num = 1;

  cout << "========================================\n";
  cout << "                 SERIES\n";
  cout << "========================================\n";

  if (serie_head){
    while (aux){

      cout << "              Serie #" << serie_num << "              \n";
      cout << "========================================\n";
      cout << "\tSerie name: " << aux->serie_name << endl;
      cout << "\tSerie premiere: " << aux->serie_premiere << endl;
      cout << "\tSerie type: " << aux->type << endl;
      cout << "\tSerie ID: " << aux -> id << endl;
      cout << "========================================\n";

      aux = aux->next_serie;
      ++serie_num;
    }
  }
  else{

    cout << "                Serie #0                \n";
    cout << "========================================\n";
    cout << "\tAun no hay series...\n";
    cout << "========================================\n";
    cout << endl;

  }
}

void readSeriesFile(Serie **serie_head){

  ifstream file;
  string text, serie_name, serie_type;
  int data_line = 0, serie_premiere, serie_id;
  Serie *aux = *serie_head;

  file.open("seriesfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de SERIES!\n";
  }

  getline(file, text);

  if (text == "SERIES"){

    while(!file.eof()){

      getline(file,text);

      if (data_line == 1) serie_name = text;

      if (data_line == 2){
        
        if (checkIntData(text) == true) serie_premiere = stoi(text);
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de series!\n\n";
          file.close();
        }
      }

      if (data_line == 3) serie_type = text;

      if (data_line == 4){

        if (checkIntSerieId(text) == true){
          serie_id = stoi(text);
          addSerie(&aux, serie_name, serie_premiere, serie_type, serie_id);
        }
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de Series!\n\n";
          file.close();
        }
      }

      ++data_line;

      if (data_line == 5) data_line = 0;

    }

  *serie_head = aux;

  }
  else{
    cout << "\nERROR. Dato invalidos en el archivo!\n";
    cout << "AVISO: No se cargaron los datos del archivo de series!\n\n";
  }

  file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN PELICULAS */

void addSerieToFile(string serie_name, int serie_premiere, string serie_type, int serie_id){

    ofstream file;

    file.open("seriesfile.txt", ios::app);

    if (file.fail()){
        cout << "ERROR. No se pudo abrir el archivo\n";
        exit(1);
    }

    file << endl;
    file << endl << serie_name;
    file << endl << serie_premiere;
    file << endl << serie_type;
    file << endl << serie_id;

    file.close();
}

void writeSerieFile(Serie *serie_head){

  if (serie_head){

    ofstream file;
    file.open("seriesfile.txt", ios::out);

    if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo\n";
      exit(1);
    }
    else{

      Serie *aux = serie_head;

      file << "SERIES\n\n";

      while(aux){


        file << aux -> serie_name << endl;
        file << aux -> serie_premiere << endl;
        file << aux -> type << endl;

        if (aux -> next_serie == NULL) file << aux -> id;
        else file << aux -> id << endl << endl;

        aux = aux -> next_serie;
      }
    }
  }
  else cout << "ERROR. Lista de series vacia!";
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCIONES */

/* FUNCIONES PARA LOS MENUS*/

int serieMenu(){

  string menu;

  cout << "========================================\n";
  cout << "               SERIE MENU               \n";
  cout << "========================================\n";
  cout << "(1) Ver series\n";
  cout << "(2) Agregar serie\n";
  cout << "(3) Eliminar serie\n";
  cout << "(4) Buscar serie\n";
  cout << "(5) Calificaciones\n";
  cout << "(6) Reviews\n";
  cout << "(0) Regresar al menu principal\n";
  cout << "========================================" << endl;
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";
  
  if (menu >= "0"  && menu <= "6") return stoi(menu);

  cout << "========================================\n";
  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  cout << "========================================\n";
  return -1;

}

/* PROCEDIMIENTO DE UN MENU PARA AGREGAR UNA SERIE */

void addSerieMenu(Serie **serie_head){

  cout << "========================================\n";
  cout << "                ADD SERIE               \n";
  cout << "========================================\n";
  string serie_name = getSerieName();
  int serie_premiere = getSeriePremiere();
  string serie_type = getSerieType();
  int serie_id = getSerieId();
  cout << "========================================\n";

  bool serie_exist = findSerieByName(*serie_head, serie_name);

  if (serie_exist == false){
    addSerie(&*serie_head, serie_name, serie_premiere, serie_type, serie_id);
    addSerieToFile(serie_name, serie_premiere, serie_type, serie_id);
    cout << "AVISO: La serie se agrego correctamente!\n";
  }
  else cout << "AVISO: La serie ya se encuentra agregada!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA SERIE */

string searchSerieMenu(){

  cout << "========================================\n";
  cout << "              SEARCH SERIE              \n";
  cout << "========================================\n";
  string serie_name = getSerieName();
  cout << "========================================\n";

  return serie_name;
}
