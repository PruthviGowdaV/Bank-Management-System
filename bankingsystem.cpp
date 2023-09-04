#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account{
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

public:
    void modify();
    void report() const;
    int retacno() const{
        return account_number;
    }
    void dep(int x){
        Money_Deposit+=x;
    }
    void draw(int x){
        Money_Deposit-=x;
    }
    int retdeposit() const{
        return Money_Deposit;
    }
    void create_account();
    void Display_Account();
    

};
void Bank_Account::report() const{
    cout<<account_number<<setw(12)<<" "<<name<<setw(14)<<type<<setw(16)<<Money_Deposit<<endl;
}

void Bank_Account::modify(){
    cout<<"\t Account Number: "<<account_number<<endl;
    cout<<"\t Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify the type of account: ";
    cin>>type;
    type=toupper(type);
}
void write_account();
void display_details(int);
void delete_account(int);
void display_all();
void Money_deposit_withdraw(int, int);
void modify_account(int);


void Bank_Account::create_account(){
    system("cls");
    cout<<"\t Enter the account number: ";
    cin>>account_number;
    cout<<"\t Enter the name of account holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Enter the type of account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount (>=500 for Saving and >=1000 for Current): ";
    cin>>Money_Deposit;
    cout<<endl;
    cout<<"\t Account Created.....";
    cout<<endl;

}

void Bank_Account::Display_Account(){
    cout<<"\t Bank Account Number : "<<account_number<<endl;
    cout<<"\t Account Holder Name : "<<name<<endl;
    cout<<"\t Type of Account : "<<type<<endl;
    cout<<"\t Balance Ammount : "<<Money_Deposit<<endl;

}

int main(){
    char ch;
    int num;
    do{
    cout<<"\t\t....................................."<<endl;
    cout<<"\t\t| Welcome to Bank Management System |"<<endl;
    cout<<"\t\t....................................."<<endl;
    

    cout<<"\t.....Main Menu....."<<endl;
    cout<<"\t 1. Create Account"<<endl;
    cout<<"\t 2. Deposit Money"<<endl;
    cout<<"\t 3. Withdraw Money"<<endl;
    cout<<"\t 4. Balance Enquiry"<<endl;
    cout<<"\t 5. Account Holder List"<<endl;
    cout<<"\t 6. Close an Account"<<endl;
    cout<<"\t 7. Modify an Account"<<endl;
    cout<<"\t 8. Exit"<<endl;
    cout<<endl;

    cout<<"\t Enter Your Choice (1-8) : ";
    cin>>ch;

    switch(ch){
        case '1':
            write_account();
            break;
        case '2':
            system("cls");
            cout<<"\t Enter the account number: " ;
            cin>>num;
            Money_deposit_withdraw(num, 1);
            break;
            //deposit function
        case '3':
            system("cls");
            cout<<"\t Enter the account number: " ;
            cin>>num;
            Money_deposit_withdraw(num, 2);
            break;
            //withdraw  function
        case '4':
            system("cls");
            cout<<"\t Enter the account number: " ;
            cin>>num;
            display_details(num);
            break; 
            //balance enquiry
        case '5':
            display_all();
            break;
            //Account holder history
        case '6':
            system("cls");
            cout<<"\t Enter the account number: " ;
            cin>>num;
            delete_account(num);
            break;
            //close an account
        case '7':
            system("cls");
            cout<<"\t Enter the account number: " ;
            cin>>num;
            modify_account(num);
            break;
            //modify an account
        case '8':
            cout<<"\t Thanks for using the Bank Management System"<<endl;
            cin>>num;
            break;       
    }
    cin.ignore();
    cin.get();
    }while(ch!='8');
    return 0;

    // Bank_Account B;
    // B.create_account();
    // B.Display_Account();
    // return 0;
}

void write_account()
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int n)
{
    Bank_Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout<<"File could not be opened || Press any key";
        return;
    }
    outFile.open("temp.dat", ios::binary);
    inFile.seekg(0,ios::beg);

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)));
        if(ac.retacno()!=n){
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        }
inFile.close();
outFile.close();
remove("Bank_Account.dat");
cout<<"\t Record has been Deleted"<<endl;
}

void display_details(int n)
{
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout<<"File could not be oppened || Press any key";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)));
    {
         if(ac.retacno()==n){
            ac.Display_Account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"\t Account doesnt exit"<<endl;
    }
    
}

void display_all()
{
    system("cls");
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened || Press any key ";
        return;
    }
    cout<<"\t Bank Account Holders List "<<endl;
    cout<<"______________________________________________________"<<endl;
    cout<<"A/c no.          NAME          TYPE           BALANCE "<<endl;
    cout<<"______________________________________________________"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)));
    {
        ac.report();
    }
    inFile.close();
}

void Money_deposit_withdraw(int n, int option){
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be oppened || Press any key";
        return;
    }
    while(File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(option == 1){
                cout<<"\t Enter the amount to be Deposited: " ;
                cin>>amt;
                ac.dep(amt);
            }
            if(option == 2){
                cout<<"\t Enter the amount to be withdrawn: ";
                cin>>amt;
                int balance = ac.retdeposit() - amt;
                if(balance < 0){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekg(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record not found"<<endl;
        return;
    }
}

void modify_account(int n)
{
	bool found=false;
	Bank_Account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		if(ac.retacno()==n)
		{
			ac.Display_Account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Bank_Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
