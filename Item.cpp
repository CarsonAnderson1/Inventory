//
// Created by ander on 3/18/2022.
//
#include "iostream"
#include "Item.h"
#include <sstream>
using std::cout;
using std::stringstream;

Item::Item(string itemName, int amount){ /// Constructs an object of class item
    _item = itemName;
    _amount = amount;
}
void Item::DecreaseAmount(int amount) {
    _amount -= amount;
}
void Item::IncreaseAmount(int amount) {
    _amount += amount;
}
string Item::Print() const {
    string tmpString;
    stringstream tmpStream;

    tmpStream << _amount;
    tmpStream >> tmpString;

    tmpString = _item + ": " + tmpString;
    return tmpString;
}
string Item::GetItem() const {
    return _item;
}
int Item::GetAmount() const {
    return _amount;
}