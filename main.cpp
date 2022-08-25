#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>

using namespace std;

//Deklaracija funkcija
string checkIfExists(string name);

class Acc{
public:
    string ime,sifra;
    Acc(string &ime_input,string &sifra_input){
        ime=ime_input;
        sifra = sifra_input;
    }
    void changeName(){
        ifstream baza;
        ofstream copyBaza;
        string newName,red;
        ponoviUpis:cout<<"Enter your new name : ";
        getline(cin,newName);
        if(checkIfExists(newName)!="no"){
            cout<<"This name already exist! Try new one"<<endl;
            system("pause");
            goto ponoviUpis;
        }
        baza.open("baza.txt");
        copyBaza.open("copy.txt");
        while(!baza.eof()){

                getline(baza,red);
                if(red.substr(0,red.find(';'))==ime){
                    copyBaza<<newName<<";"<<sifra<<"\n";
                }
                else{
                    copyBaza<<red<<"\n";
                }

        }
        copyBaza.close();
        baza.close();

        cout<<"Success! Name is changed from "<<ime<<" to -> "<<newName<<endl;
        ime=newName;
        remove("baza.txt");
        rename("copy.txt","baza.txt");
        system("pause");
    }
    void changePass(){
        string pass,red;
        ifstream baza;
        ofstream copyBaza;
        ponoviUpis:cout<<"Enter your new password : ";
        getline(cin,pass);
        if(checkIfExists(pass)!="no"){
            cout<<"This name already exist! Try new one"<<endl;
            system("pause");
            goto ponoviUpis;
        }
        baza.open("baza.txt");
        copyBaza.open("copy.txt");
        while(!baza.eof()){

                getline(baza,red);
                if(red.substr(0,red.find(';'))==ime){
                    copyBaza<<ime<<";"<<pass<<"\n";
                }
                else{
                    copyBaza<<red<<"\n";
                }

        }
        copyBaza.close();
        baza.close();

        cout<<"Success! Password is changed from "<<sifra<<" to -> "<<pass<<endl;
        sifra = pass;
        remove("baza.txt");
        rename("copy.txt","baza.txt");
        system("pause");
    }
    void printUserInfo(){
        cout<<"Your name is -> "<<ime<<endl;
        cout<<"Your password is -> "<<sifra<<endl<<endl;
        cout<<"-----------------------------"<<endl<<endl;
        system("pause");
    }
};

string checkIfExists(string name){
    string red;
    ifstream baza;
    baza.open("baza.txt");
    while(!baza.eof()){

        getline(baza,red);
        if(red.substr(0,red.find(';'))==name){
            return red;
            break;
        }

    }
    baza.close();
    return "no";
}

Acc takeAccInfo(){
    ofstream baza;
    string name,pass;
    char option;
    do{
    system("cls");
    cout<<endl<<"~~~~~~ REGISTARTION APPLICATION ~~~~~~"<<endl<<endl;
    cout<<"Do you have an account? (y/n) -> ";
    cin>>option;
    option=tolower(option);
    }while(option!='n' && option!='y');
    cin.ignore();

    string userInfo;

    pocetak:switch(option){
        case 'y' :
            upis:system("cls");
            cout<<"::LOGGIN IN::"<<endl<<endl;
            cout<<"Enter your name : ";
            getline(cin,name);
            userInfo = checkIfExists(name);
            if(userInfo=="no"){
                system("pause");
                goto upis;
            }
            cout<<"Enter your password : ";
            getline(cin,pass);
            if(pass == userInfo.substr(userInfo.find(';')+1,userInfo.length()-userInfo.find(';'))){
                Acc user = Acc(name,pass);
                return user;
            }
            else{
                cout<<"Incorrect password!"<<endl<<endl;
                system("pause");
                goto upis;
            }
        break;
        case 'n':
            ponovo:system("cls");
            cout<<"::REGISTRATION::"<<endl<<endl;
            cout<<"Enter your name : ";
            getline(cin,name);
            userInfo = checkIfExists(name);
            if(userInfo!="no"){
                goto ponovo;
            }
            cout<<"Enter your password : ";
            getline(cin,pass);
            baza.open("baza.txt",fstream::app);
            baza<<name<<";"<<pass<<"\n";
            baza.close();
        break;
    }
    if(option == 'n'){
        option = 'y';
        goto pocetak;
    }
}

void Menu(){
    Acc user =takeAccInfo();
    int opt;//option to choose what to select

    do{
        do{
        system("cls");
        cout<<"::MENU::"<<endl<<endl;
        cout<<"Welcome Mr."<<user.ime<<endl<<endl;
        cout<<"1.Print my info"<<endl;
        cout<<"2.Change name"<<endl;
        cout<<"3.Change password"<<endl;
        cout<<"0.Exit"<<endl<<endl;
        cout<<"Enter number -> ";
        cin>>opt;
        }while(opt<0 || opt>3);
        cin.ignore();
        cout<<endl;
        cout<<"-----------------------------"<<endl<<endl;
        switch(opt){
            case 1:user.printUserInfo();break;
            case 2:user.changeName();break;
            case 3:user.changePass();break;
            case 0:break;
        }
    }while(opt!=0);
}

int main(){

    Menu();

    return 0;
}
