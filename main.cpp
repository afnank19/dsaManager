#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"
#include "system_init.h"

using namespace std;

void DisplayOptions(){
    cout << "Library Managment System" << endl;
    cout << "Please choose from the options below:" << endl;
    cout << "Press (B) to borrow" << endl;
    cout << "Press (R) to return" << endl;
    cout << "Press (S) to search" << endl;
    cout << "Press (C) to sort(A-Z)" << endl;
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
            if(recepientUser == nullptr){
                cout << "Not a User!" << endl;
                break;
            }
            return_transaction(bookName, recepientUser->ID, recepientUser->name,recepientUser->email);
        }
        case 's':{
            char search_in;
            cout << "Press (B) to search books" << endl;
            cout << "Press (U) to search users" << endl;
            cin >> search_in;

            if(search_in == 'b'){
                long long ISBN;
                string name, author;
                cout << "Press (I) for ISBN search" << endl;
                cout << "Press (N) for Name search" << endl;
                cout << "Press (T) for Author search" << endl;
                cin >> search_in;
                if(search_in == 'i'){
                    cout << "Enter ISBN:";
                    cin >> ISBN;
                    Book *result =book.searchThruISBN(ISBN);
                    if(result == nullptr){
                        cout << "Nothing found" << endl;
                        break;
                    }
                    cout << result->ISBN << "," << result->name << "," << result->author << endl;
                }else if(search_in == 'n'){
                    cout << "Enter Book Name: ";
                    getline(cin, name);
                    Book *result =book.searchBooks(name, false,false);
                    if(result == nullptr){
                        cout << "Nothing found" << endl;
                        break;
                    }
                    cout << result->ISBN << "," << result->name << "," << result->author << endl;
                }
                else if(search_in == 't'){
                    cout << "Enter Author:";
                    getline(cin, author);
                    Book *result =book.searchThruAuthor(author);
                    if(result == nullptr){
                        cout << "Nothing found" << endl;
                        break;
                    }
                    cout << result->ISBN << "," << result->name << "," << result->author << endl;
                }else{
                    cout << "--invalid--" << endl;
                }
            }else if(search_in == 'u'){
                string name, id;

                cout << "Press (K) for user search" << endl;
                cout << "Press (L) for ID search" << endl;
                cin >> search_in;
                if(search_in == 'k'){
                    cout << "Enter user name:";
                    getline(cin, name);
                    User *recepientUser = user.searchByName(name);
                    if(recepientUser == nullptr){
                        cout << "Not a User!" << endl;
                        break;
                    }
                    cout << recepientUser->ID << "," << recepientUser->name << endl;
                }else if(search_in == 'l'){
                    cout << "Enter user ID:";
                    cin >> id;
                    User *recepientUser = user.searchUsers(id);
                    if(recepientUser == nullptr){
                        cout << "Not a User!" << endl;
                        break;
                    }
                    cout << recepientUser->ID << "," << recepientUser->name << endl;
                }
            }
        }
        break;
        case 'c': {
            book.sortBooks();
            book.display();
        }
        break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }


}