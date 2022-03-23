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
    void Print()const;
    size_t GetIndex(const string& itemName);
    size_t GetSize();
    size_t GetMax()const;
    Inventory& operator=(const Inventory& other);
    Item* Get(const size_t& index)const;
};


#endif //MINECRAFTINVENTORY_INVENTORY_H
