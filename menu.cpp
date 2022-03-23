//
// Created by ander on 3/19/2022.
//

#include "menu.h"
using std::endl;

/**
 * The Menu constructor. Notice there is no default constructor. Notice that three streams can be sent to this
 * constructor, they will set _output, _input and _errorStream respectively. When you want to output something to
 * the screen you will use _output. For example:
 * _output << _menuTitle << endl;
 * That statement would send the title of the menu to whatever output stream has be set, by default cout.
 * @param numberOfOptions the number of options the menu will have, remember to include the separators
 * @param output the stream that will be used to send the normal output, by default cout
 * @param input the stream that will be used to receive the normal input, by default cin
 * @param errorStream the stream that will be used to send error output, by default cerr
 */
Menu::Menu(int numberOfOptions, ostream &output, istream &input, ostream &errorStream):
        _numberOfOptions(numberOfOptions),
        _output(output),
        _input(input),
        _errorStream(errorStream){

    _menuElements = new MenuElement[_numberOfOptions];

}
/**
 * Class destructor, in charge of cleaning the memory
 */
Menu::~Menu() {
    delete[] _menuElements;

}
/**
 * Finds the maximum length of all menu options, the purpose is to be able to find how many
 * characters are needed for the separators
 * @return the length of the largest menu option (includes option and text)
 */
size_t Menu::MaxMenuLength() const {
    size_t max = 0;
    for (int i = 0; i < _numberOfOptions; ++i) {
        if(_menuElements[i].MenuElementWidth() > max){
            max = _menuElements[i].MenuElementWidth();
        }
    }
    return max;
}

/**
 * Sets the error message
 * @param errorMessage The error message when the user inputs a string when a number is expected
 */
void Menu::SetErrorMessage(const string &errorMessage) {
    _errorMessage = errorMessage;
}

/**
 * Sets the invalid option error message
 * @param invalidMessage The error message when the user inputs an option that is not in the menu
 */
void Menu::SetInvalidOption(const string &invalidMessage) {
    _invalidMessage = invalidMessage;

}

/**
 * Sets the input type of the Menu
 * @param type What kind of input the Menu will have, see line 33 to see the available options
 */
void Menu::SetInputType(InputType type) {
    _inputType = type;

}

/**
 * Sets the title of the Menu
 * @param title menu title
 */
void Menu::SetTitle(const string &title) {
    _menuTitle = title;

}

/**
 * Gets the Error Message
 * @return The error message when the user inputs a string when a number is expected
 */
string Menu::GetErrorMessage() const {
    return string(_errorMessage);
}

/**
 * Gets the Invalid Option error Message
 * @return The error message when the user inputs an option that is not in the menu
 */
string Menu::GetInvalidOption() const {
    return _invalidMessage;
}

/**
 * Gets the input type
 * @return What kind of input the Menu will have, see line 33 to see the available options
 */
InputType Menu::GetInputType() const {
    return _inputType;
}

/**
 * Gets the title
 * @return menu title
 */
string Menu::GetTitle() const {
    return string(_menuTitle);
}

/**
 * This method is to add options to the menu. If the user sends an invalid optionNumber the method will return INVALID_MENU_INDEX. Users of this method
 * should never use as displayOption 99 or E, since they are reserved values for exiting.
 * @param optionNumber the slot where the menu is to be added. This represents the position in the array, the method needs to validate that it is a valid position 0<=optionNumber<_numberOfOptions
 * @param displayOption what the user needs to input to select a given menu option
 * @param menuOption the actual text that will be display as a menu option
 * @return INVALID_MENU_INDEX if optionNumber is greater than or equal than numberOfOptions, OVERWROTE_OPTION if there was something already in that array position, the optionNumber otherwise
 */
int Menu::AddMenuOption(unsigned int optionNumber, const string &displayOption, const string &menuOption) {
    if(optionNumber >= _numberOfOptions){
        return INVALID_MENU_INDEX;
    }
    if(_menuElements[optionNumber].MenuElementWidth() != 1){
        _menuElements[optionNumber].SetMenuElement(displayOption,menuOption);
        return OVERWROTE_OPTION;
    }
    _menuElements[optionNumber].SetMenuElement(displayOption,menuOption);
    return optionNumber;

}

/**
 * This method adds a separator to the menu. The method will need to call MaxMenuLength to see how big the separator needs to be and set the separator character to '-'.
 * If the user sends an invalid separatorPosition the method will return INVALID_MENU_INDEX
 * @param separatorPosition the slot position where the separator is going to be stored. The method needs to validate that it is a valid position 0<=separatorPosition<numberOfOptions
 * @return INVALID_MENU_INDEX if separatorPosition >= _numberOfOptions, OVERWROTE_OPTION if the slot had something already in that position, separatorPosition otherwise
 */
int Menu::AddSeparator(unsigned int separatorPosition) {

//_menuElements->SetSeparator(MaxMenuLength(),'-');
    if (separatorPosition >= _numberOfOptions) {
        return INVALID_MENU_INDEX;
    }
    if (_menuElements[separatorPosition].GetSelectionOption() != "") {
        _menuElements[separatorPosition].SetSeparator(_menuOptionsWidth, '-');
        return OVERWROTE_OPTION;
    }
    else {
        _menuElements[separatorPosition].SetSeparator(MaxMenuLength(), '-');

        return separatorPosition;
    }

}

/**
 * This is the main driver of the class! This method will do the following operations:
 * 1. Output the Title
 * 2. Show all the menu options and separators
 * 3. Wait for the user to input the selection
 * 4. Return the user selection, or error appropriately
 * Remember you are outputting to _output, you are reading from _input and you are sending errors to _errorStream!
 * Furthermore, you will need to check what type of input the menu has, depending on that you will read numbers, a character or string.
 *      If your _inputType is INT and the user inputs a letter (or something that is not a number) then Run will return INPUT_ERROR
 *      If your _inputType is INT and the user inputs a number that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is CHAR and the user inputs a string of more than one letter then Run will return INPUT_ERROR
 *      If your _inputType is CHAR and the user inputs a letter that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is STRING and the user inputs a string that is not an available option then run will return INVALID_INPUT
 * @return the slot where the option has been stored (see optionNumber in AddMenuOption), if there is an error it will return the error value as noted above.
 */
int Menu::Run() const {
    /// Produces title
    _output << GetTitle() << '\n';
    /// Outputs the menu options
    for (int i = 0; i < _numberOfOptions; ++i) {
        _output << _menuElements[i].ToString() << endl;
    }
    /// For integers exit code
    if(_inputType == INT){
        _output << "99 Exit\n";
    }
    /// For string and character exit code
    if(_inputType == CHAR || _inputType == STRING){
        _output << "Type E to Exit\n";
    }
    string input;
    /// Gets input from testing
    while(_input >> input) {

        /// For integers
        if (_inputType == INT) {
            if(input == "99"){
                return EXIT;
            }
            if (!isdigit(input[0])) {
                _errorStream << _errorMessage + "\n";
                return INPUT_ERROR;
            }
            for (int i = 0; i < _numberOfOptions; ++i) {
                if(_menuElements[i].GetSelectionOption() == input) {
                    return i;
                }
            }
            _errorStream << _invalidMessage + "\n";
            return INVALID_INPUT;
        }
        /// For Characters
        if (_inputType == CHAR) {
            if(input == "E"){
                return EXIT;
            }
            if (input.length() > 1) {
                _errorStream << _errorMessage + "\n";
                return INPUT_ERROR;
            }
            for (int i = 0; i < _numberOfOptions; ++i) {
                if(_menuElements[i].GetSelectionOption() == input) {
                    return i;
                }
            }
            _errorStream << _invalidMessage + "\n";
            return INVALID_INPUT;
        }
        /// For Strings
        if (_inputType == STRING) {
            if(input == "E"){
                return EXIT;
            }
            for (int i = 0; i < _numberOfOptions; ++i) {
                if(_menuElements[i].GetSelectionOption() == input) {
                    return i;
                }
            }
            _errorStream << _invalidMessage + "\n";
            return INVALID_INPUT;
        }
    }
    return 0;
}
