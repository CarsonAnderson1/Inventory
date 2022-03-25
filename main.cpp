
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
using std::stringstream;
using std::isdigit;



int main() {
    /** Creating the Menu **/
    Menu minecraftMenu(5);
    minecraftMenu.SetTitle("Minecraft Inventory");
    minecraftMenu.SetInputType(INT);
    minecraftMenu.SetErrorMessage("Your input was not recognized");
    minecraftMenu.SetInvalidOption("Your input is not one of the given choices");
    minecraftMenu.AddMenuOption(0, "1", "Add an item to your inventory");
    minecraftMenu.AddSeparator(1);
    minecraftMenu.AddMenuOption(2,"2","Dispose of item");
    minecraftMenu.AddMenuOption(3,"3","Increase the amount of an item");
    minecraftMenu.AddMenuOption(4,"4","Print the Inventory");

    /*** Cause it to print everything out **/
    int selected; /// For the switch
    Inventory inventory;
    inventory.PrintSmall();
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
                if(inventory.GetSize() == 32){  // If inventory is full
                    cerr << "Not enough space in inventory" << endl;
                    break;
                }
                string item;
                string amount;
                stringstream amountStream;
                int amountNum;
                cout << "What Item are you adding to your inventory?" << endl;
                getline(cin, item);
                getline(cin, item);
                if(!FilterAnotherList(item)){ /// Checking to see if the item exists in Minecraft
                    cerr << "Enter valid item" << endl;
                    break;
                }
                cout << "How many are you adding?" << endl; /// Amount to add
                cin >> amount;
                if(!isdigit(amount.at(0))){ /// Checking to see if a number is being input, otherwise reject it
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                amountStream << amount;
                amountStream >> amountNum;
                inventory.AddToExistingItem(item,amountNum);
                if(amountNum == 0){
                    if(inventory.FindLargestLength()<= 20){
                        inventory.PrintSmall();
                    }
                    else {
                        inventory.PrintLarge();
                    }
                    break;
                }
                if(inventory.AddItem(item, amountNum)){ /// Adds item to inventory, and if it returns true it prints out the inventory
                    if(inventory.FindLargestLength()<= 20){
                        inventory.PrintSmall();
                    }
                    else {
                        inventory.PrintLarge();
                    }
                }
                else{
                    cerr << "Error in input" << endl;
                }

                break;
            }
            /**
             * Deleting an item / Lowering the amount of an item in the inventory
             */
            case 2:{
                string item;
                string amount;
                stringstream amountStream;
                int amountNum;
                /// Checks to see if list is empty first
                if(inventory.GetSize() == 0){
                    cerr << "List is empty" << endl;
                    break;
                }
                /// Input information to be used
                cout << "What Item are you removing from your inventory?" << endl;
                getline(cin, item);
                getline(cin, item);
                cout << "How many are you removing?" << endl;
                cin >> amount;
                /// Checks to see if the entered amount is a number
                if(!isdigit(amount.at(0))){
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                amountStream << amount;
                amountStream >> amountNum;
                /// Removes item - Checks if remove worked
                if(!inventory.Remove(item,amountNum)){
                    cerr << "Unable to remove" << endl;
                    break;
                }
                if(inventory.FindLargestLength() <= 20){
                    inventory.PrintSmall();
                }
                else {
                    inventory.PrintLarge();
                }
                break;
            }
                /**
                 * Increasing the amount of an item in the inventory
                 */
            case 3:{
                string tmpItem;
                string amount;
                stringstream amountStream;
                size_t amountNum;
                string tmpItemUnderscore;
                string yesOrNo;
                Item* tmpItemPointer;

                /// Checks to see if list is empty first
                if(inventory.GetSize() == 0){
                    cerr << "List is empty" << endl;
                    break;
                }
                /// Find item in linked list
                cout << "Which item do you want to add to?" << endl;
                cin >> tmpItem;
                tmpItemUnderscore = InputUnderscore(tmpItem);
                /// If item does not exist, break, if not, receive pointer to the item
                if(inventory.GetIndex(tmpItemUnderscore) != -1){
                    tmpItemPointer = inventory.Get(inventory.GetIndex(tmpItemUnderscore));
                }
                else{
                    cerr << "Item does not exist in list" << endl;
                    break;
                }
                if(tmpItemPointer->GetAmount() == tmpItemPointer->GetMaxAmount()){
                    cerr << "Item is already at full capacity" << endl;
                    break;
                }
                /// How much to increase amount by
                cout << "How much would you like to add to this item?" << endl;
                cin >> amount;
                /// Checks to see if the entered amount is a number
                if(!isdigit(amount.at(0))){
                    cerr << "Enter a valid amount" << endl;
                    break;
                }
                amountStream << amount;
                amountStream >> amountNum;
                /// Increases amount given when within limits
                if(tmpItemPointer->GetAmount() + amountNum <= tmpItemPointer->GetMaxAmount()) {
                    tmpItemPointer->IncreaseAmount(amountNum);
                    if(inventory.FindLargestLength() <= 20){
                        inventory.PrintSmall();
                    }
                    else {
                        inventory.PrintLarge();
                    }
                    break;
                }
                /// If amount is beyond limits
                else{
                    cerr << "The amount you're increasing goes beyond the item's stack capacity" << endl;
                    cout << "Would you like to just increase the item to maximum capacity? (y or n)" << endl;
                    cin >> yesOrNo;
                    if(yesOrNo == "y" || yesOrNo == "Y"){
                        tmpItemPointer->SetAmount(tmpItemPointer->GetMaxAmount());
                        if(inventory.FindLargestLength() <= 20){
                            inventory.PrintSmall();
                        }
                        else {
                            if(inventory.FindLargestLength() <= 20){
                                inventory.PrintSmall();
                            }
                            else {
                                inventory.PrintLarge();
                            }
                        }
                        break;
                    }
                    else{
                        inventory.PrintSmall();
                        break;
                    }
                }
            }
            case 4:{
                string yesOrNo;
                cout << "Print Inventory as a list? (y or n)" << endl;
                cin >> yesOrNo;
                if (yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "Yes" || yesOrNo == "yes" || yesOrNo == "YES") {
                    inventory.PrintList();
                }
                else if (yesOrNo == "N" || yesOrNo == "n" || yesOrNo == "No" || yesOrNo == "no" || yesOrNo == "NO") {
                    if(inventory.FindLargestLength() <= 20){
                        inventory.PrintSmall();
                    }
                    else {
                        inventory.PrintLarge();
                    }
                }
                else{
                    cerr << "Input not recognized" << endl;
                    break;
                };
            }
        }
    }

    cout << "Finished" << endl << endl;
    return 0;
}