#include <iostream>
#include <string.h>

using namespace std;

class Person {
public:
    char name[30];
    char surname[30];
    int age;
    float balance;

    Person(char *name, char *surname, int age, float balance) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->age = age;
        this->balance = balance;
    }

    void describePerson(){
        cout << this->name << " " << this->surname << " is "
             << this->age << " years old and has a balance of $" << this->balance << endl;
    }
};

int main() {
    /** Задача: Да напривме класа што ќе може да се користи за да опишеме еден човек.
     * Човекот има 4 атрибути (карактеристики) и тоа:
     *  име:char[]
     *  прзеиме:char[]
     *  возраст:int,
     *  салдо:float,
     *
     *  Од стандарден влез се чита името, презимето, возраста и салдото. Пример:
     *  Marko
     *  Georgiev
     *  20
     *  10000
     *  Наша задача е да го прикажеме човекот на стандарден излез во следниот формат:
     *  Marko Georgiev is 20 years old and has a balance of $10000.
     * */

    char name[30];
    char surname[30];
    int age;
    float balance;

    cin >> name;
    cin >> surname;
    cin >> age;
    cin >> balance;
    //cout << name << " " << surname << " " << age  << " " << balance;

    Person person1 = Person(name, surname, age, balance);
    // First way:
    cout << person1.name << " " << person1.surname << " is "
         << person1.age << " years old and has a balance of $" << person1.balance << endl;
    //Second way:
    person1.describePerson();
}
