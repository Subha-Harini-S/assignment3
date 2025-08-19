#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
using namespace std;

void create(){
    cout<<"Add the details:\n";
    char slash;
    int date,month,year;
    cout<<"Date:";
    cin>>date>>slash>>month>>slash>>year;
    if (date >= 1 && date <= 31 && month >= 1 && month <= 12 && year >= 1950 && year <= 2050) {
        cout << date << "/" << month << "/" << year << "\n";
    } else {
        cout << "Invalid date. Please ensure:\n"
             << "Day is between 1 and 31\n"
             << "Month is between 1 and 12\n"
    
             << "Year is between 1950 and 2050\n";
} 
    cout << "Sales ID: ";
    srand(time(0));
    int random = rand() % 9000 + 1; 
    string salesID =to_string(random);
    cout << salesID << "\n";

    cout<<"Item Name:";
    string item;
    cin>>item;
    cout<<item<<"\n";

    cout<<"Item Quantity:";
    int quantity;
    cin>>quantity;
    cout<<quantity<<"\n";

    cout<<"Unit Price:";
    int price;
    cin>>price;
    cout<<price<<"\n";

    ofstream file("sales.csv",ios::app);
    if(!file){
        cout<<"Error opening file\n";
        return;
    }
    file << salesID << "," << date << "/" << month << "/" << year << "," << item << "," << quantity << "," << price << "\n";

    file.close();
    cout<<"Data saved to sales.csv\n";

    char next;
    cout<<"Do you want to enter next data?\n";
    cin>>next;
    if(next=='y'){
        create();
    }
}

void crud(){
    cout<<"...";
    create();
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
        ofstream file("sales.csv");
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
        ofstream file("temp.csv");
    }
}