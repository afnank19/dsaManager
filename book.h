#ifndef _BOOK_
#define _BOOK_

#include <string>
#include <iostream>

using namespace std;

struct Book{
    long long ISBN;
    std::string name, author;
    bool availability = true;
    Book *nextBook;
};

class BookList{
    public:
        Book *head;
        BookList(){
            head = nullptr;
        }

        void insertNewBook(long long ISBN, std::string name, std::string author){
            Book *temp = new Book;
            temp->ISBN = ISBN;
            temp->name = name;
            temp->author = author;
            temp->nextBook = nullptr;

            if(head == nullptr){
                head = temp;
            }
            else{
                Book *p =  head;
                while(p->nextBook != nullptr){
                    p = p->nextBook;
                }
                p->nextBook = temp;
            }

        }
        void display(){
            Book *tP  = head;
            while(tP!= nullptr){
                cout << "Name: " << tP->name << endl;
                tP =  tP->nextBook;
            }
            std::cout << std::endl;
        }
        int deleteAtEnd(){
            Book *pre = head, *curr = head;
 
            while(curr->nextBook != nullptr){
                pre  = curr;
                curr = curr->nextBook;
            }
            //int value = curr->data;

            pre->nextBook = nullptr;
            delete curr;
            return 0;
        }
        void insertAtStart(long ISBN, std::string name, std::string author){
            Book *temp = new Book;
            temp->ISBN = ISBN;
            temp->name = name;
            temp->author = author;
            temp->nextBook = nullptr;

            if(head == nullptr){
                head = temp;
            }
            else{
                temp->nextBook = head;
                head = temp;
            }
        }
        Book* searchBooks(string name, bool isBorrowing, bool isReturning){
            Book *tP = head;

            while(tP != nullptr){
                if(tP->name == name && tP->availability){
                    if(isBorrowing){
                        tP->availability = false;
                    }
                    break;
                }
                else if(isReturning && tP->name == name && !tP->availability){
                    tP->availability = true;
                    break;
                }
                tP = tP->nextBook;
            }

            return tP;
        }
        void updateAvailability(long long ISBN, string bookname, bool returnFix){
            Book *tP = head;

            while(tP != nullptr){
                if(tP->name == bookname && returnFix){
                    tP->availability = true;
                    cout << tP->name << tP->availability << endl;
                    return;
                }
                if(tP->ISBN == ISBN){
                    tP->availability = false;
                    cout << tP->name << tP->availability << endl;
                    return;
                }
                tP = tP->nextBook;
            }

            return;
        }
};

#endif