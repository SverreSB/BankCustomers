/*
*Title driver.cpp
*Abstract 
    Bank application that can store customer’s information for a bank using pointer array 
    Driver class is holding functions for reading data and storing the data in pointer array
    Also holds functions for closing account, displaying customer information with searching 
    for customers using ssn, lastname and account number,
    displaying bank information with amount of customers and accounts,
    transfer money from one account to another, and displaying every customer.
*Author Sverre Broen
*ID 5555
*Date 18/09/2018
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip> 


#include "Customer.h"
using namespace std;


const int CUSTOMER_SIZE = 20;

void runOptions(Customer * custPtr[], int option);

bool readData(Customer * custPtr[], string &file);

void bankInfo(Customer * ptr[]);

void transferMoney(Customer * ptr[], int &source, int &destination, double &amount);

void closeAccount(Customer * ptr[], int accountNumber, int ssn, int accountType);


//Functions returning datatype values
int customerIndex(Customer * ptr[], int &ssn, string &fName, string &lName);
int indexUsingSsn(Customer * ptr[], int &ssn);
int indexUsingAccountNr(Customer * ptr[], int &number);
int amountAccounts(Customer * ptr[]);
int amountCustomers(Customer * ptr[]);
double totalBalance(Customer * ptr[]);
int findAccountType(Customer * ptr[], int accountNumber);


//Verifying that values is not existing
bool existingAccount(Customer * ptr[], int &number);
bool existingAccountType(Customer * ptr[], int &type, int &ssn);
bool ssnNotMatching(Customer * ptr[], int &ssn, string &fName, string &lName);
bool sameAccountHolder(Customer * ptr[], int &accountNumb1, int &accountNumb2);
bool hasAccount(Customer * ptr[], int index);
bool isCustomer(Customer * ptr[], int ssn);
bool existingCustomers(Customer * ptr[]);
bool isCustomerFull(Customer * ptr[]);


//Displays
void displayMenu();
void displayCustomers(Customer * ptr[], int prevIndex, int prevMin);
void displayDetailedCustomers(Customer * ptr[], int prevIndex, int prevMin);
void displayCheckingAccounts(Customer * ptr[], int prevIndex, int prevMin);
void displaySavingAccounts(Customer * ptr[], int prevIndex, int prevMin);
void successfulTransfer(Customer * ptr[], int sourceAccount, int destinationAccount);
void precision(double amount);

void findByLastName(Customer * ptr[], string lastName);

int main()
{
    int option;
    const int CUSTOMER_SIZE = 20;
    Customer * custPtr[CUSTOMER_SIZE];
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        custPtr[i] = nullptr;
    }
    
    runOptions(custPtr, option);
    
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        custPtr[i] = nullptr;
    }
    
    return 0;
    
}

//Recursive function that prompst user for input 1-7. 
void runOptions(Customer * custPtr[], int option)
{
    
    switch(option)
    {
        //Read data
        case 1:
            {
                string fileName;
                cout << "Enter file name: ";
                //Add cin to not have hardcoded values
                cin >> fileName;
                readData(custPtr, fileName);
            }
            break;
            
        case 2:
            {   
                int accNumber;
                int ssn;

                cout << "Enter AccountNumber: ";
                cin >> accNumber;
                if(!existingAccount(custPtr, accNumber))
                {
                    cout << "Incorrect account number." << endl;
                    break;
                }
                
                cout << "Enter Customer SSN: ";
                cin >> ssn;
                if(!isCustomer(custPtr, ssn))
                {
                    cout << "Incorrect SSN" << endl;
                    break;
                }
                
                int accType = findAccountType(custPtr, accNumber);
                if(accType != -1)
                {
                    closeAccount(custPtr, accNumber, ssn, accType);
                }
                
            }
            
            break;
            
        case 3:
            {
                int choice;
                int index;
                
                cout << "SSN(1)/Last Name(2)/Account Number(3): ";
                cin >> choice;
                
                if(choice == 1)
                {
                    int ssn;
                    
                    cout << "Enter SSN: ";
                    cin >> ssn;
                    index = indexUsingSsn(custPtr, ssn);
                    if(index == -1)
                    {
                        cout << "No customer with the SSN." << endl;
                        break;
                    }
                    
                    custPtr[index] -> displayAccounts();
                    
                }
                
                else if(choice == 2)
                {
                    string name;
                    cout << "Enter last name: ";
                    cin >> name;
                    findByLastName(custPtr, name);
                }
                
                else if(choice == 3)
                {
                    int accNumber;
                    int type;
                    cout << "Enter account number: ";
                    cin >> accNumber; 
                    if(!existingAccount(custPtr, accNumber))
                    {
                        cout << "No customer with that account number" << endl;
                        break;
                    }
                    
                    type = findAccountType(custPtr, accNumber);
                    index = indexUsingAccountNr(custPtr, accNumber);
                    if(custPtr[index] != nullptr)
                    {
                        custPtr[index] -> displayAccount(type);
                    }
                    
                }
                
            }
            break;
            
        case 4:
            bankInfo(custPtr);
            break;
            
        case 5:
            {
                int source;
                int destination;
                double amount;
                
                cout << "Source Account: ";
                cin >> source;
                
                cout << "Destination Account: ";
                cin >> destination;
                
                cout << "Money Account: ";
                cin >> amount;
                
                transferMoney(custPtr, source, destination, amount);
                
                break;
            }
            
            
        case 6: 
            if(existingCustomers(custPtr))
            {
                cout << "========== Customer List ==========" << endl;
                //recursive function for printing customers in acsending order
                displayCustomers(custPtr, -1, -1);
                cout << "===================================" << endl;
            }
            else
            {
                cout << "No customers to display" << endl;
            }
            
            break;
        
        
        case 7:
            cout << "Bye." << endl;
            return;
        
        default:
            break;
        
            
    }
    
    displayMenu();
    cin >> option;
    runOptions(custPtr, option);
}

//Function for reading in data and sotring the data in pointer array. 
bool readData(Customer * custPtr[], string &file)
{
    int size;
    
    int ssn;
    string name;
    string surname;
    int accountNumber;
    int accountType;
    double balance;
    
    
    ifstream infile(file);
    infile >> size; 
    cout << "Read data...." << endl;
    for(int i = 0; i < size; i++)
    {
        infile >> ssn;
        infile >> name;
        infile >> surname;
        infile >> accountNumber;
        infile >> accountType;
        infile >> balance; 
        
        
        if(ssnNotMatching(custPtr, ssn, name, surname))
        {
            cout << "Account Creation Failed – A customer with SSN " << ssn << " already exists." << endl;
        }

        
        else if(existingAccount(custPtr, accountNumber))
        {
            cout << "Account Creation Failed – Account number " << accountNumber << " already exists." << endl;

        }
        
        else if(existingAccountType(custPtr, accountType, ssn))
        {
            if(accountType == 1)
            {
                cout << "Account Creation Failed – " << name << " " << surname << " can't have two checking accounts." << endl;
            }
            else if(accountType == 2)
            {
                cout << "Account Creation Failed – " << name << " " << surname << " can't have two saving accounts." << endl;
            }
            else
            {
                cout << "Account Creation Failed – Account number " << accountType << " is not an option." << endl;
            }
            
        }
        
        else if(customerIndex(custPtr, ssn, name, surname) != -1)
        {
            if(existingAccountType(custPtr, accountType, ssn))
            {
                if(accountType == 1)
                {
                    cout << name << " " << surname << " can't have two checking accounts." << endl;
                }
                else if(accountType == 2)
                {
                    cout << name << " " << surname << " can't have two saving accounts." << endl;
                }
                else
                {
                    cout << "Account Creation Failed – Account number " << accountType << " is not an option." << endl;
                }
            }
            
            else{
                int index = customerIndex(custPtr, ssn, name, surname);
                if(accountType == 1)
                {
                    custPtr[index] -> setAccount_checking(accountNumber, accountType, balance);
                }
                else if(accountType == 2)
                {
                    custPtr[index] -> setAccount_saving(accountNumber, accountType, balance);
                }
            }
            
            
        }
        else{
            if(isCustomerFull(custPtr))
            {
                cout << "Customer creation failed - too many customers." << endl;
            }
            else
            {
                for(int j = 0; j < CUSTOMER_SIZE; j++)
                {
                    if(custPtr[j] == nullptr)
                    {
                        if(accountType == 1)
                        {
                            custPtr[j] = new Customer; 
                            custPtr[j] -> setCustomer(ssn, name, surname);
                            custPtr[j] -> setAccount_checking(accountNumber, accountType, balance);
                            break;
                        }
                        
                        else if(accountType == 2)
                        {
                            custPtr[j] = new Customer; 
                            custPtr[j] -> setCustomer(ssn, name, surname);
                            custPtr[j] -> setAccount_saving(accountNumber, accountType, balance);
                            break;
                        }
                        else
                        {
                            cout << "Not valid account type." << endl;
                            break;
                        }
                    }
                }
            }
        }
        
    }
    cout << "Done." << endl; 
}

//Function for printing out every account and customer.
//Includes total balance and total amount of accounts and customers
void bankInfo(Customer * ptr[])
{
    cout << "Number of accounts: " << amountAccounts(ptr) << endl;
    
    //Calling recursive function to print out every account in acsending order on account numbers
    displayCheckingAccounts(ptr, -1, -1);
    displaySavingAccounts(ptr, -1, -1);
    
    cout << endl;
    
    cout << "Number of customers: " << amountCustomers(ptr) << endl;
    
    displayDetailedCustomers(ptr, -1, -1);
    
    cout << endl;
    
    cout << "Total balance: $" << setprecision(2)  << fixed << totalBalance(ptr) << endl;
    
}

//Function for tranfering money from one account to another
//If account holder for source and destination is different, than it is a tranfer fee of $5
void transferMoney(Customer * ptr[], int &source, int &destination, double &amount)
{
    int checking = 1;
    int saving = 2;
        
    if(!existingAccount(ptr, source) || !existingAccount(ptr, destination))
    {
        cout << "Transfer Fail – Incorrect account number" << endl;
        return;
    }
    
    if(sameAccountHolder(ptr, source, destination))
    {
        int index = indexUsingAccountNr(ptr, source);
        
        if((ptr[index]->getAccountNumber_checking() == source) && (ptr[index] -> getBalance_checking() < amount) && (index != -1))
        {
            cout << "Transfer Fail – Insufficient amount." << endl;
            return;
        }
        else if((ptr[index]->getAccountNumber_saving() == source) && (ptr[index] -> getBalance_saving() < amount) && (index != -1))
        {
            cout << "Transfer Fail – Insufficient amount." << endl;
            return;
        }
    }
    
    else
    {
        int index = indexUsingAccountNr(ptr, source);
        
        if((ptr[index]->getAccountNumber_checking() == source) && (ptr[index] -> getBalance_checking() < (amount + 5)) && (index != -1))
        {
            cout << "Transfer Fail – Insufficient amount." << endl;
            return;
        }
        else if(ptr[index]->getAccountNumber_saving() == source && ptr[index] -> getBalance_saving() < (amount + 5) && index != -1)
        {
            cout << "Transfer Fail – Insufficient amount." << endl;
            return;
        }
    }
    
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        
        if(ptr[i] != nullptr)
        {
            //If/else if to determin if source account is savings or checking account
            //if source is checking account
            if(ptr[i] -> getAccountNumber_checking() == source)
            {
               for(int j = 0; j < CUSTOMER_SIZE; j++)
               {
                   if(ptr[j] != nullptr)
                   {
                       //If/else if to determin if destination account is savings or checking account
                       //Don't have to check if ssn is equal, since customer can't hold two checking accounts.
                       if(ptr[j] -> getAccountNumber_checking() == destination)
                       {
                           ptr[j] -> addAmount(amount, checking);
                           ptr[i] -> withdrawAmount(amount + 5, checking);
                           successfulTransfer(ptr, source, destination);
                       }
                       
                       //else if account number is of type savings account
                       else if(ptr[j] -> getAccountNumber_saving() == destination)
                       {
                           //If account holder is same person, then the tranfer fee is not added
                           if(ptr[j] -> getSsn() == ptr[i] -> getSsn())
                           {
                               ptr[j] -> addAmount(amount, saving);
                               ptr[i] -> withdrawAmount(amount, checking);
                               successfulTransfer(ptr, source, destination);
                           }
                           
                           else
                           {
                               ptr[j] -> addAmount(amount, saving);
                               ptr[i] -> withdrawAmount(amount +5, checking);
                               successfulTransfer(ptr, source, destination);
                           }
                       }
                   }
               }
            }
            
            //else if source is saving account
            else if(ptr[i] -> getAccountNumber_saving() == source)
            {
                for(int j = 0; j < CUSTOMER_SIZE; j++)
                {
                    if(ptr[j] != nullptr)
                    {
                        //If/else if to determin if destination account is savings or checking account
                        //If destination is checking account
                        if(ptr[j] -> getAccountNumber_checking() == destination)
                        {
                            //If source and destination account is same account holder
                            if(ptr[j] -> getSsn() == ptr[i] -> getSsn())
                            {
                                ptr[j] -> addAmount(amount, checking);
                                ptr[i] -> withdrawAmount(amount, saving);
                                successfulTransfer(ptr, source, destination);
                                
                            }
                            else
                            {
                                ptr[j] -> addAmount(amount, checking);
                                ptr[i] -> withdrawAmount(amount + 5, saving);
                                successfulTransfer(ptr, source, destination);
                            }
                        }
                        
                        //else if destination is saving account
                        //Not checking if ssn is the same, since both accounts is saving accounts
                        else if(ptr[j] -> getAccountNumber_saving() == destination)
                        {
                            ptr[j] -> addAmount(amount, saving);
                            ptr[i] -> withdrawAmount(amount + 5, saving);
                            successfulTransfer(ptr, source, destination);
                        }
                    }
                }
            }
        }
    }
}

void closeAccount(Customer * ptr[], int accountNumber, int ssn, int accountType)
{
    int index = indexUsingAccountNr(ptr, accountNumber);
    
    
    if(index != -1)
    {
        
        ptr[index] -> deleteAccountInformation(accountType);
    }
    
    
    
    if(!hasAccount(ptr, index))
    {
        cout << "Customer " << ptr[index] -> getName() << " " << ptr[index] -> getSurname();
        cout << " is also deleted." << endl;
        ptr[index] = nullptr;
    }
    cout << endl;
}

//Function for checking if a accountnumber is in use or not
bool existingAccount(Customer * ptr[], int &number)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountNumber_checking() == number || ptr[i] -> getAccountNumber_saving() == number)
            {
                return true; 
            }
        }
    }
    return false; 
}

//Function checking if account type is already createt for customer object
bool existingAccountType(Customer * ptr[], int &type, int &ssn)
{
    
    if(type == 1 || type == 2)
    {
        for(int i = 0; i < CUSTOMER_SIZE; i++)
        {
            if(ptr[i] != nullptr)
            {
                if(type == 1)
                {
                    if(ptr[i] -> getAccountType_checking() != -1 && ptr[i] -> getSsn() == ssn)
                    {
                        return true;
                    }
                }
                
                else
                {
                    if(ptr[i] -> getAccountType_saving() != -1 && ptr[i] -> getSsn() == ssn)
                    {
                        return true;
                    }
                }
                
            }
        }
    }
    return false; 
}

//Function for checking if ssn, name and surname given by file matches each other
bool ssnNotMatching(Customer * ptr[], int &ssn, string &fName, string &lName)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSsn() == ssn && (ptr[i] -> getName() != fName && ptr[i] -> getSurname() != lName))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool sameAccountHolder(Customer * ptr[], int &accountNumb1, int &accountNumb2)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountNumber_checking() == accountNumb1 || ptr[i] -> getAccountNumber_saving() == accountNumb1)
            {
                for(int j = 0; j < CUSTOMER_SIZE; j++)
                {
                    if(ptr[j] != nullptr)
                    {
                        if(ptr[j] -> getAccountNumber_checking() == accountNumb2 || ptr[j] -> getAccountNumber_saving() == accountNumb2)
                        {
                            if(ptr[i] -> getSsn() == ptr[j] -> getSsn())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

bool hasAccount(Customer * ptr[], int index)
{
    if(ptr[index] != nullptr)
    {
        if((ptr[index] -> getAccountType_checking() != -1) || (ptr[index] -> getAccountType_saving() != -1))
        {
            return true;
        }
    }
    return false;
}

bool isCustomer(Customer * ptr[], int ssn)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSsn() == ssn)
            {
                return true;
            }
        }
    }
    return false;
}

bool existingCustomers(Customer * ptr[])
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            return true;
        }
    }
    
    return false;
}

bool isCustomerFull(Customer * ptr[])
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] == nullptr)
        {
            return false;
        }
    }
    return true;
}

//Function for checking if customer object exist. 
//if customer exists, then the fiunction returns the index of the object in pointer array
int customerIndex(Customer * ptr[], int &ssn, string &fName, string &lName)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr){
            if(ptr[i] -> getSsn() == ssn && (ptr[i] -> getName() == fName && ptr[i] -> getSurname() == lName))
            {
                return i;
            }
        }
    }
    return -1;
}

int indexUsingSsn(Customer * ptr[], int &ssn)
{
    int index = 0;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSsn() == ssn)
            {
                return i;
            }
        }
    }
    return -1;
}

int indexUsingAccountNr(Customer * ptr[], int &number)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountNumber_checking() == number || ptr[i] -> getAccountNumber_saving() == number)
            {
                return i;
            }
        }
    }
    
    return -1;
}

//Function returning amount of customers in pointer array
int amountCustomers(Customer * ptr[])
{
    int counter = 0;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            counter++;
        }
    }
    return counter;
}

//Function return amount of accounts in pointer array
int amountAccounts(Customer * ptr[])
{
    int accounter = 0; //account counter;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr){
            if(ptr[i] -> getAccountType_checking() != -1)
            {
                accounter++;
            }
            if(ptr[i] -> getAccountType_saving() != -1)
            {
                accounter++;
            }
        }
    } 
    
    return accounter;
}

int findAccountType(Customer * ptr[], int accountNumber)
{
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountNumber_checking() == accountNumber)
            {
                return 1;    
            }
            else if(ptr[i] -> getAccountNumber_saving() == accountNumber)
            {
                return 2;
            }
        }
    }
    
    return -1;
}

double totalBalance(Customer * ptr[])
{
    double balance = 0; 
    
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountType_checking() != -1)
            {
                balance += ptr[i] -> getBalance_checking();
            }
            if(ptr[i] -> getAccountType_saving() != -1)
            {
                balance += ptr[i] -> getBalance_saving();
            }
        }
    }
    
    return balance; 
}

//Function for displaying menu options to user
void displayMenu()
{
    cout << "Select your choice: \n";
    cout << "    1.  Read customer data file \n    2.  Close an account \n";
    cout << "    3.  Customer Info \n    4.  Bank Info \n    5.  Transfer Money \n";
    cout << "    6.  Customer List \n    7.  Exit \n";
    cout << endl;  
}

//Recursive function for printing customers. 
//Stops when objects ssn is no longer less than min, is not greater than prevMin and i is not equal to prevIndex.
void displayCustomers(Customer * ptr[], int prevIndex, int prevMin)
{

    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSsn() < min && ptr[i] -> getSsn() > prevMin && i != prevIndex)
            {
                min = ptr[i] -> getSsn();
                minIndex = i;
            }
        }
    }
    
    if(minIndex == -1)
    {
        return;
    }
    
    ptr[minIndex] -> getCustomerInformation();

    displayCustomers(ptr, minIndex, min);
    
}

void displayDetailedCustomers(Customer * ptr[], int prevIndex, int prevMin)
{

    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSsn() < min && ptr[i] -> getSsn() > prevMin && i != prevIndex)
            {
                min = ptr[i] -> getSsn();
                minIndex = i;
            }
        }
    }
    
    if(minIndex == -1)
    {
        return;
    }
    
    
    ptr[minIndex] -> getDetailedCustomerInformation();
    
    displayDetailedCustomers(ptr, minIndex, min);
}

//Recursive function for printing out checking accounts in acsending order
void displayCheckingAccounts(Customer * ptr[], int prevIndex, int prevMin)
{
    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] ->getAccountType_checking() != -1)
            {
                if(ptr[i] -> getAccountNumber_checking() < min && ptr[i] -> getAccountNumber_checking() > prevMin && i != prevIndex)
                {
                    min = ptr[i] -> getAccountNumber_checking();
                    minIndex = i;
                }                
            }
        }
    }
    
    if(minIndex == -1)
    {
        return;
    }
    
    ptr[minIndex] -> getCheckingInformation();
    
    displayCheckingAccounts(ptr, minIndex, min);
}

//Recursive function for printing out saving accounts in acsending order
void displaySavingAccounts(Customer * ptr[], int prevIndex, int prevMin)
{
    int min = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] ->getAccountType_saving() != -1){
                if(ptr[i] -> getAccountNumber_saving() < min && ptr[i] -> getAccountNumber_saving() > prevMin && i != prevIndex)
                {
                    min = ptr[i] -> getAccountNumber_saving();
                    minIndex = i;
                }
            }
        }
    }
    
    if(minIndex == -1)
    {
        return;
    }

    ptr[minIndex] -> getSavingInformation();
    
    displaySavingAccounts(ptr, minIndex, min);
}

void precision(double amount)
{
    cout << setprecision(2)  << fixed << amount;
}

void successfulTransfer(Customer * ptr[], int sourceAccount, int destinationAccount)
{
    cout << "Transfer Succeed." << "\n";
    cout << "New Balance" << endl;
    
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getAccountNumber_checking() == sourceAccount)
            {
                cout << "   " << ptr[i] -> getAccountNumber_checking() << ": $";
                precision(ptr[i] -> getBalance_checking());
                cout << endl;
            }
            else if(ptr[i] -> getAccountNumber_saving() == sourceAccount)
            {
                cout << "   " << ptr[i] -> getAccountNumber_saving() << ": $"; 
                precision(ptr[i] -> getBalance_saving());
                cout << endl;
            }
            
            if(ptr[i] -> getAccountNumber_checking() == destinationAccount)
            {
                cout << "   " << ptr[i] -> getAccountNumber_checking() << ": $";
                precision(ptr[i] -> getBalance_checking());
                cout << endl;
            }
            else if(ptr[i] -> getAccountNumber_saving() == destinationAccount)
            {
                cout << "   " << ptr[i] -> getAccountNumber_saving() << ": $"; 
                precision(ptr[i] -> getBalance_saving());
                cout << endl;
            }
        }
    }
}

void findByLastName(Customer * ptr[], string lastName)
{
    int found = false;
    for(int i = 0; i < CUSTOMER_SIZE; i++)
    {
        if(ptr[i] != nullptr)
        {
            if(ptr[i] -> getSurname() == lastName)
            {
                ptr[i] -> displayAccounts();
                found = true;
            }
        }
    }
    if(!found)
    {
        cout << "No customer with the last name." << endl;
    }
}



