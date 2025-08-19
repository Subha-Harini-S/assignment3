#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
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

void read(){
     cout << "View sales.csv file\n";
    ifstream file("sales.csv");

    if (!file.is_open()) {
        cout << "Unable to open file.\n";
        return;
    }

    string line;
    cout << "Sales record\n";
    cout << left << setw(10) << "SalesID"
         << setw(15) << "Date"
         << setw(20) << "Item"
         << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;
    cout << string(65, '-') << endl; 

    while (getline(file, line)) {
        stringstream ss(line);
        string salesID, date, item, quantity, price;

        getline(ss, salesID, ',');
        getline(ss, date, ',');
        getline(ss, item, ',');
        getline(ss, quantity, ',');
        getline(ss, price, ',');

        cout << left << setw(10) << salesID
             << setw(15) << date
             << setw(20) << item
             << setw(10) << quantity
             << setw(10) << price << endl;
    }

     file.close();

}
void search(){
    cout<<"Search the sales ID is present or not?\n";
    char id;
    cin>>id;
    if(id=='n'){
        cout<<"Sales ID is not present the Sales.csv file\n";
    }
    else{
        cout<<"Sales ID:"<<id<<"\n";
    }
}

void update(){
    char update;
    cout<<"Do you need to update?\n";
    cin>>update;
    if(update=='y'){
    cout<<"View sales.csv file\n";
    cout << "Enter Sales ID to update: ";
    string targetID;
    cin >> targetID;

    ifstream file("sales.csv");
    if (!file) {
        cout << "Cannot open sales.csv\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string salesID;
        getline(ss, salesID, ',');

        if (salesID == targetID) {
            found = true;

            string date, item, quantity, price;
            getline(ss, date, ',');
            getline(ss, item, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');

            cout << "\nSelect detail to update:\n";
            cout << "1. Item\n2. Quantity\n3. Price\n4. Date\n5. All details\n";
            int choice;
            cin >> choice;

            cin.ignore(); 

            switch (choice) {
                case 1:
                    cout << "Enter new item name: ";
                    getline(cin, item);
                    break;
                case 2:
                    cout << "Enter new quantity: ";
                    getline(cin, quantity);
                    break;
                case 3:
                    cout << "Enter new price: ";
                    getline(cin, price);
                    break;
                case 4:
                    cout << "Enter new date (dd/mm/yyyy): ";
                    getline(cin, date);
                    break;
                case 5:
                    cout << "Enter new item name: ";
                    getline(cin, item);
                    cout << "Enter new quantity: ";
                    getline(cin, quantity);
                    cout << "Enter new price: ";
                    getline(cin, price);
                    cout << "Enter new date (dd/mm/yyyy): ";
                    getline(cin, date);
                    break;
                default:
                    cout << "Invalid choice. No update done.\n";
                    break;
            }

            line = salesID + "," + date + "," + item + "," + quantity + "," + price;
        }
        lines.push_back(line);
    }
    file.close();

    if (!found) {
        cout << "Sales ID " << targetID << " not found.\n";
        return;
    }

    ofstream outFile("sales.csv");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto &l : lines) {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Record updated successfully.\n";
}
}
void crud(){
    cout<<"...";
    create();
    read();
    update();
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