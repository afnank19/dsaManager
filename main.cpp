#include <iostream>
#include <fstream>
#include "book.h"
#include "user.h"
#include "system_init.h"

using namespace std;

int main(){
    BookList book;
    UserList user;

    init_system(book, user);
}