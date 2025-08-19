#include <iostream>
#include <fstream>
using namespace std;

void crud(){
    cout<<"...";
    // create();
    // read();
    // update();
    // delete();
}

int main(){
    cout<<"START\n";
    cout<<"Is sales.csv file exist? y/n\n";
    char ch;
    cin>>ch;
    if(ch=='y'){
        cout<<"Perforn any of the CRUD operation\n";
        crud();
    }
    else{
        cout<<"Create sales.csv file\n";
        std::ofstream file("sales.csv");
    }
     cout<<"Is temp.csv file exist? y/n\n";
    char temp;
    cin>>ch;
    if(temp=='y'){
        cout<<"Perforn any of the Sorting operation\n";
        // sorting();
    }
    else{
        cout<<"Create temp.csv file\n";
        std::ofstream file("temp.csv");
    }
}