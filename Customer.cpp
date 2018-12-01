/*
*Title Customer.cpp
*Abstract customer class holding every function for creating customer objects
*Author Sverre Broen
*ID 5555
*Date 18/09/2018
*/


#include <iostream>
#include <iomanip> 
#include "Customer.h"
using namespace std;




bool Customer::setCustomer(int newSsn, string newName, string newSurname)
{
    ssn = newSsn;
    name = newName;
    surname = newSurname;
    return true; 
}

bool Customer::setAccount_checking(int newAccountNumber_checking, int newAccountType_checking, double newBalance_checking)
{
    if(accountType_checking != -1)
    {
        cout << "Error: Account type already exists" << endl;
        return false;
    }
    accountNumber_checking = newAccountNumber_checking;
    accountType_checking = newAccountType_checking;
    balance_checking = newBalance_checking;
    return true;
}

bool Customer::setAccount_saving(int newAccountNumber_saving, int newAccountType_saving, double newBalance_saving)
{
    if(accountType_saving != -1)
    {
        cout << "Error: Account type already exists" << endl;
        return false;
    }
    accountNumber_saving = newAccountNumber_saving;
    accountType_saving = newAccountType_saving;
    balance_saving = newBalance_saving;
    return true;
    
}

//Function for adding amount to 
bool Customer::addAmount(double amount, int &type)
{
    if(type == 1)
    {
        balance_checking += amount; 
    }
    
    else if(type == 2)
    {
        balance_saving += amount;
    }
}

bool Customer::withdrawAmount(double amount, int &type)
{
        if(type == 1)
    {
        balance_checking -= amount; 
    }
    
    else if(type == 2)
    {
        balance_saving -= amount;
    }
}

bool Customer::deleteAccountInformation(int &type)
{
    if(type == 1 || type == 2)
    {
        cout << "Account closed" << endl;
        displayAccount(type);
        if(type == 1)
        {
            accountNumber_checking = -1;
            accountType_checking = -1;
            balance_checking = 0; 
        }
        else if(type == 2)
        {
            accountNumber_saving = -1;
            accountType_saving = -1;
            balance_saving = 0; 
        }
        
    }
}

void Customer::displayCustomer()
{
    cout << "SSN: " << ssn << endl;
    cout << "Name: " << name << endl;
    cout << endl;
}

void Customer::displayAccount(int type)
{
    cout << "   " << "Name: " << name << " " << surname << "\n";
    if(type == 1)
    {
        cout << "   " << "Account Number: " << accountNumber_checking << "\n";
        cout << "   " << "Account Type: Checking" << "\n";
        cout << "   " << "Balance: $" << setprecision(2) << fixed <<balance_checking << "\n";
    }
    
    else if(type == 2)
    {
        cout << "   " << "Account Number: " << accountNumber_saving << "\n";
        cout << "   " << "Account Type: Saving" << "\n";
        cout << "   " << "Balance: $" << setprecision(2) << fixed <<balance_saving<< "\n";
    
    }
    cout << endl;
}

void Customer::displayAccounts()
{
    if(accountType_checking != -1)
    {
        cout << "   " << "Name: " << name << " " << surname << "\n";
        cout << "   " << "Account Number: " << accountNumber_checking << "\n";
        cout << "   " << "Account Type: Checking" << "\n";
        cout << "   " << "Balance: $" << setprecision(2) << fixed <<balance_checking << "\n";
    }
    cout << endl;
    
    if(accountType_saving != -1)
    {
        cout << "   " << "Name: " << name << " " << surname << "\n";
        cout << "   " << "Account Number: " << accountNumber_saving << "\n";
        cout << "   " << "Account Type: Saving" << "\n";
        cout << "   " << "Balance: $" << setprecision(2) << fixed <<balance_saving<< "\n";
    }
    
    cout << endl;
}

void Customer::getCustomerInformation()
{
    cout << "   " << "SSN: " << ssn << "\n";
    cout << "   " << "Name: " << name << " " << surname << "\n";
    cout << endl;
}

void Customer::getDetailedCustomerInformation()
{
    bool addComma = false;
    cout << "   " << "Name: " << name << " " << surname << ": ";
    cout << ssn << " - ";
    if(accountType_checking != -1)
    {
        cout << accountNumber_checking << "($" << balance_checking << ")";
        addComma = true;
    }
    
    if(accountType_saving != -1)
    {
        if(addComma)
        {
            cout << ", ";
        }
        cout << accountNumber_saving << "($" << balance_saving << ")";
    }
    cout << endl;
}

void Customer::getCheckingInformation()
{
    cout << "   " << accountNumber_checking << ": $" << balance_checking << " (checking)" << endl;
}

void Customer::getSavingInformation()
{
    cout << "   " << accountNumber_saving << ": $" << balance_saving << "(saving)" << endl;
}


//Accessord
string Customer::getName()
{
    return name;
}

string Customer::getSurname()
{
    return surname;
}

int Customer::getSsn()
{
    return ssn;
}

int Customer::getAccountNumber_checking()
{
    return accountNumber_checking;
}

int Customer::getAccountNumber_saving()
{
    return accountNumber_saving;
}

int Customer::getAccountType_checking()
{
    return accountType_checking;
}

int Customer::getAccountType_saving()
{
    return accountType_saving;
}

double Customer::getBalance_checking()
{
    return balance_checking;
}

double Customer::getBalance_saving()
{
    return balance_saving;
}