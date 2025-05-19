#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс B1 - Транспортное средство
class B1 {
protected:
    string brand;
    int year;

public:
    B1(const string& b, int y) : brand(b), year(y) {}
    virtual ~B1() {}

    virtual void display() const {
        cout << "Brand: " << brand << ", Year: " << year;
    }

    string getBrand() const { return brand; }
    int getYear() const { return year; }
};

// Класс B2 - Двигатель
class B2 {
protected:
    string engineType;
    int horsepower;

public:
    B2(const string& et, int hp) : engineType(et), horsepower(hp) {}

    void displayEngine() const {
        cout << "Engine: " << engineType << ", Horsepower: " << horsepower;
    }

    string getEngineType() const { return engineType; }
    int getHorsepower() const { return horsepower; }
};

// Класс D1 - Легковой автомобиль (наследует B1 и B2)
class D1 : public B1, public B2 {
protected:
    int numDoors;

public:
    D1(const string& b, int y, const string& et, int hp, int doors)
        : B1(b, y), B2(et, hp), numDoors(doors) {}

    void display() const override {
        B1::display();
        cout << ", ";
        B2::displayEngine();
        cout << ", Doors: " << numDoors << endl;
    }

    int getNumDoors() const { return numDoors; }
};

// Класс D2 - Грузовик (наследует D1)
class D2 : public D1 {
private:
    double cargoCapacity;

public:
    D2(const string& b, int y, const string& et, int hp, int doors, double capacity)
        : D1(b, y, et, hp, doors), cargoCapacity(capacity) {}

    void display() const override {
        D1::display();
        cout << "Cargo capacity: " << cargoCapacity << " tons" << endl;
    }

    double getCargoCapacity() const { return cargoCapacity; }
};

// Класс D3 - Гоночный автомобиль (наследует D2 и B2)
class D3 : public D2, public B2 {
private:
    double topSpeed;

public:
    D3(const string& b, int y, const string& et1, int hp1, int doors,
        double capacity, const string& et2, int hp2, double speed)
        : D2(b, y, et1, hp1, doors, capacity),
        B2(et2, hp2), topSpeed(speed) {}

    void display() const override {
        D2::display();
        cout << "Secondary ";
        B2::displayEngine();
        cout << ", Top speed: " << topSpeed << " km/h" << endl;
    }

    double getTopSpeed() const { return topSpeed; }
};

int main() {
    // Создаем массив указателей на базовый класс B1
    vector<B1*> vehicles;

    vehicles.push_back(new B1("Generic Vehicle", 2000));
    vehicles.push_back(new D1("Toyota Camry", 2020, "V6", 300, 4));
    vehicles.push_back(new D2("Volvo Truck", 2019, "Diesel", 450, 2, 15.5));
    vehicles.push_back(new D3("Ferrari F1", 2022, "V8", 800, 2, 0.5, "Electric", 1200, 350));

    // Демонстрация работы с массивом объектов
    cout << "Vehicle list:\n=================\n";
    for (const auto& vehicle : vehicles) {
        vehicle->display();
        cout << "\n-----------------\n";
    }

    // Освобождение памяти
    for (auto vehicle : vehicles) {
        delete vehicle;
    }

    return 0;
}