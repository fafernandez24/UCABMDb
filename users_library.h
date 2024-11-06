#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using  sizeType = std::string::size_type;

/////////////////////////////////////////////////////////////////////////////////////////////

// STRUCT

/*El siguiente struct sirve para almacenar el conjunto de elementos de los usuarios
  como el correo, la edad, el pais, la calificaciones y las reseñas.*/

struct Users{
    string email;
    int years_old;
    string country;

    Users *next_user;
    Users *prev_user;
};

/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCIONES DE VALIDACION DE TIPO BOOLEANO*/

/* ESTA FUNCION VALIDA LA EDAD DEL USUARIO */

bool checkIntDataYearsOld(string word){

    if (word.empty()) return false;

    for (sizeType n = 0; n < word.length(); ++n){
        if (word[n] < '0' || word[n] > '9') return false;
    }

    if (stoi(word) >= 0 && stoi(word) <= 150) return true;

    return false;
}

/* ESTA FUNCION VALIDA EL CORREO DEL USUARIO */

bool checkUserEmail(string email){

    if (email.empty()) return false;

    for (sizeType n = 0; n < email.length(); ++n){
        if (email[n] == '@') return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS & FUNCIONES PARA LOS USUARIOS */

/* Funcion que busca retornar un puntero que apunte a un elemento de tipo usuario */

Users *createUser(string email, int old, string country){

  Users *new_user = new Users;

  new_user -> email = email;
  new_user -> years_old = old;
  new_user -> country = country;

  new_user -> next_user = NULL;
  new_user -> prev_user = NULL;

  return new_user;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS PELICULAS */

/* Funcion para obtener el nombre de la pelicula */
string getUsersEmail(){
  string email;
  bool check_email = false;

  while(check_email == false){
    cin.ignore();
    cout << "\tEmail: ";
    getline(cin, email);

    check_email = checkUserEmail(email);
    if (check_email == false){
      cout << "ERROR. Ingresaste un correo invalido!\n";
      cout << "AVISO: Recuerda incluir el @!\n";
    }
  }

  return email;
} 

/* Funcion para obtener el año de estreno de la pelicula */
int getUsersYearsOld(){
  string years_old;
  bool check_num = false;

  while (check_num == false){

    cout << "\tEdad: ";
    cin >> years_old;
    
    check_num = checkIntDataYearsOld(years_old);
    if (check_num == false){
      cout << "ERROR. Ingresaste un valor invalido!\n";
      cout << "AVISO: Igresar un entero entre 0 y 150!\n";
    }
  }
  return stoi(years_old);
}

/* Funcion para obtener el genero de la pelicula */
string getUsersCountry(){
  string country;
  cin.ignore();
  cout << "\tPais: ";
  getline(cin, country);
  return country;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* Procedimiento para mostras las peliculas en pantalla */

void printUsers(Users *users_head){

  Users *aux = users_head;
  int users_num = 1;

  cout << "========================================\n";
  cout << "                USUARIOS\n";
  cout << "========================================\n";

  if (users_head){
    while (aux){

      cout << "              User #" << users_num << "              \n";
      cout << "========================================\n";
      cout << "\tUser email: " << aux-> email << endl;
      cout << "\tUser age: " << aux->years_old << " years" << endl;
      cout << "\tUser country: " << aux->country << endl;
      cout << "========================================\n";

      aux = aux->next_user;
      ++users_num;
    }
  }
  else{

    cout << "========================================\n";
    cout << "                User #0\n";
    cout << "========================================\n";
    cout << "\tAun no hay usuarios...\n";
    cout << "========================================\n";
    cout << endl;
  }
}

/* Procedimiento para agregar peliculas */

void addUsers(Users **users_head, string email, int years_old, string country){

    Users *new_user = createUser(email, years_old, country);

    if (!*users_head){
      *users_head = new_user;
    }
    else{
      new_user -> next_user = *users_head;
      *users_head = new_user;   
    }
}

/* Procedimiento para eliminar peliculas */

void deleteUsers(Users **users_head, string email){

  if (*users_head){

    Users *aux = *users_head;

    if (aux -> email != email){
      Users *aux2 = NULL;

      while (aux -> email != email || aux ->next_user == NULL){
        aux2 = aux;
        aux = aux -> next_user;
      }
      aux2 -> next_user = aux -> next_user;
      delete(aux);
    }
    else{
      *users_head = aux -> next_user;
      delete(aux);
    }
  }
  else{
    cout << "ERROR. Lista de usuarios vacia.\n";
  }
}

/* PROCEDIMIENTO PARA BUSCAR AL USUARIO E IMPRIMIR SUS DATOS */

void searchUsers(Users *users_head, string email){
   
   if (users_head){

      Users *aux = users_head;
      int users_num = 1;

      while (aux -> email != email){
        aux = aux -> next_user;
        ++users_num;
      }

      cout << "              Movie #" << users_num << "              \n";
      cout << "========================================\n";
      cout << "\tUser email: " << aux->email << endl;
      cout << "\tUser age: " << aux->years_old << endl;
      cout << "\tUser country: " << aux->country << endl;
      cout << "========================================\n";
   }
   else{
      cout << "ERROR. Lista de peliculas vacia.\n";
   }
}

/* FUNCION QUE RETORNA UN TIPO DE DATO BOOLEANO QUE DETERMINA SI UN USUARIO SE ENCUENTRA O NO EN LA LISTA DE USUARIOS */

bool findUsers(Users *users_head, string email){
  if (users_head){
    Users *aux = users_head;
    while (aux){
      if (aux -> email == email) return true;
      aux = aux -> next_user;
    }
  }
  return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* PROCEDIMIENTOS PARA LA LECTURA Y ESCRITURA  DEL ARCHIVO DESTINADO PARA USUARIOS */

/* PROCEDIMIENTO PARA LA LECTURA DE ARCHIVOS PARA USUARIOS */

void readUsersFile(Users **users_head){

  ifstream file;
  string text, email, country;
  int data_line = 0, years_old;
  Users *aux = *users_head;


  file.open("usersfile.txt", ios::in);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo de USUARIOS!\n";
      exit(1);
  }

  getline(file, text);

  if (text == "USERS"){

      while(!file.eof()){

      getline(file,text);

      if (data_line == 3){
          country = text;
          addUsers(&aux, email, years_old, country);
      }

      if (data_line == 2){

        if (checkIntDataYearsOld(text) == true) years_old = stoi(text);
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de usuarios!\n\n";
          file.close();
          break;
        }
      }

      if (data_line == 1){

        if (checkUserEmail(text) == true) email = text;
        else{
          cout << "\nERROR. Dato invalidos en el archivo!\n";
          cout << "AVISO: No se cargaron los datos del archivo de usuarios!\n\n";
          file.close();
          break;
        }
      } 

      ++data_line;

      if (data_line == 4) data_line = 0;
    }
    *users_head = aux;

  }
  else{
    cout << "\nERROR. Dato invalidos en el archivo!\n";
    cout << "AVISO: No se cargaron los datos del archivo de usuarios!\n\n";
  }


  file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN USUARIOS */

void addUserToFile(string email, int years_old, string country){

  ofstream file;

  file.open("usersfile.txt", ios::app);

  if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo";
      exit(1);
  }

  file << endl;
  file << endl << email;
  file << endl << years_old;
  file << endl << country;

  file.close();
}

void writeUsersFile(Users *users_head){

  if (users_head){

    ofstream file;
    file.open("usersfile.txt", ios::out);

    if (file.fail()){
      cout << "ERROR. No se pudo abrir el archivo\n";
      exit(1);
    }
    else{

      Users *aux = users_head;

      file << "USERS\n\n";

      while(aux){


        file << aux -> email << endl;
        file << aux -> years_old << endl;

        if (aux -> next_user == NULL) file << aux -> country;
        else file << aux -> country << endl << endl;

        aux = aux -> next_user;
      }
    }
  }
  else cout << "ERROR. Lista de usuarios vacia!";
}

/////////////////////////////////////////////////////////////////////////////////////////////

/* FUNCION DE MENU PARA USUARIOS QUE RETORNA UN NUMERO */

int usersMenu(){

  string menu;

  cout << "========================================\n";
  cout << "               USERS MENU               \n";
  cout << "========================================\n";
  cout << "(1) Ver usuarios\n";
  cout << "(2) Agregar usuario\n";
  cout << "(3) Eliminar usuario\n";
  cout << "(4) Buscar usuario\n";
  cout << "(0) Salir\n";
  cout << "========================================\n";
  cout << "Ingresar opcion: ";
  cin >> menu;
  cout << "========================================\n";

  if (menu >= "0"  && menu <= "3") return stoi(menu);

  cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
  cout << "Por favor ingresar una opcion correcta.\n";
  return -1;
}

void addUsersMenu(Users **users_head){

  cout << "========================================\n";
  cout << "                ADD USER                \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  int years_old = getUsersYearsOld();
  string country = getUsersCountry();
  cout << "========================================\n";

  bool users_exist = findUsers(*users_head, email);

  if (users_exist == false){
    addUsers(&*users_head, email, years_old, country);
    addUserToFile(email, years_old, country);
    cout << "Se agrego el usuario correctamente!\n";
  }
  else cout << "AVISO: El usuario ya existe!\n";

}

void deleteUsersMenu(Users **users_head){

  cout << "========================================\n";
  cout << "              DELETE USER               \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  cout << "========================================\n";

  bool users_exist = findUsers(*users_head, email);

  if (users_exist == true){
    deleteUsers(&*users_head, email);
    writeUsersFile(*users_head);
    cout << "El usuario se borro correctamente!\n";
  }
  else cout << "ERROR. El usuario no se pudo encontrar!\n";
}

/* PROCEDIMIENTO DEL MENU PARA BUSCAR LA PELICULA */

void searchUsersMenu(Users *users_head){

  cout << "========================================\n";
  cout << "              SEARCH USERS              \n";
  cout << "========================================\n";
  string email = getUsersEmail();
  cout << "========================================\n";

  bool users_exist = findUsers(users_head, email);

  if (users_exist == true) searchUsers(users_head, email);
  else cout << "ERROR. No se encontro el usuario!\n";
}

/////////////////////////////////////////////////////////////////////////////////////////////
