#ifndef _USER_
#define _USER_

#include <string>
#include <iostream>

using namespace std;

struct User{
    string ID;
    std::string name, email;
    User *nextUser;
};

class UserList{
    public:
        User *head;
        UserList(){
            head = nullptr;
        }

        void insertAtEnd(string ID, std::string name, std::string email){
            User *temp = new User;
            temp->ID = ID;
            temp->name = name;
            temp->email = email;
            temp->nextUser = nullptr;

            if(head == nullptr){
                head = temp;
            }
            else{
                User *p =  head;
                while(p->nextUser != nullptr){
                    p = p->nextUser;
                }
                p->nextUser = temp;
            }

        }
        void display(){
            User *tP  = head;
            while(tP->nextUser != nullptr){
                cout <<"ID: " << tP->ID <<"| Email: " << tP->email << endl;
                tP =  tP->nextUser;
            }
            std::cout << std::endl;
        }
        int deleteAtEnd(){
            User *pre = head, *curr = head;
 
            while(curr->nextUser != nullptr){
                pre  = curr;
                curr = curr->nextUser;
            }
            //int value = curr->data;

            pre->nextUser = nullptr;
            delete curr;
            return 0;
        }
        void insertAtStart(int ID, std::string name, std::string email){
            User *temp = new User;
            temp->ID = ID;
            temp->name = name;
            temp->email = email;
            temp->nextUser = nullptr;

            if(head == nullptr){
                head = temp;
            }
            else{
                temp->nextUser = head;
                head = temp;
            }
        }
};

#endif