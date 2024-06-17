#include <iostream>
#include <cstring>

#include <cstdlib>

#define MAX_MESSAGE_SIZE 30

using namespace std;

class ThreeMessages {
private:
    char regular[MAX_MESSAGE_SIZE];
    char *dynamicWithNew;
    char *dynamicWithMalloc;
public:
    ThreeMessages(const char *reg = "DEFAULT_REGULAR",
                  const char *dynNew = "DEFAULT_DYN_NEW",
                  const char *dynMalloc = "DEFAULT_DYN_MALLOC"){

        // Static memory allocation
        strcpy(this->regular, reg);
        this->regular[sizeof(regular) - 1] = '\0';

        // Dynamic memory allocation with New
        dynamicWithNew = new char[strlen(dynNew) + 1];
        strcpy(dynamicWithNew, dynNew);

        // Dynamic memory allocation with Malloc
        dynamicWithMalloc = (char *) malloc(strlen(dynMalloc) + 1);
        if (dynamicWithMalloc != nullptr){
            strcpy(dynamicWithMalloc, dynMalloc);
        }
    }

    ~ThreeMessages(){
        delete[] dynamicWithNew;
        free(dynamicWithMalloc);
    }

    const char *getRegular() const { return regular; }

    const char *getDynamicWithNew() const { return dynamicWithNew; }

    const char *getDynamicWithMalloc() const { return dynamicWithMalloc; }

    void setRegular(const char *reg) {
        strcpy(regular, reg);
        regular[sizeof(regular) - 1] = '\0';
    }

    void setDynamicWithNew(const char *dynNew){
        delete[] dynamicWithNew;
        dynamicWithNew = new char[strlen(dynNew) + 1];
        strcpy(dynamicWithNew, dynNew);
    }

    void setDynamicWithMalloc(const char *dynMalloc) {
        free(dynamicWithMalloc);
        dynamicWithMalloc = (char *) malloc(strlen(dynMalloc) + 1);
        if (dynamicWithMalloc != nullptr) {
            strcpy(dynamicWithMalloc, dynMalloc);
        }
    }
};

int main() {
    ThreeMessages tm("Regular", "Dynamic With New", "Dynamic With Malloc");
    

    cout << "Message1: " << tm.getRegular() << endl;
    cout << "Message2: " << tm.getDynamicWithNew() << endl;
    cout << "Message3: " << tm.getDynamicWithMalloc() << endl;

    tm.setRegular("Changed Regular");
    tm.setDynamicWithNew("Changed Dynamic With New");
    tm.setDynamicWithMalloc("Changed Dynamic With Malloc");

    cout << "Changed Message1: " << tm.getRegular() << endl;
    cout << "Changed Message2: " << tm.getDynamicWithNew() << endl;
    cout << "Changed Message3: " << tm.getDynamicWithMalloc() << endl;

    // Default Constructor works as intended.
    ThreeMessages td;
    cout << "Message1: " << td.getRegular() << endl;
    cout << "Message2: " << td.getDynamicWithNew() << endl;
    cout << "Message3: " << td.getDynamicWithMalloc() << endl;

    return 0;
}
