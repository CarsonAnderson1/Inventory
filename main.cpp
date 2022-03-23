
#include <iostream>
#include "Inventory.h"
#include "static_functions.h"
#include <iomanip>
#include "Menu.h"

using std::cout;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
using std::getline;



int main() {
    /** Creating the Menu **/
    Menu minecraftMenu(3);
    minecraftMenu.SetTitle("Minecraft Inventory");
    minecraftMenu.SetInputType(INT);
    minecraftMenu.SetErrorMessage("Your input was not recognized");
    minecraftMenu.SetInvalidOption("Your input is not one of the given choices");
    minecraftMenu.AddMenuOption(0, "1", "Add an item to your inventory");
    minecraftMenu.AddSeparator(1);
    minecraftMenu.AddMenuOption(2,"2","Dispose of item");


    /*** Cause it to print everything out **/
    int selected; /// For the switch
    Inventory inventory;
    inventory.Print();
    while ((selected = minecraftMenu.Run()) != -1) {
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            /**
             * Adding an item to the inventory
             */
            case 0: {
                string item;
                string amount;
                std::stringstream amountStream;
                int amountNum;
                cout << "What Item are you adding to your inventory?" << endl;
                getline(cin, item);
                getline(cin, item);
                if(!FilterAnotherList(item)){ /// Checking to see if the item exists in Minecraft
                    cerr << "Enter valid item" << endl;
                    break;
                }
                size_t tmpMax = FilterAnotherList(item); /// Finds the largest size of an item in Minecraft
                inventory.SetMaxInventory(tmpMax); /// Sets the max size
                tmpMax = inventory.GetMax();
                cout << "How many are you adding?" << endl; /// Amount to add
                cin >> amount;
                if(!std::isdigit(amount.at(0))){ /// Checking to see if a number is being input, otherwise reject it
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                amountStream << amount;
                amountStream >> amountNum;
                inventory.AddItem(item, amountNum); /// Adds item to inventory
                NonStackItem(item);
                inventory.Print(); /// Prints out inventory
                break;
            }
            /**
             * Deleting an item / Lowering the amount of an item in the inventory
             */
            case 2:{
                string item;
                string amount;
                std::stringstream amountStream;
                int amountNum;

                /// Input information to be used
                cout << "What Item are you removing from your inventory?" << endl;
                getline(cin, item);
                getline(cin, item);
                cout << "How many are you removing?" << endl;
                cin >> amount;
                amountStream << amount;
                amountStream >> amountNum;

                /// Checks to see if the entered amount is a number
                if(!std::isdigit(amount.at(0))){
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                /// Removes item - Checks if remove worked
                if(!inventory.Remove(item,amountNum)){
                    cerr << "Unable to remove" << endl;
                    break;
                }
                inventory.Print();
                break;
            }
        }
    }

    cout << "Finished" << endl << endl;
    return 0;
}