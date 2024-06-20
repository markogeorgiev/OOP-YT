#include <iostream>
#include <string.h>

using namespace std;

class Device {
public:
    char name[30];
    float price;

    Device(const float price, const char *name) : price(price) {
        strcpy(this->name, name);
    }

    void print() {
        cout << "Device name: " << this->name << ", costs " << price << endl;
    }
};

class Samsung : public Device{
public:
    int numCameras;

    Samsung(float price,char *name, int numCameras) : Device(price,name), numCameras(numCameras) {}

    int getNumCameras() {
        cout << name << " has " << numCameras << " cameras" << endl;
        return numCameras;
    }
};

int main() {
    Device iPhone(399, "iPhone 13");
    iPhone.print();

    Samsung s24(1200, "Samsung S24 Ultra", 4);
    s24.print();
    s24.getNumCameras();
}

