// #############################################################################################
//  Project: Aid Management System
// #############################################################################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "Perishable.h"
#include "Item.h"
using namespace std;
namespace sdds
{
    unsigned int AidMan::menu()
    {
        unsigned int menuOption;
        cout << "Aid Management System" << endl;
        cout << "Date: " << Date() << endl;
        cout << "Data file: ";
        if (m_filename == nullptr)
        {
            cout << "No file" << endl;
        }
        else
        {
            cout << m_filename << endl;
        }
        cout << "---------------------------------" << endl;
        menuOption = m_menu.run();
        return menuOption;
    }

    AidMan::AidMan()
    {
        m_menu.m_menuList = new char[strlen("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n") + 2];
        strcpy(m_menu.m_menuList,
               "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n");
        m_menu.m_options = 7;
    }
    AidMan::~AidMan()
    {
        deallocate();
    }
    void AidMan::run()
    {
        bool flag = false;
        unsigned int optionNumber = 0;
        do
        {
            optionNumber = menu();
            if (optionNumber != 0 && optionNumber != 7 && !m_filename)
            {
                optionNumber = 7;
            }
            if (optionNumber == 1)
            {
                cout << "\n****List Items****\n";
                int numOfItemsListed = list();
                cin.ignore();
                cout << "Enter row number to display details or <ENTER> to continue:\n> ";
                if (cin.peek() != '\n')
                {
                    int choice = ut.getint(1, numOfItemsListed + 1);
                    iProductPtrs[choice - 1]->linear(false);
                    iProductPtrs[choice - 1]->display(cout) << endl;
                }
            }
            else if (optionNumber == 2)
            {
                cout << "\n****Add Item****\n";
                if (!(iProdNum < sdds_max_num_items))
                {
                    cout << "Database full!\n";
                }
                else
                {
                    Menu tempM;
                    tempM.m_menuList = new char[strlen("1- Perishable\n2- Non-Perishable\n-----------------\n") + 2];
                    strcpy(tempM.m_menuList, "1- Perishable\n2- Non-Perishable\n-----------------\n");
                    tempM.m_options = 2;
                    int choice = tempM.run();
                    iProduct *iProdtempPtr = nullptr;
                    if (choice == 1)
                    {
                        iProdtempPtr = new Perishable();
                    }
                    else if (choice == 2)
                    {
                        iProdtempPtr = new Item();
                    }
                    else if (choice == 0)
                    {
                        cout << "Aborted\n";
                    }
                    if (choice)
                    {
                        int sku = iProdtempPtr->readSku(cin);
                        int idx = search(sku);
                        if (idx != -1)
                        {
                            cout << "Sku: " << setw(5) << sku << " is already in the system, try updating quantity instead.\n";
                            delete iProdtempPtr;
                        }
                        else
                        {
                            iProdtempPtr->read(cin);
                            if (*iProdtempPtr)
                            {
                                iProductPtrs[iProdNum] = iProdtempPtr;
                                iProdNum++;
                            }
                            else
                            {
                                iProdtempPtr->display(cout);
                                delete iProdtempPtr;
                            }
                        }
                    }
                }
            }
            else if (optionNumber == 3)
            {
                cout << "\n****Remove Item****\n";
                cout << "Item description: ";
                char itemDesc[100];
                cin.ignore();
                cin.getline(itemDesc, 100, '\n');
                int itemListed = list(itemDesc);
                if (itemListed > 0)
                {
                    cout << "Enter SKU: ";
                    int sku = ut.getint(10000, 99999);
                    int idx = search(sku);
                    if (idx == -1)
                    {
                        cout << "SKU not found!" << endl;
                    }
                    else
                    {
                        cout << "Following item will be removed: " << endl;
                        iProductPtrs[idx]->linear(false);
                        iProductPtrs[idx]->display(cout) << endl;

                        Menu tempM;
                        tempM.m_menuList = new char[strlen("Are you sure?\n1- Yes!\n") + 2];
                        strcpy(tempM.m_menuList, "Are you sure?\n1- Yes!\n");
                        tempM.m_options = 2;
                        int choice = tempM.run();
                        if (choice == 1)
                        {
                            remove(idx);
                            cout << "Item removed!" << endl;
                        }
                        else
                        {
                            cout << "Aborted!" << endl;
                        }
                    }
                }
            }
            else if (optionNumber == 4)
            {
                cout << "\n****Update Quantity****\n";
                cout << "Item description: ";
                char itemDesc[100];
                cin.ignore();
                cin.getline(itemDesc, 100, '\n');
                int itemListed = list(itemDesc);
                if (itemListed > 0)
                {
                    cout << "Enter SKU: ";
                    int sku = ut.getint(10000, 99999);
                    int idx = search(sku);
                    if (idx == -1)
                    {
                        cout << "SKU not found!" << endl;
                    }
                    else
                    {
                        Menu tempM;
                        tempM.m_menuList = new char[strlen("1- Add\n2- Reduce\n") + 2];
                        strcpy(tempM.m_menuList, "1- Add\n2- Reduce\n");
                        tempM.m_options = 2;
                        int choice = tempM.run();
                        if (choice == 1)
                        {
                            if (iProductPtrs[idx]->qtyNeeded() - iProductPtrs[idx]->qty())
                            {
                                cout << "Quantity to add: ";
                                int qty = ut.getint(1, iProductPtrs[idx]->qtyNeeded() - iProductPtrs[idx]->qty());
                                *iProductPtrs[idx] += qty;
                                cout << qty << " items added!" << endl;
                            }
                            else
                            {
                                cout << "Quantity Needed already fulfilled!\n";
                            }
                        }
                        else if (choice == 2)
                        {
                            if (iProductPtrs[idx]->qty())
                            {
                                cout << "Quantity to reduce: ";
                                int qty = ut.getint(1, iProductPtrs[idx]->qty());
                                *iProductPtrs[idx] -= qty;
                                cout << qty << " items removed!" << endl;
                            }
                            else
                            {
                                cout << "Quantity on hand is zero!\n\n";
                            }
                        }
                        else if (choice == 0)
                        {
                            cout << "Aborted!" << endl;
                        }
                    }
                }
            }
            else if (optionNumber == 5)
            {
                cout << "\n****Sort****\n";
                sort();
            }
            else if (optionNumber == 6)
            {
                int itemShipped = 0;
                cout << "\n****Ship Items****\n";
                ofstream file("shippingOrder.txt");
                if (file)
                {
                    file << "Shipping Order, Date: " << Date() << "\n";
                    file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
                    file << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
                    for (int i = 0; i < iProdNum; i++)
                    {
                        if (iProductPtrs[i]->qty() == iProductPtrs[i]->qtyNeeded())
                        {
                            iProductPtrs[i]->linear(true);
                            file << setfill(' ') << setw(4) << itemShipped + 1 << " | ";
                            iProductPtrs[i]->display(file) << endl;
                            remove(i);
                            itemShipped++;
                        }
                    }
                    file << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
                }
                cout << "Shipping Order for "<< itemShipped <<" times saved!" << endl;
            }
            else if (optionNumber == 7)
            {
                cout << "\n****New/Open Aid Database****\n";
                load();
            }
            else if (optionNumber == 0)
            {
                cout << "Exiting Program!";
                flag = true;
            }
            cout << "\n";
        } while (flag == false && optionNumber != 0);
        save();
    }
    void AidMan::save()
    {
        if (m_filename != nullptr)
        {
            ofstream file(m_filename);
            for (int i = 0; i < iProdNum; i++)
            {
                iProductPtrs[i]->save(file) << endl;
            }
        }
    }
    void AidMan::deallocate()
    {
        for (int i = 0; i < iProdNum; i++)
        {
            delete iProductPtrs[i];
            iProductPtrs[i] = nullptr;
        }
        delete[] m_filename;
        iProdNum = 0;
    }
    bool AidMan::load()
    {
        save();
        deallocate();
        cout << "Enter file name: ";
        char filename[50] = {'\0'};
        cin.ignore();
        cin.getline(filename, '\n');
        m_filename = new char[strlen(filename) + 1];
        strcpy(m_filename, filename);
        ifstream file(m_filename);
        if (!file)
        {
            cout << "Failed to open " << m_filename << " for reading!";
            cout << "Would you like to create a new data file?";
            Menu tempM;
            tempM.m_menuList = new char[strlen("1- Yes!\n") + 2];
            tempM.m_options = 1;
            strcpy(tempM.m_menuList, "1- Yes!\n");
            unsigned int optionNumber = tempM.run();
            if (optionNumber == 1)
                file.open(m_filename, fstream::app);
        }
        else
        {
            while (file)
            {
                char firstChar = file.peek();
                if (firstChar >= '1' && firstChar <= '3')
                {
                    iProductPtrs[iProdNum] = new Perishable();
                }
                else if (firstChar >= '4' && firstChar <= '9')
                {
                    iProductPtrs[iProdNum] = new Item();
                }
                else
                {
                    file.setstate(ios_base::failbit);
                }
                if (file && firstChar != '\n')
                {
                    iProductPtrs[iProdNum]->load(file);
                    if (*iProductPtrs[iProdNum])
                    {
                        iProdNum++;
                    }
                }
                else
                {
                    delete iProductPtrs[iProdNum];
                    iProductPtrs[iProdNum] = nullptr;
                }
            }
            cout << iProdNum << " records loaded!\n";
        }
        return iProdNum > 0;
    }
    int AidMan::list(const char *sub_desc)
    {
        int numOfItemsListed = 0;
        cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        if (!sub_desc)
        {
            for (int i = 0; i < iProdNum; i++)
            {
                iProductPtrs[i]->linear(true);
                cout << setfill(' ') << setw(4) << i + 1 << " | ";
                iProductPtrs[i]->display(cout) << endl;
                numOfItemsListed++;
            }
        }
        else
        {
            for (int i = 0; i < iProdNum; i++)
            {
                if (*iProductPtrs[i] == sub_desc)
                {
                    iProductPtrs[i]->linear(true);
                    cout << setfill(' ') << setw(4) << i + 1 << " | ";
                    iProductPtrs[i]->display(cout) << endl;
                    numOfItemsListed++;
                }
            }
        }
        cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
        return numOfItemsListed;
    }
    int AidMan::search(int sku) const
    {
        for (int i = 0; i < iProdNum; i++)
            if (*iProductPtrs[i] == sku)
                return i;
        return -1;
    }
    void AidMan::remove(int index)
    {
        if (index < iProdNum)
        {
            delete iProductPtrs[index];
            for (int idx = index; idx < iProdNum - 1; idx++)
                iProductPtrs[idx] = iProductPtrs[idx + 1];
            iProductPtrs[iProdNum - 1] = nullptr;
            iProdNum--;
        }
    }
    void AidMan::sort()
    {
        for (int i = 1; i < iProdNum; i++)
        {
            for (int j = 0; j < iProdNum - 1; j++)
            {
                int diff1 = iProductPtrs[j]->qtyNeeded() - iProductPtrs[j]->qty();
                int diff2 = iProductPtrs[j + 1]->qtyNeeded() - iProductPtrs[j + 1]->qty();
                if (diff2 > diff1)
                {
                    iProduct *tempPtr = iProductPtrs[j];
                    iProductPtrs[j] = iProductPtrs[j + 1];
                    iProductPtrs[j + 1] = tempPtr;
                }
            }
        }
        cout << "Sort completed!\n";
    }
}