#include <iostream>
#include <string>


using namespace std;


struct User {
    std::string email;
    std::string username;
    int age;
    std::string nationality;
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
