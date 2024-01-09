#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "book.h"
#include "user.h"

//initializes the book linked list for the system
BookList init_books(BookList booklist){
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

    //booklist.display();
    return booklist;
};

UserList init_users(UserList userlist){
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

    return userlist;
    //userlist.display();
};
string GetSysTime(){
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);

    std::string currentTimeString = std::ctime(&currentTimeT);

    return currentTimeString;
}

void init_transaction(long long ISBN, string bookname, string author, string user_id, string user_name){
    ofstream transaction_file("data/transaction_history.txt");
    string currentTime = GetSysTime();

    transaction_file << ISBN << "," << bookname << "," << author << " :: Borrowed by => " << 
                        user_id << ": " << user_name << " at " << currentTime;

    cout << "TRANSACTION COMPLETE, check data/transaction_history.txt for complete information!";
}
