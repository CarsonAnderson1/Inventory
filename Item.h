//
// Created by ander on 3/18/2022.
//

#ifndef MINECRAFTINVENTORY_ITEM_H
#define MINECRAFTINVENTORY_ITEM_H
#include <string>

using std::string;

class Item {
private:
    string _item; /// Name of item
    int _amount; /// Amount of that item

public:
    Item(string itemName, int amount); /// Constructs Item Object
    void DecreaseAmount(int amount); /// Decreases amount of an item in inventory
    void IncreaseAmount(int amount); /// Increases amount of an item in inventory
    int GetAmount()const;
    string Print()const;
    string GetItem()const;

};


#endif //MINECRAFTINVENTORY_ITEM_H
