//
// Created by ander on 3/20/2022.
//
#include <string>
#include <iostream>
#ifndef INVENTORY_STATIC_FUNCTIONS_H
#define INVENTORY_STATIC_FUNCTIONS_H
using std::string;
using std::cout;
using std::endl;

bool FilterAnotherList(string& itemName);
bool NonStackItem(const string& itemName);
string InputUnderscore(const string& itemName);
string RemoveUnderscore(const string& itemName);


#endif //INVENTORY_STATIC_FUNCTIONS_H
