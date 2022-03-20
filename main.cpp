
#include <iostream>
#include "Inventory.h"
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


    /*** Cause it to print everything out **/
    int selected; // For the switch
    Inventory inventory;
    inventory.Print();
    while ((selected = minecraftMenu.Run()) != -1) {
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            case 0: {
                string item;
                string amount;
                std::stringstream amountStream;
                int amountNum;
                cout << "What Item are you adding to your inventory?" << endl;
                getline(cin, item);
                getline(cin, item);
                cout << "How many are you adding?";
                cin >> amount;
                if(!std::isdigit(amount.at(0))){
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                amountStream << amount;
                amountStream >> amountNum;
                inventory.AddItem(item, amountNum);
                inventory.Print();
                break;
            }

        }
    }

    cout << "Finished" << endl << endl;
    return 0;
}