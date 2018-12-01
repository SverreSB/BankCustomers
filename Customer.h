/*
*Title Customer.h
*Abstract customer class defining functions and structuring customer object. 
*Author Sverre Broen
*ID 5555
*Date 18/09/2018
*/

using namespace std;


class Customer{

    public: 
        bool setCustomer(int newSsn, string newName, string newSurname);
        bool setAccount_checking(int newAccountNumber_checking, int newAccountType_checking, double newBalance_checking);
        bool setAccount_saving(int newAccountNumber_saving, int newAccountType_saving, double newBalance_saving);
        bool addAmount(double amount, int &type);
        bool withdrawAmount(double amount, int &type);
        bool deleteAccountInformation(int &type);
        
        void displayCustomer();
        void displayAccount(int type);
        void displayAccounts();
        
        void getCustomerInformation();
        void getDetailedCustomerInformation();
        void getCheckingInformation();
        void getSavingInformation();
        
        
        
        //accessors
        string getName();
        string getSurname();
        int getSsn();
        int getAccountNumber_checking();
        int getAccountNumber_saving(); 
        int getAccountType_checking();
        int getAccountType_saving(); 
        double getBalance_checking();
        double getBalance_saving();
    
    private:
        int ssn;
        string name;
        string surname;
        int accountNumber_checking;
        int accountNumber_saving;
        int accountType_checking = -1;
        int accountType_saving = -1;
        double balance_checking; 
        double balance_saving;
};