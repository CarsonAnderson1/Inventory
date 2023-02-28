//
// Created by ander on 3/18/2022.
//

#include "Inventory.h"
#include <iomanip>
#include <iostream>
#include "string"
#include <fstream>
#include <static_functions.h>
using std::string;
using std::endl;
using std::right;
using std::setw;
using std::ifstream;
using std::cerr;
using std::left;
using std::cin;

/**
 * Default Constructor
 * @param nothing
 */
Inventory::Inventory() {
    _head = nullptr;
    _size = 0;
}
/**
 * Destructor
 * @param nothing
 */
Inventory::~Inventory() { /// Destructor

    Node* toDelete = _head;
    for (int i = 0; i < _size; i++) {
        _head = _head->next;
        delete toDelete->item;
        delete toDelete;
        toDelete = _head;
    }
}
/**
 * Copy Constructor
 * @param Inventory object
 */
Inventory::Inventory(const Inventory& other){
    _head = other._head;
    _size = other._size;
}
/**
 * Copy Assignment Operator
 * @param book
 */
Inventory &Inventory::operator=(const Inventory& other){
    return *this;
}
/**
 * Adds an item to the inventory
 * @param string: name of an item, int: amount of the item
 */
bool Inventory::AddItem(const string& itemName, const int& amount) {
    /** Checking for the maximum amount
     *  ADD ITEM
     */
    size_t maxAmount = 64;
    string newName = RemoveUnderscoreAddCapitals(itemName);
    if(newName == "Snowball" || newName == "Bucket" || newName == "Egg" || newName== "Sign" || newName == "Ender Pearl"){
        maxAmount = 16;
        cout << "THIS ITEM ONLY STACKS TO 16" << endl;
    }
    newName = InputUnderscore(itemName); /// If it occurs more than once
    ItemInstances(newName);
    if(NonStackItem(newName)){
        maxAmount = 1;
        cout << "THIS ITEM DOES NOT STACK" << endl;
    }
    else{
        maxAmount = 64;
        cout << "THIS ITEM ONLY STACKS TO 64" << endl;
    }

    /** Adds Items
     * ADD ITEM
     */
    Node* tmp = new Node; /// Creates new node
    Item* itemTmp = new Item(itemName,amount); /// Creates new item
    itemTmp->SetMaxAmount(maxAmount);
    if(amount > maxAmount){
        return false;
    }
    if(_size == 0){ /// Checks to see if the list is empty
        _head = tmp;
        tmp->item = itemTmp;
        _size++;
    }
    else {
        tmp->next = _head;
        _head = tmp;
        tmp->item = itemTmp;
        _size++;
    }
    return true;
}
/**
 * If you are adding an item that exists in the list, it will add the amount you're attempting to add to that
 * item, and create a new item with the remainder, unless the remainder is 0.
 * It will return true if it did so
 * It will return false if it did not add to an item
 * @param string: name of an item, int: amount of the item
 */
bool Inventory::AddToExistingItem(const string &itemNameBefore, int &amount) {
    string yesOrNo;
    int remainder = 0;
    size_t tmpItemAmount;
    string itemName = InputUnderscore(itemNameBefore);
    for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next) {
        if(tmp->item->GetItem().find(itemName) >= 0 && tmp->item->GetItem().find(itemName) <= tmp->item->GetItem().length() &&
          (tmp->item->GetItem().length() - itemName.length()) < 5){

            /// Checks to see if an existing item of the same name is not full
            if(tmp->item->GetAmount() != tmp->item->GetMaxAmount()) {
                tmpItemAmount = tmp->item->GetAmount();

                /// If you want to stack existing items
                cout << "Would you like to add to an existing " << tmp->item->GetItem() << " stack? (y or n)" << endl;
                cin >> yesOrNo;
                if (yesOrNo == "Y" || yesOrNo == "y" || yesOrNo == "Yes" || yesOrNo == "yes" || yesOrNo == "YES") {
                    remainder = tmp->item->GetMaxAmount() - tmp->item->GetAmount() - amount;
                    /// If the amount you're adding goes over 64
                    if (tmp->item->GetAmount() + amount > tmp->item->GetMaxAmount()) {
                        remainder = amount + tmp->item->GetAmount() - tmp->item->GetMaxAmount();
                        amount = remainder;
                        tmp->item->SetAmount(tmp->item->GetMaxAmount());
                        continue;
                        return true;
                    }
                        /// If the amount you're adding does not go over 64
                    else if (tmp->item->GetAmount() + amount < tmp->item->GetMaxAmount()) {
                        tmp->item->IncreaseAmount(amount);
                        remainder = 0;
                        amount = remainder;
                        return true;
                    }
                }

                /// If you don't want the items to stack
                if (yesOrNo == "N" || yesOrNo == "n" || yesOrNo == "No" || yesOrNo == "no" || yesOrNo == "NO") {
                    return true;
                }
                    /// If you put in an unknown input
                else {
                    return false;
                }
            }
        }
    }

}
/**
 * Returns the size of the linked list
 * @param nothing
 */
size_t Inventory::GetSize()const {
    return _size;
}
/**
 * Gives the index of an item in the linked list
 * @param string: item name
 */
size_t Inventory::GetIndex(const string &itemName) {
    Node* tmp = _head;
    string tmpItemName = itemName;
    tmpItemName = InputUnderscore(itemName);
    for (int i = 0; i < _size; ++i) {
        if(tmp->item->GetItem() == tmpItemName){
            return i;
        }
        tmp = tmp->next;
    }
    return -1;
}
void Inventory::ItemInstances(const string &itemName) const {
    size_t instances = 1;
    std::stringstream instanceStream;
    string instanceString;
    for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next) {
        if(tmp->item->GetItem().find(itemName) >= 0 &&
           tmp->item->GetItem().find(itemName) <= tmp->item->GetItem().length() && (tmp->item->GetItem().length() - itemName.length() < 5)){

            instances++;
            tmp->item->SetInstance(instances);
            instanceStream << instances;
            instanceStream >> instanceString;
            instanceStream.clear();
            tmp->item->ChangeItemName(itemName + " (" + instanceString + ")");
        }
    }
}
/** If the given name is a copy (has parentheses and a number),
     *  It will make a new string without those attributes to then compare to the other copies
     *  and original in the list.
     *
     *  If it finds itself, it will break from this list. But it also keeps track of its own instance
     *  through "instanceNum" to then compare to the other copies. This is because if the instance number is
     *  lower we don't want to decrease it, but if it is higher, we want it to decrease.
     *
     *  Ex List: stone:1, stone (2): 54, stone (3): 27
     *  - if we delete stone (2), we want stone (3) to become stone (2), but have stone remain the same
     */
void Inventory::DecreaseItemInstances(const string &itemNameBefore) const {
    string instanceNumString = "0";
    std::stringstream instanceNumStream;
    size_t instanceNum = 0;
    string itemName = "";
    /// Breaks down the itemBefore if it is a copy to its original name
    /// Ex. "stone (2)" becomes "stone"
    for (int i = 0; i < itemNameBefore.length(); ++i) {
        if(itemNameBefore[i] != '(' && itemNameBefore[i] != ' ' && itemNameBefore[i] != ')' && !std::isdigit(itemNameBefore[i]))
            itemName.push_back(itemNameBefore[i]);
        /// Gets the instance number from it.
        /// Ex. "stone (2)" : instanceNum = 2
        if(std::isdigit(itemNameBefore[i])){
            instanceNumString = itemNameBefore[i];
        }
    }
    instanceNumStream.str(instanceNumString);
    instanceNumStream >> instanceNum;

    std::stringstream instanceStream;
    string instanceString;
    /// Looks for a copy
    for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next) {
        if(tmp->item->GetItem().find('(') >= 0 && tmp->item->GetItem().find('(') <= tmp->item->GetItem().length() &&
           tmp->item->GetItem().find(itemName) >= 0 && tmp->item->GetItem().find(itemName) <= tmp->item->GetItem().length() &&
           tmp->item->GetItem() != itemNameBefore && tmp->item->GetItem().length() - itemName.length() < 5){

            /// If the instance is below that which we are removing, we don't want it to lower
            if(tmp->item->GetInstance() < instanceNum){
                continue;
            }
            /// Lowers the instance numbers that are greater than that which we are removing
            tmp->item->SetInstance(tmp->item->GetInstance() - 1);
            instanceStream << tmp->item->GetInstance();
            instanceStream >> instanceString;
            instanceStream.clear();
            if(tmp->item->GetInstance() != 1)
                tmp->item->ChangeItemName(itemName + " (" + instanceString + ")");
            else
                tmp->item->ChangeItemName(itemName);
        }
    }
}

void Inventory::CheckItemInstances() const {
    /**
     * tmp holds an item that is an original. Ex. "Cobblestone"
     * tmp2 holds an item that is a duplicate. Ex. "Cobblestone (3)"
     */
    for (Node* tmp = _head; tmp != nullptr; tmp = tmp->next) {
        /// If it is a duplicate it continues loop
        if(tmp->item->GetItem().find("(") >= 0 && tmp->item->GetItem().find("(") <= tmp->item->GetItem().length()){
            continue;
        }
        size_t instances = 1;

        for (Node* tmp2 = _head; tmp2 != nullptr; tmp2 = tmp2->next) {
            /// If it is not a duplicate it continues loop
            if(tmp2->item->GetItem().find("(") >=! 0 && tmp2->item->GetItem().find("(") <=! tmp2->item->GetItem().length()){
                continue;
            }
            /// Finds an item within another item in the list
            /// Ex. (tmp) cobblestone is within (tmp2) cobblestone (2).
            if(tmp2->item->GetItem().find(tmp->item->GetItem() + " (") < tmp2->item->GetItem().length() &&
               tmp2->item->GetItem().find(tmp->item->GetItem() + " (") >= 0 &&
               (tmp2->item->GetItem().length() - tmp->item->GetItem().length()) < 5){

                instances++;
                tmp2->item->SetInstance(instances);
            }
        }

    }
}
Item* Inventory::Get(const size_t& index)const{
    Node* tmp = _head;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp->item;
}

size_t Inventory::FindLargestLength() const {
    size_t max = 0;
    Node* tmp = _head;
    for (tmp = _head; tmp != nullptr; tmp = tmp->next) {
        if(tmp->item->GetItem().length() > max){
            max = tmp->item->GetItem().length();
        }
    }
    return max;
}
/**
 * Prints out the inventory
 * @param nothing
 */
void Inventory::PrintSmall()const{
    CheckItemInstances();
    string invArray[17][4];
    int column = 0;
    int row = 0;
    size_t maxSize = 10;
    Node* tmp = _head;
    /// Find the maximum and fill the arrays (NORMAL SIZE)
    if(_size <= 36) {
        while (tmp != nullptr && _size != 0 && tmp->item->GetAmount() > 0) {
            if (column % 2 == 0) { /// If the row doesn't hold a separator
                invArray[column][row] = tmp->item->Print();
            }
            if (invArray[column][row].length() > maxSize) {
                maxSize = invArray[column][row].length() + 2;
            }
            row++;
            if (row > 3) {
                row = 0;
                column++;
            }
            if (column % 2 == 0) { /// Only moves to next node if row isn't a separator
                tmp = tmp->next;
            }
        }
            /// Output 1 (Normal Size)
            cout << endl;
            cout << setw(maxSize) << "INVENTORY" << endl << endl;
            for (int i = 0; i < 17; i++) {
                for (int j = 0; j < 4; j++) {
                    if (i % 2 == 0) {
                        if (j != 3) {
                            cout << left << setw(maxSize) << invArray[i][j] << " |";
                        } else if (j == 3) {
                            cout << left << setw(maxSize) << invArray[i][j];
                        }
                    }
                    else {

                        // Sets a divider between inventory slots
                        cout.fill('-');
                        cout << "--" << setw(maxSize) << "--";
                        cout.fill(' ');

                    }
                }
                cout << endl; // Starts a new line after 4 columns
            }
            cout << endl;
    }
}
void Inventory::PrintLarge() const {
    CheckItemInstances();
    string invArray[23][3];
    int column = 0;
    int row = 0;
    size_t maxSize = 10;
    Node* tmp = _head;
    /// Find the maximum and fill the arrays (NORMAL SIZE)
    if(_size <= 36) {
        while (tmp != nullptr && _size != 0 && tmp->item->GetAmount() > 0) {
            if (column % 2 == 0) { /// If the row doesn't hold a separator
                invArray[column][row] = tmp->item->Print();
            }
            if (invArray[column][row].length() > maxSize) {
                maxSize = invArray[column][row].length() + 2;

            }
            row++;
            if (row > 2) {
                row = 0;
                column++;
            }
            if (column % 2 == 0) { /// Only moves to next node if row isn't a separator
                tmp = tmp->next;
            }
        }
            cout << endl;
            cout << setw(maxSize) << "INVENTORY" << endl << endl;
            for (int i = 0; i < 23; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i % 2 == 0) {
                        if (j != 2) {
                            cout << left << setw(maxSize) << invArray[i][j] << " |";
                        } else if (j == 2) {
                            cout << left << setw(maxSize) << invArray[i][j];
                        }
                    }
                    else {
                        // Sets a divider between inventory slots
                        cout.fill('-');
                        cout << left << setw(maxSize* 1.1) << "-";
                        cout.fill(' ');
                    }
                }
                cout << endl; // Starts a new line after 3 columns
            }
            cout << endl;
    }
}
void Inventory::PrintList()const {
    CheckItemInstances();
    string invArray[36];
    int row = 0;
    Node *tmp = _head;
    if (_size <= 36) {
        while (tmp != nullptr && _size != 0 && tmp->item->GetAmount() > 0) {
            invArray[row] = tmp->item->Print();
            row++;
            tmp = tmp->next;
        }
        for (int i = 0; i < _size; ++i) {
            cout << invArray[i] << endl;
        }
        cout << endl;
    }
}

/**
 * Removes an item from the inventory, or reduces amount
 * @param string: item name, int: amount
 */
bool Inventory::Remove(const string &itemNameBefore, const int amount) {
    string itemName = InputUnderscore(itemNameBefore);
    if(_size == 0){ /// If the list is empty
        return false;
    }
    DecreaseItemInstances(itemName);
    size_t index;
    index = GetIndex(itemName);
    if(index == -1){ /// If what you're looking for does not exist
        return false;
    }
    Node* tmp = _head;
    if(index == 0){ /// If the node to delete is the head
        tmp->item->DecreaseAmount(amount);
        if(tmp->item->GetAmount() <= 0){
            Node* toDelete = _head;
            _head = _head->next;
            delete toDelete->item;
            delete toDelete;
            _size --;
            return true;
        }
        else{
            return true;
        }
    }
    for (int i = 0; i < index - 1; ++i) { /// Finds node before nodeToDelete
        tmp = tmp->next;
    }
    Node* toRemove = tmp->next;
    toRemove->item->DecreaseAmount(amount);
    if(toRemove->item->GetAmount() <= 0){
        tmp->next = tmp->next->next;
        toRemove->next = nullptr;
        delete toRemove->item;
        delete toRemove;
        _size --;
        return true;
    }
    return false;

}
/**
 * Default Constructor for a Node
 * @param nothing
 */
Inventory::Node::Node() {
    next = nullptr;
    item = nullptr;
}
/**
 * Finds the longest item in Minecraft in word length
 * @param nothing
 */
size_t Inventory::GetMax()const {
    string itemValid;
    string newString;

    ifstream iFS;
    size_t colon;
    size_t end;
    size_t maxScore = 0;
    iFS.open("../minecraftItemList");
    if (iFS.is_open()) {
        while (std::getline(iFS, itemValid)) { /// Looks through each line of the file
            if(itemValid[0] != '('){ /// Checks to see if its the type of line im looking for
                continue;
            }
            colon = itemValid.find(':');
            end = itemValid.find(')');
            newString = itemValid.substr(colon + 1,end - colon - 1); /// Finds the name of the item
            if(newString.length() > maxScore){
                maxScore = newString.length();
            }
        }
        iFS.close();
        return maxScore;
    }
}

