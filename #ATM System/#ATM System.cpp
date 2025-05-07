#include <iostream>
#include<string>
#include<cmath>
#include<vector>
#include<cctype>
#include<fstream>
#include <iomanip>
#include "Mylib.h"
using namespace std;
using namespace Mylib;

enum enAtmOp { eQuickWithdraw = 1, eNormalWithdraw = 2,eDeposit = 3, eCheckBalance = 4, eLogout= 5 };

string ClientsFileName = "ClientsData.txt";

void Login();
void ATMMainMenueScreen();
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double Balance;


};

stClient CurrentClient;
string ConvertRecordToLine(stClient Client, string delim = "#//#")
{
	string ClientString = "";

	ClientString = Client.AccountNumber + delim;
	ClientString += Client.PinCode + delim;
	ClientString += Client.Name + delim;
	ClientString += Client.Phone + delim;
	ClientString += to_string(Client.Balance);
	return ClientString;

}

stClient ConvertLineToRecord(string sClient, string delim = "#//#")
{
	stClient Client;
	vector<string> vString = Split(sClient, delim);
	if (vString.size() == 5)
	{
		Client.AccountNumber = vString[0];
		Client.PinCode = vString[1];
		Client.Name = vString[2];
		Client.Phone = vString[3];
		Client.Balance = stod(vString[4]);
	}
	return Client;
}

vector <string>ClientStrings(string FileName)
{
	vector<string>vStrings;

	return vStrings;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
	vector<stClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		stClient Client;
		string Line;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}

		MyFile.close();
	}

	return vClient;
}
//-----------------------------------------------------------------------

bool FindClientByAccountNumber(string AccountNumber, stClient& Client)
{

	vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);


	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}
	return false;

}



short ReadAtmMenuOption()
{
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 5]?  ";
	cin >> Choice;
	return Choice;
}

// Transaction part 

void UpdateClientBalance(string AccountNumber, double Balance, vector<stClient>& vClient)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out);
	if (MyFile.is_open())
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.Balance = Balance;
			}

			MyFile << ConvertRecordToLine(C) << endl;

		}
		//this line of code is to update the data 
		vClient = LoadClientsDataFromFile(ClientsFileName);
		MyFile.close();
	}
}
//deposit part
void DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, stClient& Client, vector<stClient>& vClient)
{
	char AreYouSureChoice;

	cout << "\nAre you sure you want perform this transaction? y/n ? ";
	cin >> AreYouSureChoice;
	if (toupper(AreYouSureChoice) == 'Y')
	{
		Client.Balance += Amount;
		UpdateClientBalance(AccountNumber, Client.Balance, vClient);
		cout << "Done Successfully , the new balance is : " << Client.Balance << endl;

	}
}

void DepositProcess()
{
	vector<stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	int DepositAmount = 0;
	
	
		cout << "Please enter Deposit amount? ";
		cin >> DepositAmount;

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount , CurrentClient, vClient);

}

void ShowDepositScreen()
{
	cout << "--------------------------------------\n";
	cout << "          Deposit Screen\n";
	cout << "--------------------------------------\n\n";
	DepositProcess();
}

int GetQuickdrawAmount(short Choice)
{
	switch (Choice)
	{
	case 1:
	{
		return 20;
	}
	case 2:
	{
		return 50;
	}
	case 3:
	{
		return 100;

	}
	case 4:
	{
		return 200;

	}
	case 5:
	{
		return 400;

	}
	case 6:
	{
		return 600;
	}
	case 7:
	{
		return 800;

	}
	case 8:
	{
		return 1000;
	}
	}

}

//withdraw part

short ReadQuickWithdrawChoice()
{
	short Choice = 0;
	do
	{
		cout << "Choose what to withdraw from [1] to [8] ? ";
		cin >> Choice;
	} while (!(Choice >= 1 && Choice <= 9));
	return Choice;
}

void QuickdrawProcess()
{
	vector<stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	
	
	short WithdrawAmount = GetQuickdrawAmount(ReadQuickWithdrawChoice());
	
	while (WithdrawAmount > CurrentClient.Balance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to : " << CurrentClient.Balance << endl;
		WithdrawAmount = GetQuickdrawAmount(ReadQuickWithdrawChoice());
	}
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount*-1, CurrentClient, vClient);


}
void QuickWithdrawScreen()
{
	cout << "=======================================\n";
	cout << "         Quick Withdraw Screen\n";
	cout << "=======================================\n";
	cout << "         [1] 20           [2] 50\n";
	cout << "         [3] 100          [4] 200\n";
	cout << "         [5] 400          [6] 600\n";
	cout << "         [7] 800          [8] 1000\n";
	cout << "         [9] Exit \n";
	cout << "=======================================\n";
	cout << "Your Balance is : " << CurrentClient.Balance << endl;
	QuickdrawProcess();
	

}

void NormalWithdrawProcess()
{
	vector<stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	int WithdrawAmount = 0;
		do
		{
		  cout << "Please enter withdraw amount multiple of 5 's ? ";
		  cin >> WithdrawAmount;

		}while (WithdrawAmount % 5 != 0);


		while (WithdrawAmount > CurrentClient.Balance)
		{
			cout << "Amount Exceeds the balance, you can withdraw up to : " << CurrentClient.Balance << endl;
			cout << "\n\nPlease enter withdraw amount? ";
			cin >> WithdrawAmount;
		}

		DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, CurrentClient, vClient);
	
}

void NormalWithdrawScreen()
{
	cout << "--------------------------------------\n";
	cout << "         Normal Withdraw Screen\n";
	cout << "--------------------------------------\n";
	NormalWithdrawProcess();
}

void CheckBalanceScreen()
{
	cout << "===========================================\n";
	cout << "          Check Balance Screen\n ";
    cout << "===========================================\n";
	cout<<"Your Balance is "<< CurrentClient.Balance<<endl;


}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to ATM Main Menue...";
	system("pause>0");
	ATMMainMenueScreen();

}

void PerformAtmMenuOption(enAtmOp AtmOp)
{
	switch (AtmOp)
	{
	case eQuickWithdraw:
	{
		system("cls");
		QuickWithdrawScreen();
		GoBackToMainMenu();
		break;
	}
	case eNormalWithdraw:
	{
		system("cls");
		NormalWithdrawScreen();
		GoBackToMainMenu();
		break;
	}
	case eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenu();
		break;
	}
	case eCheckBalance:
	{
		system("cls");
		CheckBalanceScreen();
		GoBackToMainMenu();
		break;
	}
	case eLogout:
	{
		system("cls");
		Login();
		break;
	}

	}
}

void ATMMainMenueScreen()
{
	system("cls");
	cout << "==========================================================\n";
	cout << "               ATM Main Menue Screen\n";
	cout << "==========================================================\n";
    cout << "                 [1] Quick Withdraw.\n";
	cout << "                 [2] Normal Withdraw.\n";
	cout << "                 [3] Deposit.\n";
	cout << "                 [4] Check Balance.\n";
	cout << "                 [5] Logout.\n";
	cout << "==========================================================\n";
	PerformAtmMenuOption((enAtmOp)ReadAtmMenuOption());
}

void ReadAccountNumberAndPinCode(string& AccountNumber, string& PinCode)
{
	cout << "Enter Account Nubmer? ";
	getline(cin >> ws, AccountNumber);
	cout << "Enter Pin? ";
	getline(cin, PinCode);

}

bool FindClientByAccountNumberAndPinCode(string AccountNubmerToFind, string PinCode, stClient& GetClient)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	for (stClient & C:vClients)
	{
		if (C.AccountNumber == AccountNubmerToFind && C.PinCode == PinCode)
		{
			GetClient = C;
			return true;
		}
	}

	return false;
}

void Login()
{

	string UserName, Password;
	

	bool FindResult = true;
	do
	{
		system("cls");
		cout << "--------------------------------------\n";
		cout << "            Login Screen \n";
		cout << "--------------------------------------\n";

		if (!FindResult)
			cout << "Invalid AccountnUmber/PinCode!\n";

		ReadAccountNumberAndPinCode(UserName, Password);

		FindResult = FindClientByAccountNumberAndPinCode(UserName, Password, CurrentClient);

	} while (FindResult == false);
	
	system("cls");
	ATMMainMenueScreen();
}

int main()
{
	Login();
	system("pause>0");
	return 0;
}

