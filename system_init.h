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
        booklist.insertNewBook(ISBN, name, author);
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
        userlist.insertNewUser(ID_string, name, email);
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

ofstream transaction_file;

void init_transaction(long long ISBN, string bookname, string author, string user_id, string user_name){
    transaction_file.open("data/transaction_history.txt", ios::app);

    string currentTime = GetSysTime();
    string to_file = to_string(ISBN) +"," + bookname + "," + author + " :: Borrowed by => " + 
                        user_id + ": " + user_name + " at " + currentTime;

    transaction_file << to_file;

    cout << "TRANSACTION COMPLETE, check data/transaction_history.txt for complete information!";
    transaction_file.close();
}
void return_transaction(string bookname, string user_id, string user_name, string user_email){
    transaction_file.open("data/transaction_history.txt", ios::app);

    string currentTime = GetSysTime();
    //ofstream transaction_file("data/transaction_history.txt");

    transaction_file << "R," << bookname << ",Returned by => " << user_id << "," <<
                        user_name << "," << user_email << " at " << currentTime;

    cout << "RETURN COMPLETE, check data/transaction_history.txt for complete information!";
    transaction_file.close();
}
bool isAllDigits(string str){
    if(str == ""){
        return false;
    }
    for(int i = 0; i < str.length(); i++){
        if (!isdigit(str[i])) {
            return false; // If a non-numeric character is found, return false
        }
    }
    return true;
}

void update_borrow(BookList b){
    ifstream getAvailFromTransaction("data/transaction_history.txt");

    string ISBN_string, throwaway, bookname;
    long long ISBN_check;

    while(getAvailFromTransaction.good()){
        getline(getAvailFromTransaction,ISBN_string,',');
        getline(getAvailFromTransaction, bookname,',');
        getline(getAvailFromTransaction, throwaway,'\n');
        //cout << ISBN_string << " = " << isAllDigits(ISBN_string) << endl;
        
        if(ISBN_string != "R"){
            if(isAllDigits(ISBN_string)){
                ISBN_check = stoll(ISBN_string);
                b.updateAvailability(ISBN_check, bookname, false);
            }
        }else{
            b.updateAvailability(ISBN_check, bookname, true);
        }
        
    }

    getAvailFromTransaction.close();
}
