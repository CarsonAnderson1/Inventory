//
// Created by ander on 3/18/2022.
//
#include "iostream"
#include "Item.h"
#include <sstream>
#include <fstream>
using std::cout;
using std::stringstream;
using std::ifstream;

/**
 * Default constructor for item
 * @param string: item name, int: amount
 */
Item::Item(string itemName, int amount){
    _itemName = itemName;
    _amount = amount;
}
/**
 * Decreases amount of an item in the inventory
 * @param amount
 */
void Item::DecreaseAmount(const int& amount) {
    _amount -= amount;
}
/**
 * Increases the amount of an item in the inventory
 * @param amount
 */
void Item::IncreaseAmount(const int& amount) {
    _amount += amount;
}
void Item::SetAmount(const int &amount) {
    _amount = amount;
}
void Item::ChangeItemName(const string &newName) {
    _itemName = newName;
}
/**
 * Returns the item name and number of an item object
 * @param nothing
 */
string Item::Print() const {
    string tmpString;
    stringstream tmpStream;

    tmpStream << _amount;
    tmpStream >> tmpString;

    tmpString = _itemName + ": " + tmpString;
    return tmpString;
}
/**
 * Returns item name
 * @param nothing
 */
string Item::GetItem() const {
    return _itemName;
}
/**
 * Returns amount of item
 * @param nothing
 */
int Item::GetAmount() const {
    return _amount;
}
/**
 * Sets max amount the item can hold
 * @param int max
 */
void Item::SetMaxAmount(const int& max){
    _maxAmount = max;
}
/**
 * Gets max amount the item can hold
 * @param nothing
 */
size_t Item::GetMaxAmount() const {
    return _maxAmount;
}
void Item::SetInstance(const size_t &instance) {
    _instance = instance;
}
size_t Item::GetInstance() const {
    return _instance;
}
