//
// Created by ander on 3/18/2022.
//

#include "Inventory.h"
#include <iomanip>
#include <iostream>
#include "string"
#include <fstream>
#include <static_functions.h>
using std::cout;
using std::string;
using std::endl;
using std::right;
using std::setw;
using std::ifstream;
using std::cerr;

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
    string newName = RemoveUnderscore(itemName);
    if(newName == "Snowball" || newName == "Bucket" || newName == "Egg" || newName== "Sign" || newName == "Ender Pearl"){
        maxAmount = 16;
        cout << "THIS ITEM ONLY STACKS TO 16" << endl;
    }
    else if(NonStackItem(newName)){
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
 * Returns the size of the linked list
 * @param nothing
 */
size_t Inventory::GetSize() {
    return _size;
}
/**
 * Gives the index of an item in the linked list
 * @param string: item name
 */
size_t Inventory::GetIndex(const string &itemName) {
    Node* tmp = _head;
    string tmpItemName = InputUnderscore(itemName);
    for (int i = 0; i < _size; ++i) {
        if(tmp->item->GetItem() == tmpItemName){
            return i;
        }
        tmp = tmp->next;
    }
    return -1;
}
Item* Inventory::Get(const size_t& index)const{
    Node* tmp = _head;
    for (int i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp->item;
}
/**
 * Prints out the inventory
 * @param nothing
 */
void Inventory::Print()const{
    string invArray[17][4];
    int column = 0;
    int row = 0;
    int greatestSize = 10;
    Node* tmp = _head;
    if(_size <= 36) {
        while (tmp!= nullptr && _size != 0 && tmp->item->GetAmount() > 0) {
            if(column % 2 == 0) { /// If the row doesn't hold a separator
                invArray[column][row] = tmp->item->Print();
            }
            if(invArray[column][row].length() > greatestSize){
                greatestSize = invArray[column][row].length() + 2;
            }
            row++;
            if (row > 3) {
                row = 0;
                column++;
            }
            if(column % 2 == 0) { /// Only moves to next node if row isn't a separator
                tmp = tmp->next;
            }
        }
        cout << endl;
        cout << setw(greatestSize) << "INVENTORY" << endl << endl;
        for(int i = 0; i < 17; i++){
            for(int j = 0; j < 4; j++){
                if(i % 2 == 0) {
                    if(j < 3){
                        cout << std::left << setw(greatestSize) << invArray[i][j] << " |";
                    }
                    else{
                        cout << std::left << setw(greatestSize) << invArray[i][j];
                    }

                }
                else{
                    cout.fill('-');
                    cout << right << setw(greatestSize * 1.2) << "-";
                    cout.fill(' ');
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}
/**
 * Removes an item from the inventory, or reduces amount
 * @param string: item name, int: amount
 */
bool Inventory::Remove(const string &itemName, const int amount) {
    if(_size == 0){ /// If the list is empty
        return false;
    }
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

