#include "person.h"
#include "person.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

void readData(vector<Person> &employees);
void getCompanies(vector<Person> &employees, vector<string> &companyNames);
void printHighestPaid(vector<Person> &employees);
void separateAndSave(vector<Person> &employees, vector<string> &companyNames);


int main(){
    //creating vectors
    vector<Person> employees;
    vector<string> companyNames;

    //call functions
    readData(employees);
    getCompanies(employees, companyNames);
    printHighestPaid(employees);
    separateAndSave(employees, companyNames);

    return 0;

}

void readData(vector<Person> &employees){

    string fName, lName, coName;
    int id;
    float hours, rate;

    ifstream inData;
    inData.open("input.txt", ios::in);
    if (inData){
        cout<<"The file opened successfully.\n";

        Person p;

        do {
            //reads one line of the file at a time to get all the info on each line
            inData>>fName>>lName>>id>>coName>>hours>>rate;
            p.setFirstName(fName);
            p.setLastName(lName);
            p.setEmployeeId(id);
            p.setCompanyName(coName);
            p.setHoursWorked(hours);
            p.setPayRate(rate);
            //push the object to the employees vector after each line in
            //the file is read
            employees.push_back(p);
        }while (!inData.eof()); //while the file is not empty
        cout<<"Done reading the file.\n";
    }
    else{
        cout<<"ERROR: The file could not be opened.\nEnding the program.\n";
    }
    inData.close(); //close the file
}

void getCompanies(vector<Person> &employees, vector<string> &companyNames){
    for (int i=0; i<employees.size()-1; i++){

        string coName=employees.at(i).getCompanyName();

        companyNames.push_back(coName);
    }
}

void printHighestPaid(vector<Person> &employees){
    float highest=0;
    int index=0;
    highest=employees.at(0).totalPay();
    for (int i=0; i<employees.size()-1; i++){
        if (employees.at(i).totalPay()>highest){
            highest=employees.at(i).totalPay();
            index=i;
        }
    }
    cout<<"Highest Paid: "<<employees.at(index).fullName()<<endl;
    cout<<"Employee ID: "<<employees.at(index).getEmployeeId()<<endl;
    cout<<"Employer: "<<employees.at(index).getCompanyName()<<endl;
    cout<<"Total Pay: $"<<fixed<<setprecision(2)<<employees.at(index).totalPay()<<endl;
}

void separateAndSave(vector<Person> &employees, vector<string> &companyNames){
    ofstream outData;
    float companyPay=0;
    for (int i=0; i<companyNames.size()-1;i++){
        string fileName=companyNames.at(i)+".txt";
        outData.open(fileName.c_str(), ios::out);
        if (outData){
            for (int j=0; j<employees.size()-1;j++){
                if (employees.at(j).getCompanyName()==companyNames.at(i)){
                    companyPay+=employees.at(j).totalPay();
                    outData<<left<<
                    setw(20)<<
                    employees.at(j).getFirstName()<<
                    setw(20)<<
                    employees.at(j).getLastName()<<
                    setw(5)<<
                    employees.at(j).getEmployeeId()<<
                    setw(15)<<
                    employees.at(j).getCompanyName()<<"\t"<<
                    fixed<<setprecision(2)<<
                    employees.at(j).totalPay()<<"\n";
                }
            }
        }
        else {
            cout<<"ERROR: Could not open the file. Ending the program."<<endl;
            break;
        }
        outData<<"Total $"<<companyPay<<endl;
        companyPay=0;
        outData.close();
    }

}
