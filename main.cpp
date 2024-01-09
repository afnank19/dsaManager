#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"
#include "system_init.h"

using namespace std;

void DisplayOptions(){
    cout << "Press (B) to borrow" << endl;
    cout << "Press (S) to search" << endl;
    cout << "Press (A) to sort" << endl;
}
string user_input_handler(){
    string user_input;
    cin >> user_input;
    return user_input;
}

int main(){
    BookList book;
    UserList user;

    char input;

    //init_system(book, user);
    book = init_books(book);
    user = init_users(user);

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
            Book *borrowedBook = book.searchBooks(bookName, true);
            if(borrowedBook == nullptr){
                cout << "Book was not found or is not available.";
                break;
            }
            string user_id;
            cout << "Enter your ID: ";
            cin >> user_id;
            User *recepientUser = user.searchUsers(user_id);
            init_transaction(borrowedBook->ISBN,borrowedBook->name,borrowedBook->author,user_id, recepientUser->name);
        }
        break;
        case 's':{
            cout << "haha";
        }
        break;
        
        default:
            break;
        }
    }


}