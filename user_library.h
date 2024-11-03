#include <iostream>
#include <string>


using namespace std;


struct User {
    string email;
    string username;
    int age;
    string nationality;
    User *next;
    User *prev;
};

bool validateEmail(const std::string &email);
void saveUsers(User *head);
void displayUsers();
void loadUsersFromFile(User **head);
bool isUserListEmpty(User *head);
void registerUser(User *&head);
void deleteUser(User *&head, const std::string &email);
