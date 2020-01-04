//
//  main.cpp
//  Bank Management System
//
//  Created by Rockabye Saw on 27/12/2019.
//  Copyright © 2019 Rockabye Saw. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <iomanip>
#include <fstream>

class Account
{
    int acno;
    char name[50];
    int deposit;
    char type;
    
public:
    void create_account(); // function to get data from user
    void show_account() const; // function to show data on screen
    void modify(); // function to add new data
    void dep(int);    // function to accept amount and add to balance amount
    void draw(int);    // function to accept amount and subtract from balance amount
    void report() const;    // function to show data in tabular format
    int retacno() const;    // function to return account number
    int retdeposit() const;    // function to return balance amount
    char rettype() const;    // function to return type of account
};

void Account::create_account()
{
    std::cout << "\nEnter The Account No.: ";
    std::cin >> acno;
    std::cout << "\n\nEnter The Name of The Account Holder: ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    std::cout << "\nEnter Type of The Account (C/S): ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current): ";
    std::cin >> deposit;
    std::cout << "\n\n\nAccout Created ...";
}

void Account::show_account() const
{
    std::cout << "\nAccount No: " << acno;
    std::cout << "\nAccount Holder Name: " << name;
    std::cout << "\nType of Account: " << type;
    std::cout << "\nBalance Amount: " << deposit;
}

void Account::modify()
{
    std::cout << "\nAccount No: " << acno;
    std::cout << "\nModify Account Holder Name: ";
    std::cin.ignore();
    std::cin.getline(name, 50);
    std::cout << "\nModify Type of Account : ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "\nModify Balance amount : ";
    std::cin >> deposit;
}

void Account::dep(int x)
{
    deposit += x;
}

void Account::draw(int x)
{
    deposit -= x;
}

void Account::report() const
{
    std::cout << acno << std::setw(10) <<" "<< name << std::setw(10) <<" " << type << std::setw(6) << deposit << std::endl;
}


int Account::retacno() const
{
    return acno;
}

int Account::retdeposit() const
{
    return deposit;
}

char Account::rettype() const
{
    return type;
}

void write_account();    //function to write record in binary file
void display_sp(int);    //function to display account details given by user
void modify_account(int);    //function to modify record of file
void delete_account(int);    //function to delete record of file
void display_all();        //function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();    //introductory screen function

int main(int argc, const char * argv[])
{
    char ch;
    int num;
    intro();
    do
    {
        system("clear");
        std::cout<<"\n\n\n\tMAIN MENU";
        std::cout<<"\n\n\t01. NEW ACCOUNT";
        std::cout<<"\n\n\t02. DEPOSIT AMOUNT";
        std::cout<<"\n\n\t03. WITHDRAW AMOUNT";
        std::cout<<"\n\n\t04. BALANCE ENQUIRY";
        std::cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        std::cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        std::cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        std::cout<<"\n\n\t08. EXIT";
        std::cout<<"\n\n\tSelect Your Option (1-8) ";
        std::cin>>ch;
        system("clear");
        switch (ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                std::cout << "\n\n\tEnter The Account No. : ";
                std::cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                std::cout << "\n\n\tEnter The Account No. : ";
                std::cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                std::cout << "\n\n\tEnter The Account No. : ";
                std::cin >> num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                std::cout << "\n\n\tEnter The Account No. : ";
                std::cin >> num;
                delete_account(num);
                break;
            case '7':
                std::cout << "\n\n\tEnter The Account No. : ";
                std::cin >> num;
                modify_account(num);
                break;
            case '8':
                std::cout << "\n\n\tThanks for using bank managemnt system";
                break;
            default :
                std::cout << "\a";
        }
        std::cin.ignore();
        std::cin.get();
    }
    while (ch != '8');
    return 0;
}

void write_account()
{
    Account ac;
    std::ofstream outFile;
    outFile.open("account.bin", std::ios::binary|std::ios::app);
    ac.create_account();
    outFile.write((char *)&ac, sizeof(Account));
    outFile.close();
}

void display_sp(int n)
{
    Account ac;
    bool flag = false;
    std::ifstream inFile;
    inFile.open("account.bin", std::ios::binary);
    if(!inFile)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    std::cout << "\nBALANCE DETAILS\n";
    
    while (inFile.read((char *)&ac, sizeof(Account)))
    {
        if(ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    
    inFile.close();
    
    if(flag == false)
        std::cout << "\n\nAccount number does not exist";
}

void modify_account(int n)
{
    Account ac;
    bool found = false;
    std::fstream File;
    File.open("account.bin", std::ios::binary|std::ios::in|std::ios::out);
    if(!File)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read((char *)&ac, sizeof(Account));
        if(ac.retacno() == n)
        {
            ac.show_account();
            std::cout << "\n\nEnter The New Details of Account" << std::endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Account));
            File.seekp(pos, std::ios::cur);
            File.write((char *)&ac, sizeof(Account));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if(found == false)
        std::cout << "\n\n Record Not Found ";
}

void delete_account(int n)
{
    Account ac;
    std::fstream outFile;
    std::ifstream inFile;
    inFile.open("account.bin", std::ios::binary);
    if(!inFile)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("temp.bin", std::ios::binary);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read((char *)&ac, sizeof(Account)))
    {
        if(ac.retacno() != n)
        {
            outFile.write((char *)&ac, sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.bin");
    rename("temp.bin","account.bin");
    std::cout << "\n\n\tRecord Deleted ..";
}

void display_all()
{
    Account ac;
    std::ifstream inFile;
    inFile.open("account.bin", std::ios::binary);
    if(!inFile)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    std::cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    std::cout << "====================================================\n";
    std::cout << "A/c no.      NAME           Type  Balance\n";
    std::cout << "====================================================\n";
    while (inFile.read((char *)&ac, sizeof(Account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    Account ac;
    std::fstream File;
    File.open("account.bin", std::ios::binary|std::ios::in|std::ios::out);
    if(!File)
    {
        std::cout << "File could not be open !! Press any Key...";
        return;
    }
    
    while (!File.eof() && found == false)
    {
        File.read((char *)&ac, sizeof(Account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            
            if(option == 1)
            {
                std::cout << "\n\n\tTO DEPOSITE AMOUNT ";
                std::cout << "\n\nEnter The amount to be deposited: ";
                std::cin >> amt;
                ac.dep(amt);
            }
            
            if (option == 2)
            {
                std::cout << "\n\n\tTO WITHDRAW AMOUNT ";
                std::cout << "\n\nEnter The amount to be withdraw: ";
                std::cin >> amt;
                int bal = ac.retdeposit() - amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    std::cout<<"Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos, std::ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
            std::cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(found == false)
        std::cout << "\n\n Record Not Found ";
}

void intro()
{
    std::cout << "\n\n\n\t  BANK";
    std::cout << "\n\n\tMANAGEMENT";
    std::cout << "\n\n\t  SYSTEM";
    std::cin.get();
}

