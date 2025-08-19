#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
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
bool search(const string& targetID) {
    ifstream file("sales.csv");
    if (!file) {
        cout << "Cannot open sales.csv\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string salesID;
        getline(ss, salesID, ',');
        if (salesID == targetID) {
            file.close();
            return true;  
        }
    }
    file.close();
    return false; 
}

void update(){
    char update;
    cout << "Do you want to update? (y/n): ";
    cin >> update;
    if (update != 'y') return;
    cout << "Enter Sales ID to update: ";
    string targetID;
    cin >> targetID;
    if (!search(targetID)) {
        cout << "Sales ID " << targetID << " not found.\n";
        return;
    }
    ifstream file("sales.csv");
    if (!file) {
        cout << "Cannot open sales.csv\n";
        return;
    }
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string salesID;
        getline(ss, salesID, ',');
        if (salesID == targetID) {
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

void del(){
    cout << "Do you want to delete a record? (y/n): ";
    char del;
    cin >> del;
    if (del != 'y') return;
    cout << "Enter Sales ID to delete: ";
    string targetID;
    cin >> targetID;
    if (!search(targetID)) {
        cout << "Sales ID " << targetID << " not found.\n";
        return;
    }
    ifstream file("sales.csv");
    if (!file) {
        cout << "Cannot open sales.csv\n";
        return;
    }
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string salesID;
        getline(ss, salesID, ',');
        if (salesID != targetID) {
            lines.push_back(line);
        }
    }
    file.close();
    ofstream outFile("sales.csv");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
    cout << "Record with Sales ID " << targetID << " deleted successfully.\n";
}

void crud(){
    create();
    read();
    update();
    del();
}

void sorting(){
    ifstream file("sales.csv");
    if (!file) {
        cout << "Cannot open sales.csv\n";
        return;
    }
    vector<string> lines;
    vector<string> formattedDates;
    vector<string> fullRecords;
    string line;
    bool reachedEOF = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string salesID, date, item, quantity, price;
        getline(ss, salesID, ',');
        getline(ss, date, ',');
        getline(ss, item, ',');
        getline(ss, quantity, ',');
        getline(ss, price, ',');
        int d, m, y;
        char slash;
        stringstream ds(date);
        ds >> d >> slash >> m >> slash >> y;
        stringstream formattedDate;
        formattedDate << setw(4) << setfill('0') << y << "-"
                      << setw(2) << setfill('0') << m << "-"
                      << setw(2) << setfill('0') << d;
        string newLine = salesID + "," + formattedDate.str() + "," + item + "," + quantity + "," + price;
        fullRecords.push_back(newLine);
        formattedDates.push_back(formattedDate.str());
    }
    if (file.eof()) {
        reachedEOF = true;
    }
    file.close();
    for (size_t i = 0; i < fullRecords.size(); ++i) {
        for (size_t j = i + 1; j < fullRecords.size(); ++j) {
            if (formattedDates[i] > formattedDates[j]) {
                swap(fullRecords[i], fullRecords[j]);
                swap(formattedDates[i], formattedDates[j]);
            }
        }
    }
    ofstream tempFile("temp.csv");
    if (!tempFile) {
        cout << "Error creating temp.csv\n";
        return;
    }
    for (const auto &record : fullRecords) {
        tempFile << record << "\n";
    }
    tempFile.close();
    cout << "Sorted data saved to temp.csv.\n";
    if (!reachedEOF) {
        cout << "Did not reach end of file. Sorting again\n";
        sorting(); 
    } else {
        cout << "Reached end of file. Returning to main program.\n";
    }
}

void report(){
    ifstream file("temp.csv");
    ofstream report("report.txt");
    if (!file.is_open() || !report.is_open()) {
        cout << "Error opening temp.csv or report.txt file.\n";
        return;
    }
    string line;
    string currentDate = "";
    int subtotal = 0;
    int grandTotal = 0;
    bool isFirstLine = true;
    string firstDate = "";
    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);
        stringstream ss(line);
        string salesID, date;
        getline(ss, salesID, ',');
        getline(ss, date, ',');
        if (isFirstLine) {
            firstDate = date;
            isFirstLine = false;
        }
    }
    report << "\n\nc: " << firstDate << "\n\n";
    report << "Sales Report : Stationary Items Sold\n\n";
    report << string(99, '-') << "\n";
    report << left << setw(20) << "Date"
           << setw(15) << "SaleID"
           << setw(20) << "ItemName"
           << setw(12) << "Quantity"
           << setw(12) << "Price"
           << setw(15) << "SalesAmount" << "\n";
    report << string(99, '-') << "\n";
    for (const string& row : lines) {
        stringstream ss(row);
        string salesID, date, item, quantityStr, priceStr;
        getline(ss, salesID, ',');
        getline(ss, date, ',');
        getline(ss, item, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');
        int quantity = stoi(quantityStr);
        int price = stoi(priceStr);
        int salesAmount = quantity * price;

        if (date != currentDate && !currentDate.empty()) {
            report << string(99, '-') << "\n";
            report << right << setw(80) << "Subtotal for " << currentDate << " is : " << subtotal << "\n";
            report << string(99, '-') << "\n\n";
            grandTotal += subtotal;
            subtotal = 0;
        }
        report << left << setw(20) << date
               << setw(15) << salesID
               << setw(20) << item
               << setw(12) << quantity
               << setw(12) << price
               << setw(15) << salesAmount << "\n";
        subtotal += salesAmount;
        currentDate = date;
    }
    if (!currentDate.empty()) {
        report << string(99, '-') << "\n";
        report << right << setw(80) << "Subtotal for " << currentDate << " is : " << subtotal << "\n";
        report << string(99, '-') << "\n";
        grandTotal += subtotal;
    }
    report << right << setw(80) << "Grand Total: " << grandTotal << "\n";
    report << string(99, '-') << "\n";
    file.close();
    report.close();
    cout << "Report generated successfully in report.txt\n";
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
        sorting();
    }
    else{
        cout<<"Create temp.csv file\n";
        ofstream file("temp.csv");
        sorting();
    }
    char rep;
    cin>>rep;
    if(rep=='y'){
        cout<<"Store temp.csv file to report.txt\n";
        report();
    }
    else{
        cout<<"Create report.txt file\n";
        ofstream file("report.txt");
        report();
    }
}
