
struct usuarios {
    int id;
    string correo_electronico;
    string nombre_de_usuario;
    int edad;
    string nacionalidad;
}

void guardar_usuarios(usuarios *p) {
    ofstream archivo("usuarios.txt");
    usuarios *actual = p;
    while (actual != NULL) {
        archivo << actual->id <<"\t "
                << actual->correo_electronico <<"\t "
                << actual->nombre_usuario <<"\t "
                << actual->edad << "\t "
                << actual->nacionalidad << endl;
        actual = actual->prx;
    }
    archivo.close();
}

void mostrar_usuarios() {
    ifstream archivo("usuarios.txt");
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}

void usuarios_por_archivo(usuarios **p) {
    ifstream archivo("usuarios.txt");
    string linea;
    while (getline(archivo, linea)) {
        usuarios *usuario_nuevo = new usuarios;
        usuario_nuevo->prx = NULL;
        usuario_nuevo->prev = NULL;
        istringstream iss(linea);
        iss >> usuario_nuevo->id;
        iss >> usuario_nuevo->correo_electronico;
        iss >> usuario_nuevo->nombre_usuario;
        iss >> usuario_nuevo->edad;
        getline(iss, usuario_nuevo->nacionalidad);
        if (*p != NULL) {
            (*p)->prev = usuario_nuevo;
            usuario_nuevo->prx = *p;
        }
        *p = usuario_nuevo;
    }
    archivo.close();
}

bool lista_vacia_usuarios(usuarios *p){
    if(p) return false;
    return true;
}

///void imprimir_los_usuarios(usuarios *p){
    usuarios *impus = p;
    cout << setw(10) << //////

void imprimir_usuario(usuarios*p){
    usuarios *current = p;