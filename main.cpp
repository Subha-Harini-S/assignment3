#include <iostream>
#include <fstream>
using namespace std;

int main(){
    cout<<"START\n";
    cout<<"Is sales.csv file exist? y/n\n";
    char ch;
    cin>>ch;
    if(ch=='y'){
        cout<<"Perforn any of the CRUD operation\n";
        // crud();
    }
    else{
        cout<<"Create sales.csv file\n";
        std::ofstream file("sales.csv");
    }
}