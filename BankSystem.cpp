#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "BankSystem.h"


BankSystem::BankSystem(string i, string fn, string ln)
{
    oneClient = new Client(i, fn, ln);
}

void BankSystem::AddCheckingDialog()
{
    if (oneClient->checking != NULL)
    {
        cout << "The client already has a checking account\n";
        log.push_back("Invalid attempt to overwrite a checking account.");
    }
    else
    {
        float initialBalance;
        cout << "--Enter initial balance: ";
        cin >> initialBalance;
        CheckingAccount* check = new CheckingAccount(initialBalance);
        oneClient->checking = check;
        log.push_back("Checking account successfully created.");
    }
}

void BankSystem::RemoveCheckingDialog()
{
    if (oneClient->checking != NULL)
    {
        CheckingAccount* check = oneClient->checking;
        oneClient->checking = NULL;
        delete check;
        log.push_back("Checking account successfully removed.");
    }
    else
    {
        cout << "The client does not have a checking account\n";
        log.push_back("Invalid attempt to remove a non-existing checking account.");
    }
}

void BankSystem::DepositCheckingDialog()
{
    if (oneClient->checking != NULL)
    {
        float amount;
        cout << "-- Amount to deposit: ";
        cin >> amount;
        oneClient->checking->deposit(amount);
        log.push_back("$" + to_string(amount) + " successfully deposited in checking account.");
    }
    else
    {
        cout << "The client does not have a checking account\n";
        log.push_back("Invalid attempt to deposit in a non-existing checking account.");
    }
}

void BankSystem::WithdrawCheckingDialog()
{
    if (oneClient->checking != NULL)
    {
        float amount;
        cout << "-- Amount to withdraw: ";
        cin >> amount;
        oneClient->checking->withdraw(amount);
        log.push_back("$" + to_string(amount) + " successfully withdrawn from checking account.");
    }
    else
    {
        cout << "The client does not have a checking account\n";
        log.push_back("Invalid attempt to withdraw from a non-existing checking account.");
    }
}

void BankSystem::AddSavingDialog()
{
    if (oneClient->saving != NULL)
    {
        cout << "The client already has a saving account\n";
        log.push_back("Invalid attempt to overwrite a saving account.");
    }
    else
    {
        float initialBalance, rate;
        cout << "-- Enter  initial balance: ";
        cin >> initialBalance;
        cout << "-- Enter rate : ";
        cin >> rate;
        SavingAccount* sav = new SavingAccount(initialBalance, rate);
        oneClient->saving = sav;
        log.push_back("Saving account successfully created.");
    }
}

void BankSystem::RemoveSavingDialog()
{
    if (oneClient->saving != NULL)
    {
        SavingAccount* sav = oneClient->saving;
        oneClient->saving = NULL;
        delete sav;
        log.push_back("Saving account successfully removed.");
    }
    else
    {
        cout << "The client does not have a saving account\n";
        log.push_back("Invalid attempt to remove a non-existing saving account.");
    }
}

void BankSystem::DepositSavingDialog()
{
    if (oneClient->saving != NULL)
    {
        float amount;
        cout << "-- Amount to deposit: ";
        cin >> amount;
        oneClient->saving->deposit(amount);
        log.push_back("$" + to_string(amount) + " successfully deposited in saving account.");
    }
    else
    {
        cout << "The client does not have a saving account\n";
        log.push_back("Invalid attempt to deposit in a non-existing saving account.");
    }
}

void BankSystem::TransferDialog()
{
    if (oneClient->saving == NULL)
    {
        cout << "The client does not have a saving account\n";
        log.push_back("Invalid attempt to use a non-existing saving account.");
    }

    else if (oneClient->checking == NULL)
    {
        cout << "The client does not have a checking account\n";
        log.push_back("Invalid attempt to use a non-existing checking account.");
    }

    else
    {
        float amt;
        cout << "--Amount to transfer: ";
        cin >> amt;
        oneClient->saving->transfer(*(oneClient->checking), amt);
        log.push_back("$" + to_string(amt) + " successfully transferred from saving to checking account.");
    }
}

void BankSystem::start()
{
    int ch;
    cout << "= Menu =\n";
    cout << "1. Add a Checking account" << endl;
    cout << "2. Remove Checking account" << endl;
    cout << "3. Deposit into Checking Account" << endl;
    cout << "4. Withdraw from Checking Account" << endl;
    cout << "5. Add a Saving account" << endl;
    cout << "6. Remove Saving account" << endl;
    cout << "7. Deposit into Saving account" << endl;
    cout << "8. Transfer from Saving to Checking account" << endl;;
    cout << "9. Exit" << endl;

    bool ex = false;
    while (1)
    {
        cout << "Choose an option [1-9]: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            AddCheckingDialog();
            break;
        case 2:
            RemoveCheckingDialog();
            break;
        case 3:
            DepositCheckingDialog();
            break;
        case 4:
            WithdrawCheckingDialog();
            break;
        case 5:
            AddSavingDialog();
            break;
        case 6:
            RemoveSavingDialog();
            break;
        case 7:
            DepositSavingDialog();
            break;
        case 8:
            TransferDialog();
            break;
        case 9:
            ex = true;
            cout << "= LOG =\n";

            for (string a : log)
            {
                cout << a << "\n";
            }

            break;
        default:
            cout << "Invalid input!";
        }

        if (ex)
            break;
    }
}
