//
// Created by ander on 3/18/2022.
//

#ifndef MINECRAFTINVENTORY_ITEM_H
#define MINECRAFTINVENTORY_ITEM_H
#include <string>
#include "static_functions.h"

using std::string;

class Item {
private:
    string _itemName; /// Name of item
    int _amount; /// Amount of that item
    int _maxAmount; /// Maximum amount an item can stack to
    size_t _instance = 1;
public:
    Item(string itemName, int amount);
    void DecreaseAmount(const int& amount);
    void IncreaseAmount(const int& amount);
    void SetAmount(const int& amount);
    int GetAmount()const;
    string Print()const;
    string GetItem()const;
    void SetMaxAmount(const int& max);
    size_t GetMaxAmount()const;
    void SetInstance(const size_t& instance);
    size_t GetInstance()const;
    void ChangeItemName(const string& newName);
};


#endif //MINECRAFTINVENTORY_ITEM_H
