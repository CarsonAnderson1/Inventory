//
// Created by ander on 3/18/2022.
//

#ifndef MINECRAFTINVENTORY_INVENTORY_H
#define MINECRAFTINVENTORY_INVENTORY_H
#include <iomanip>
#include <string>
#include "item.h"

using std::string;

class Inventory {
private:
    class Node{
    public:
        Node();
        Node* next;
        Item* item;
    };
    Node* _head = nullptr;
    size_t _size = 0;
    size_t _maxSize = 0;
public:
    Inventory();
    ~Inventory();
    Inventory(const Inventory& other);
    bool AddItem(const string& itemName, const int& amount);
    bool Remove(const string& itemName, const int amount);
    bool AddToExistingItem(const string& itemName, int& amount);
    void PrintSmall()const;
    void PrintLarge()const;
    void PrintList()const;
    size_t FindLargestLength()const;
    size_t GetIndex(const string& itemName);
    size_t GetSize()const;
    size_t GetMax()const;
    void ItemInstances(const string& itemName)const; /// Sees if this item recurs
    void CheckItemInstances()const; /// Looks through linked list, checking for recurring items within itself
    void DecreaseItemInstances(const string& itemName)const;
    Inventory& operator=(const Inventory& other);
    Item* Get(const size_t& index)const;
};


#endif //MINECRAFTINVENTORY_INVENTORY_H
