#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

// STRUCT

/*El siguiente struct sirve para almacenar el conjunto de elementos de los usuarios
  como el correo, la edad, el pais, la calificaciones y las reseñas.*/

struct Users{
    int id;
    string email;
    int years_old;
    string country;

    Users *next_user;
    Users *prev_user;
};

/* PROCEDIMIENTOS & FUNCIONES PARA LOS USUARIOS */

/* Funcion que busca retornar un puntero que apunte a un elemento de tipo usuario */

Users *createUser(int id, string email, int old, string country){

    Users *new_user = new Users;

    new_user->id = id; 
    new_user->email = email;
    new_user->years_old = old;
    new_user->country = country;

    new_user->next_user = NULL;
    new_user->prev_user = NULL;

    return new_user;
}

/* FUNCIONES PARA OBTENER LOS DATOS DE LAS PELICULAS */

/* Funcion para obtener el nombre de la pelicula */
string getUsersEmail(){
    string email;
    cin.ignore();
    cout << "\tEmail: ";
    getline(cin, email);
    return email;
} 

/* Funcion para obtener el ID del usuario */
int getUsersId(){
    int id;
    cout << "\tID: ";
    cin >> id;
    return id;
}

/* Funcion para obtener la edad del usuario */
int getUsersYearsOld(){
    int years_old;
    cout << "\tEdad: ";
    cin >> years_old;
    return years_old;
}

/* Funcion para obtener el pais del usuario */
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
            cout << "\tUser ID: " << aux->id << endl;
            cout << "\tUsers email: " << aux->email << endl;
            cout << "\tUser age: " << aux->years_old << endl;
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

void addUsers(Users **users_head, int id, string email, int years_old, string country){

    Users *new_user = createUser(id, email, years_old, country);

    if (!*users_head){
      *users_head = new_user;
    }
    else{
      new_user->next_user = *users_head;
      (*users_head)->prev_user = new_user;
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
      cout << "\tMovie name: " << aux->email << endl;
      cout << "\tMovie premiere: " << aux->years_old << endl;
      cout << "\tMovie type: " << aux->country << endl;
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
    int data_line = 0, id, years_old;
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

            if (data_line == 4){
                    country = text;
                    addUsers(&aux, id, email, years_old, country);
            }

            if (data_line == 3) years_old = stoi(text);

            if (data_line == 2) email = text;

            if (data_line == 1) id = stoi(text);

            ++data_line;

            if (data_line == 5) data_line = 0;
        }
        *users_head = aux;

    }
    else{
        cout << "\nERROR. Datos invalidos en el archivo!\n";
        cout << "AVISO: No se cargaron los datos del archivo de usuarios!\n\n";
    }

    file.close();
}

/* PROCEDIMIENTO PARA LA ESCRITURA DE ARCHIVOS EN USUARIOS */

void addUserToFile(int id, string email, int years_old, string country){

    ofstream file;

    file.open("usersfile.txt", ios::app);

    if (file.fail()){
            cout << "ERROR. No se pudo abrir el archivo";
            exit(1);
    }

    file << endl;
    file << endl << id;
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


        file << aux->id << endl;
        file << aux->email << endl;
        file << aux->years_old << endl;
        file << aux->country << endl << endl;

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

    if (menu == "0" || menu == "1" || menu == "2" || menu == "3" || menu == "4")
        return stoi(menu);

    cout << "ERROR. Ingresaste " << menu << " que es un valor invalido.\n";
    cout << "Por favor ingresar una opcion correcta.\n";
    return -1;
}

void addUsersMenu(Users **users_head){


    cout << "========================================\n";
    cout << "                ADD USER                \n";
    cout << "========================================\n";
    int id = getUsersId();
    string email = getUsersEmail();
    int years_old = getUsersYearsOld();
    string country = getUsersCountry();
    cout << "========================================\n";

    bool users_exist = findUsers(*users_head, email);

    if (users_exist == false){
        addUsers(&*users_head, id, email, years_old, country);
        addUserToFile(id, email, years_old, country);
        cout << "Se agrego el usuario correctamente!\n";
    } else {
        cout << "AVISO: El usuario ya existe!\n";
    }
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

///////////////////////////////////////////////////////////////////////
