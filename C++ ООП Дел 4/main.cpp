#include <iostream>
#include <cstring>

using namespace std;

#define INDEX_SIZE 7

class Student {
private:
    char* name;
    char* surname;
    int startYear;
    char index[INDEX_SIZE];

    void copy(const Student &student){
        name = new char[strlen(student.getName()) + 1];
        surname = new char[strlen(student.getSurname()) + 1];

        strcpy(name, student.getName());
        strcpy(surname,student.getSurname());
        strcpy(index, student.getIndex());
        startYear = student.getStartYear();
    }

public:
    Student(const char* name = "N0_NAME",
            const char* surname = "NO_SURNAME",
            const int startYear = -1,
            const char* index = "?????"){
        this->name = new char[strlen(name) + 1];
        this->surname = new char[strlen(surname) + 1];

        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->startYear = startYear;
        strcpy(this->index,index);
    }

    Student(const Student &student){
        name = nullptr;
        surname = nullptr;
        copy(student);
    }

    Student& operator = (const Student &student){
        if (this != &student){
            delete [] name;
            delete [] surname;
            copy(student);
        }
    }


    ~Student(){
        delete [] name;
        delete [] surname;
    }

    void print(){
        // FORMAT: Name: [name] [surname] - [index] ([startYear])
        printf("Name: %s %s - %s (%d)\n", name, surname, index, startYear);
    }

    char *getName() const { return name; }

    char *getSurname() const { return surname; }

    int getStartYear() const { return startYear; }

    const char *getIndex() const { return index; }
};

int main() {
     /* Задача 1: Да креираме класа која опишува еден студент.
         Секој студент има:
         - име:динамички алоцирана низа од карактери
         - презиме:динамички алоцирана низа од карактери
         - година на запишување:int
         - Индекс:низа од 6 карактери
    
        Задача 2: Да дефинираме copy конструктор и да
         преоптовариме = оператор, конструктор со аргументи и
         деструктор. Дефинирајте уште еден метод void print(), за печатење на
         сите информации во следниот формат:
     FORMAT: Name: [name] [surname] - [index] ([startYear])*/


    Student student1("Marko", "Georgiev", 2011, "111111");
    Student student2("Damjan", "Dimovski", 2033, "333333");
    Student copycat(student1);

    cout << "Marko: " << endl;
    student1.print();
    cout << "Damjan: " << endl;
    student2.print();
    cout << "Copycat copying Marko: " << endl;
    copycat.print();

    cout << "Copycat = Damjan: " << endl;
    copycat = student2;
    copycat.print();
}
