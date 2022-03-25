//
// Created by ander on 3/20/2022.
//
#include <fstream>
#include "static_functions.h"
using std::ifstream;

/**
 * Checks to see if the itemName exists in the "minecraftItemList"
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
    iFS.open("../minecraftItemList");
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
    /// I dont want an underscore for a copy item between its name and the instance
    /// ex. nether_brick_(3) is bad, i want nether_brick (3)
    if(returnString.find("_(") > 0 && returnString.find("_(") < returnString.length()){
        returnString[returnString.find("_(")] = ' ';
    }
    return returnString;
}
string RemoveUnderscoreAddCapitals(const string& itemName){
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
string RemoveUnderscore(const string& itemName){
    string returnString = itemName;
    for (int i = 0; i < returnString.length(); ++i) {
        if(returnString[i] == '_'){
            returnString[i] = ' ';
        }
    }
    return returnString;
}
bool NonStackItem(const string& itemName) {
    /// This looks through nonStackItems file
    string itemNonStack;
    string itemAnotherList;
    ifstream iFS;
    iFS.open("../nonStackItems");
    if (iFS.is_open()) {

        /** It is going to look in non-stack items since the only items I could find were broadly
         * listed into categories such as "armor". Then it will look through each line in another list and see
         * if they exist in it, making it a non stack item. (maximum amount is 1)
         */

        /// This looks through minecraftItemList
        size_t colon;
        size_t end;
        string newString;
        ifstream iFS2;
        iFS2.open("../minecraftItemList");
        if (iFS2.is_open()) {
            while (std::getline(iFS2, itemAnotherList)) { /// Looks through each line of another list
                if (itemAnotherList[0] != '(') { /// Checks to see if its the type of line im looking for
                    continue;
                }
                colon = itemAnotherList.find(':');
                end = itemAnotherList.find(')');
                newString = itemAnotherList.substr(colon + 1, end - colon - 1); /// Finds the name of the item
                if(newString == InputUnderscore(itemName)) {
                    break;
                }
                }
            string nonStackUnderscore;
            while (std::getline(iFS, itemNonStack)) { /// Looks through each line of non-stack
                nonStackUnderscore = InputUnderscore(itemNonStack);
                if(newString.find(nonStackUnderscore) <= newString.length() && newString.find(nonStackUnderscore) >= 0){
                    iFS.close();
                    iFS2.close();
                    return true;
                }
            }
            iFS.close();
            iFS2.close();
            return false;
        }
    }
}