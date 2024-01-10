#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"
#include "system_init.h"

using namespace std;

void DisplayOptions(){
    cout << "Press (B) to borrow" << endl;
    cout << "Press (R) to return" << endl;
    cout << "Press (S) to search" << endl;
    cout << "Press (C) to sort" << endl;
    cout << "Press (A) to Add new book" << endl;
}

int main(){
    BookList book;
    UserList user;

    char input;

    //init_system(book, user);
    book = init_books(book);
    user = init_users(user);
    update_borrow(book);

    string bookName;

    while(input != 'x'){
        cout << endl;
        DisplayOptions();
        cin >> input;

        switch (input){
        case 'b':{
            cout << "Enter FULL book name: ";
            cin.ignore();
            getline(cin, bookName);
            Book *borrowedBook = book.searchBooks(bookName, true, false);
            if(borrowedBook == nullptr){
                cout << "--Book was not found or is not available.--";
                break;
            }
            string user_id;
            cout << "Enter your ID: ";
            cin >> user_id;
            User *recepientUser = user.searchUsers(user_id);
            init_transaction(borrowedBook->ISBN,borrowedBook->name,borrowedBook->author,user_id, recepientUser->name);
        }
        break;
        case 'r':{
            string bookName;
            cout << "Enter FULL bookname you want to return: ";
            cin.ignore();
            getline(cin, bookName);

            Book *recievedBook = book.searchBooks(bookName, false, true);
            if(recievedBook == nullptr){
                cout << "--Recieved book is NOT part of Library!--" << endl;
                break;
            }
            if(recievedBook->availability){
                cout << "--Book Was Not Borrowed--" << endl;
                break;
            }
            string user_id;
            cout << "Enter your ID: ";
            cin >> user_id;
            User *recepientUser = user.searchUsers(user_id);
            return_transaction(bookName, recepientUser->ID, recepientUser->name,recepientUser->email);
        }
        break;
        
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }


}