#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

class CharacterNotAllowedException {
public:
    char invalidChar;
    char invalidString[30];

    CharacterNotAllowedException(const char invalidChar = '?', const char *invalidString = "invalid_string") {
        this->invalidChar = invalidChar;
        strcpy(this->invalidString, invalidString);
    }

    void print_err() {
        cout << "Found invalid char: " << invalidChar << ", in string: " << invalidString << endl;
    }
};

class OnlyLettersString {
public:
    char ols[30];

    OnlyLettersString(const char *ols = "onlyLetters") {
        for (int i = 0; i < strlen(ols); ++i) {
            if (!isalpha(ols[i])) {
                throw CharacterNotAllowedException(ols[i], ols);
            }
        }
        strcpy(this->ols, ols);
    }

    void tellEveryoneConstructorIsWorking() {
        cout << "Constructor working fine!!!";
    }

    void show() {
        cout << ols << endl;
    }
};

int main() {
    char input[30];
    while (true) {
        cin >> input;
        try {
            OnlyLettersString temp = OnlyLettersString(input);
            temp.show();
        } catch (CharacterNotAllowedException e) {
            e.print_err();
        }
    }
}
