#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"

//initializes the book linked list for the system
void init_books(BookList booklist){
    long long ISBN;
    string name, author,ISBN_string;

    ifstream read_book_dataset("data/sample_dataset.txt");

    //runs till the file runs out of lines
    while(read_book_dataset.good()){
        getline(read_book_dataset,ISBN_string,',');
        getline(read_book_dataset,name,',');
        getline(read_book_dataset,author,'\n');

        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
        author.erase(0, author.find_first_not_of(" \t\n\r\f\v"));
        author.erase(author.find_last_not_of(" \t\n\r\f\v") + 1);
        //cout << name << " : " << author << endl;
        ISBN = stoll(ISBN_string);
        booklist.insertAtEnd(ISBN, name, author);
    }

    booklist.display();
};

void init_users(UserList userlist){
    int ID;
    string name, email, ID_string;

    ifstream read_user_dataset("data/user_dataset.txt");

    while(read_user_dataset.good()){
        getline(read_user_dataset,ID_string,',');
        getline(read_user_dataset,name,',');
        getline(read_user_dataset,email,'\n');

        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
        email.erase(0, email.find_first_not_of(" \t\n\r\f\v"));
        email.erase(email.find_last_not_of(" \t\n\r\f\v") + 1);
        //cout<< ID_string << name << " : " << email << endl;
        //ID = stoi(ID_string);
        userlist.insertAtEnd(ID_string, name, email);
    }

    userlist.display();
};

//manages the initialization
void init_system(BookList booklist, UserList userlist){
    init_books(booklist);
    init_users(userlist);
};