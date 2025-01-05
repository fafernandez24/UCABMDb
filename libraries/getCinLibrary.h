// @author Freddy Fernández

#include <iostream>

using namespace std;
using  sizeType = std::string::size_type;

bool checkIntData(string word){
    for(sizeType i = 0; i < word.length(); ++i){
        if (word[i] < '0' || word[i] > '9'){
            return false;
        }
    }
    return true;
}

int getInt(){

    string word = "";
    bool bol = false;

    while(bol == false){
        cout << "Ingresar un dato de tipo entero: ";
        cin >> word;

        bol = checkIntData(word);
    }

    return stoi(word);
}