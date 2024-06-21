#include <iostream>
#include <cstring>

using namespace std;

class BetterInteger {
public:
    int integer;

    explicit BetterInteger(int integer) : integer(integer) {}

    BetterInteger(const BetterInteger &other) {
        this->integer = other.integer;
    }

    BetterInteger &operator=(const BetterInteger &other) {
        if (this != &other) {
            this->integer = other.integer;
        }
    }

    void inplaceAddition(int num) { integer += num; }

    BetterInteger &operator+=(int toAdd) {
        this->integer += toAdd;
    }

    BetterInteger &operator+=(const BetterInteger &toAdd) {
        // betterInteger += otherBetterInteger
        this->integer += toAdd.integer;
    }

    void print() const { cout << "Better integer has a value of: " << integer << endl; }

    friend ostream &operator<<(ostream &os, BetterInteger &obj) {
        return os << "Better integer has a value of: " << obj.integer;
    }

    bool checkEqual(int num) const { return integer == num; };

    bool operator==(int num) const {
        return this->integer == num;
    }

    bool operator==(const BetterInteger &other) const {
        return this->integer == other.integer;
    }

    void increment() { integer++; }

    BetterInteger operator++(int) {
        BetterInteger toReturn(*this);
        this->integer++;
        return toReturn;
    }

    BetterInteger operator++() {
        this->integer++;
        return *this;
    }

    void decrement() { integer--; }
    
    BetterInteger operator--(int) {
        BetterInteger toReturn(*this);
        this->integer--;
        return toReturn;
    }

    BetterInteger operator--() {
        this->integer--;
        return *this;
    }

    // Other overloads
    BetterInteger &operator*=(int toAdd) {
        this->integer *= toAdd;
    }

    BetterInteger &operator-=(int toAdd) {
        this->integer *= toAdd;
    }

    friend istream &operator>>(istream &is, BetterInteger &obj) {
        return is >> obj.integer;
    }
};

int main() {
    /* Задача: Да имплементираме класа BetterInteger која има
     *  една променлива integer:int, и за неа ќе има:
     *  increment, decrement, inplace addition,
     *  printing, and checkEqual.
     *  Истото да го направиме со преоптоварување на оператори.
     */
    cout << "Input initial integer value: " << endl;
    int integer;
    cin >> integer;
    BetterInteger betterInteger(integer);

    cout << "Start giving commands! " << endl;
    char command[30];
    while (true) {
        cin >> command;
        if (strcmp("++", command) == 0) {
            betterInteger++;
        } else if (strcmp("--", command) == 0) {
            betterInteger--;
        } else if (strcmp("==", command) == 0) {
            int num;
            cin >> num;
            cout << (betterInteger == num) << endl;
            continue;
        } else if (strcmp("+=", command) == 0) {
            int toAdd;
            cin >> toAdd;
            betterInteger += toAdd;
        } else if (strcmp(">>", command) == 0) {
            cin >> betterInteger;
        } else {
            cout << " NO MORE INPUTS" << endl;
            break;
        }
        cout << betterInteger << endl;
    }
}
