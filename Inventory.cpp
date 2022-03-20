//
// Created by ander on 3/18/2022.
//

#include "Inventory.h"
#include <iomanip>
#include <iostream>
#include "string"
using std::cout;
using std::string;
using std::endl;
using std::right;
using std::setw;

Inventory::Inventory() {
    _head = nullptr;
    _size = 0;
}
Inventory::~Inventory() { /// Destructor

    Node* toDelete = _head;
    for (int i = 0; i < _size; i++) {
        _head = _head->next;
        delete toDelete->item;
        delete toDelete;
        toDelete = _head;
    }
}
Inventory::Inventory(const Inventory& other){ /// Copy constructor
    _head = other._head;
    _size = other._size;
}
Inventory &Inventory::operator=(const Inventory& other){
    return *this;
}
bool Inventory::AddItem(const string& itemName, const int& amount) {
    Node* tmp = new Node; /// Creates new node
    Item* itemTmp = new Item(itemName,amount); /// Creates new item
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
size_t Inventory::GetSize() {
    return _size;
}
size_t Inventory::GetIndex(const string &itemName) {
    Node* tmp = _head;
    for (int i = 0; i < _size; ++i) {
        if(tmp->item->GetItem() == itemName){
            return i;
        }
    }
}
void Inventory::Print()const{
    string invArray[17][4];
    int column = 0;
    int row = 0;
    int greatestSize = 10;
    Node* tmp = _head;
    if(_size <= 36) {
        while (tmp!= nullptr) {
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
                    cout << setw(greatestSize * 1.2) << "-";
                    cout.fill(' ');
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool Inventory::Remove(const string &itemName, const int amount) {
    size_t index;
    index = GetIndex(itemName);
    Node* tmp = _head;
    for (int i = 0; i < index - 1; ++i) { /// Finds node before nodeToDelete
        tmp = tmp->next;
    }
    Node* toRemove = tmp->next;
    toRemove->item->DecreaseAmount(amount);


}
Inventory::Node::Node() {
    next = nullptr;
    item = nullptr;
}