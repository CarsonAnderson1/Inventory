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
    string _item; /// Name of item
    int _amount; /// Amount of that item
    int _maxAmount;
public:
    Item(string itemName, int amount); /// Constructs Item Object
    void DecreaseAmount(int amount); /// Decreases amount of an item in inventory
    void IncreaseAmount(int amount); /// Increases amount of an item in inventory
    int GetAmount()const;
    string Print()const;
    string GetItem()const;
    void SetMaxAmount(const int& max);
    size_t GetMaxAmount()const;
};


#endif //MINECRAFTINVENTORY_ITEM_H
