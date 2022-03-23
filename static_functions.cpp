//
// Created by ander on 3/20/2022.
//
#include <fstream>
#include "static_functions.h"
using std::ifstream;

/**
 * Checks to see if the itemName exists in the "anotherList"
 * @param string: item name
 * @returns size_t: max size of an item
 */
bool FilterAnotherList(string& itemName) {
    string itemValid;
    string itemNew;
    string newString = "";
    string underscoreItem;
    ifstream iFS;
    size_t colon;
    size_t end;
    underscoreItem = InputUnderscore(itemName);
    size_t maxScore = 0;
    iFS.open("../anotherList");
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
                if(newString == underscoreItem){
                    itemName = underscoreItem;
                    iFS.close();
                    return true;
                }

        }
        iFS.close();
        return false;
    }
}
string InputUnderscore(const string& itemName){
    string returnString = itemName;
    for (int i = 0; i < returnString.length(); ++i) {
        returnString[i] = tolower(returnString[i]);
        if(returnString[i] == ' '){
            returnString[i] = '_';
        }
    }
    return returnString;
}
string RemoveUnderscore(const string& itemName){
    string returnString = itemName;
    returnString[0] = toupper(returnString[0]);
    for (int i = 0; i < returnString.length(); ++i) {
        if(returnString[i] == '_'){
            returnString[i] = ' ';
            returnString[i+1] = toupper(returnString[i+1]);
        }
    }
    return returnString;
}
bool NonStackItem(const string& itemName){
    string itemValid;
    RemoveUnderscore(itemName);
    ifstream iFS;
    iFS.open("../Non-Stackable Items");
    if(iFS.is_open()){
        while(std::getline(iFS,itemValid)){
            if(itemValid == itemName){
                cout << "YOU MAY ONLY HAVE ONE OF THESE PER INVENTORY SLOT" << endl;
                iFS.close();
                return true;
            }
        }
        iFS.close();
        return false;
    }
}