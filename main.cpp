#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"

using namespace std;

void init_system(BookList booklist){
    long long ISBN;
    string name, author,ISBN_string;

    ifstream read_book_dataset("data/sample_dataset.txt");

    while(read_book_dataset.good()){
        getline(read_book_dataset,ISBN_string,',');
        getline(read_book_dataset,name,',');
        getline(read_book_dataset,author,'\n');

        name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);
        author.erase(0, author.find_first_not_of(" \t\n\r\f\v"));
        author.erase(author.find_last_not_of(" \t\n\r\f\v") + 1);
        cout << name << " : " << author << endl;
    }

    //booklist.display();
}


int main(){
    BookList book;

    init_system(book);
}