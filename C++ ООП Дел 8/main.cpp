#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class Vehicle {
protected:
    bool isEfficient;
    char *color;
    char *type; //SUV, Sedan, Sport, Sportback

    void copy(const Vehicle &r) {
        delete[] color;
        delete[] type;
        color = new char[strlen(r.getColor()) + 1];
        type = new char[strlen(r.getType()) + 1];
        strcpy(color, r.getColor());
        strcpy(type, r.getType());
        isEfficient = r.getEfficiency();
    }

public:
    Vehicle(const bool isEfficient = false, const char *color = "no_color",
            const char *type = "no_type")
            : isEfficient(isEfficient),
              color(new char[strlen(color) + 1]),
              type(new char[strlen(type) + 1]) {
        strcpy(this->color, color);
        strcpy(this->type, type);
    }

    Vehicle(const Vehicle &other) {
        color = nullptr;
        type = nullptr;
        copy(other);
    }

    Vehicle &operator=(const Vehicle &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    ~Vehicle() {
        delete[] color;
        delete[] type;
    }

    char *getColor() const { return color; }

    char *getType() const { return type; }

    bool getEfficiency() const { return isEfficient; }

    virtual void print() {
        printf("Color: %s, Type: %s, the vehicle is%s efficient, ",
               color, type,
               isEfficient ? "" : " not");
    }

    virtual Vehicle* clone() const = 0;
};

class GasolineVehicle : public Vehicle {
private:
    float L100Km;
    char *engine; //V6, V8, V10, V12, Straight6, Straight3

    void copy(const GasolineVehicle &r) {
        delete[] engine;
        engine = new char[strlen(r.getEngine()) + 1];
        strcpy(engine, r.engine);
        L100Km = r.getL100Km();
    }

public:
    explicit GasolineVehicle(const bool efficient = false, const char *color = "no_color",
                             const char *type = "no_type", const float L100Km = -9999,
                             const char *engine = "unknown_engine")
            : Vehicle(efficient, color, type), L100Km(L100Km), engine(new char[strlen(engine) + 1]) {
        strcpy(this->engine, engine);
    }

    GasolineVehicle(const GasolineVehicle &other) : Vehicle(other) {
        engine = nullptr;
        copy(other);
    }

    GasolineVehicle &operator=(const GasolineVehicle &other) {
        if (this != &other) {
            Vehicle::operator=(other);
            copy(other);
        }
        return *this;
    }

    ~GasolineVehicle() {
        delete[] engine;
    }

    void print() override {
        Vehicle::print();
        printf("Engine: %s, L/100Km: %.2f\n", engine, L100Km);
    }

    char *getEngine() const { return engine; }

    float getL100Km() const { return L100Km; }

    Vehicle* clone() const{
        return new GasolineVehicle(*this);
    }
};

class ElectricVehicle : public Vehicle {
private:
    int range;
    char *battery; //lithium, nickel

    void copy(const ElectricVehicle &r) {
        delete[] battery;
        battery = new char[strlen(r.getBattery()) + 1];
        strcpy(battery, r.getBattery());
        range = r.getRange();
    }

public:
    explicit ElectricVehicle(const bool efficient = false, const char *color = "no_color",
                             const char *type = "no_type", const int range = -9999,
                             const char *battery = "no_battery")
            : Vehicle(efficient, color, type), range(range), battery(new char[strlen(battery) + 1]) {
        strcpy(this->battery, battery);
    }

    ElectricVehicle(const ElectricVehicle &other) : Vehicle(other) {
        battery = nullptr;
        copy(other);
    }

    ElectricVehicle &operator=(const ElectricVehicle &other) {
        if (this != &other) {
            Vehicle::operator=(other);
            copy(other);
        }
        return *this;
    }

    void print() override {
        Vehicle::print();
        printf("Battery: %s, Range: %d\n", battery, range);
    }

    ~ElectricVehicle() {
        delete[] battery;
    }

    int getRange() const { return range; }

    char *getBattery() const { return battery; }

    Vehicle* clone() const {
        return new ElectricVehicle(*this);
    }
};

#define MAX_VEHICLES 30

class Dealership {
private:
    char *name = nullptr;
    int numVehicles;
    Vehicle* *vehicles;
public:
    explicit Dealership(const char *name = "no_dealership_name")
            : name(new char[strlen(name) + 1]) {
        strcpy(this->name, name);
        numVehicles = 0;
        vehicles = nullptr;
    }

    void addVehicle(const Vehicle &toAdd){
        Vehicle* *temp = new Vehicle*[numVehicles + 1];
        for (int i = 0; i < numVehicles; ++i) {
            temp[i] = vehicles[i];
        }
        temp[numVehicles] = toAdd.clone();
        numVehicles++;
        delete [] vehicles;
        vehicles = temp;
    }

    void displayVehicles(){
        printf("----%s----\n", name);
        for (int i = 0; i < numVehicles; ++i) {
            vehicles[i]->print();
        }
    }

    ~Dealership() {
        for (int i = 0; i < numVehicles; ++i) {
            delete vehicles[i];
        }
        delete [] vehicles;
        delete[] name;
    }
    /** За да работи кодот во продолжение мора да го избришете методот
     * кој ја прави класата Vehicle абстрактна
     * */
/*
private:
    Vehicle slicedVehicles[MAX_VEHICLES];
    int numSlicedVehicles = 0;
public:
    void addSlicedVehicle(const Vehicle &toAdd){
        slicedVehicles[numVehicles] = toAdd;
    }

    void displaySlicedVehicles(){
        for (int i = 0; i < numSlicedVehicles; ++i) {
            slicedVehicles[i].print();
        }
    }*/
};

int main() {
    char color[100];
    char type[100];
    char engine[100];
    char battery[100];
    bool isEfficient;
    float L100Km;
    int id, range;

    Dealership dealership = Dealership("Marko's Car Dealership");

    cout << "---Start---\n";
    while (true) {
        cin >> id;
        if (id == 1 || id == 2) {
            cin >> color;
            cin >> type;
            cin >> isEfficient;
            if (id == 1) {
                // It's a Gasoline
                cin >> engine;
                cin >> L100Km;
                //TODO Call the add method:
                dealership.addVehicle(GasolineVehicle(isEfficient,color,type,L100Km,engine));
            } else if (id == 2) {
                //Electric
                cin >> battery;
                cin >> range;
                //TODO Call the add method:
                dealership.addVehicle(ElectricVehicle(isEfficient,color,type,range,battery));
            }
        } else {
            break;
        }
    }

    dealership.displayVehicles();
}
