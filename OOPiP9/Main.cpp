#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <windows.h>
using namespace std;

// Класс для работы с датой
class Date {
private:
    int day, month, year;
public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    bool isExpired() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int currentYear = 1900 + ltm->tm_year;
        int currentMonth = 1 + ltm->tm_mon;
        int currentDay = ltm->tm_mday;

        if (year < currentYear) return true;
        if (year == currentYear && month < currentMonth) return true;
        if (year == currentYear && month == currentMonth && day < currentDay) return true;
        return false;
    }

    string toString() const {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }
};

// Базовый класс для лекарств
class Medicine {
protected:
    string name;
    int price;
    Date expirationDate;
    bool prescriptionRequired;
public:
    Medicine(string n, int p, Date exp, bool pr = false)
        : name(n), price(p), expirationDate(exp), prescriptionRequired(pr) {
    }

    virtual ~Medicine() {}

    bool isExpired() const {
        return expirationDate.isExpired();
    }

    virtual string getInfo() const {
        return name + " (Цена: " + to_string(price) + " руб., Годен до: " + expirationDate.toString() + ")";
    }

    int getPrice() const { return price; }
    string getName() const { return name; }
    bool needsPrescription() const { return prescriptionRequired; }
};

// Класс для таблеток
class Pill : public Medicine {
private:
    int quantity;
    string dosage;
public:
    Pill(string n, int p, Date exp, int q, string d, bool pr = false)
        : Medicine(n, p, exp, pr), quantity(q), dosage(d) {
    }

    string getInfo() const override {
        return "Таблетки " + Medicine::getInfo() +
            ", Количество: " + to_string(quantity) + " шт., Дозировка: " + dosage;
    }
};

// Класс для сиропов
class Syrup : public Medicine {
private:
    double volume; // в мл
    string flavor;
public:
    Syrup(string n, int p, Date exp, double v, string f, bool pr = false)
        : Medicine(n, p, exp, pr), volume(v), flavor(f) {
    }

    string getInfo() const override {
        return "Сироп " + Medicine::getInfo() +
            ", Объем: " + to_string(volume) + " мл, Вкус: " + flavor;
    }
};

// Функтор для сравнения лекарств по имени
class MedicineNameComparator {
private:
    string nameToFind;
public:
    MedicineNameComparator(const string& name) : nameToFind(name) {}

    bool operator()(Medicine* med) const {
        return med->getName() == nameToFind;
    }
};

// Класс заказа
class PharmacyOrder {
private:
    int orderId;
    Date orderDate;
    vector<Medicine*> medicines;
public:
    PharmacyOrder(int id, Date date) : orderId(id), orderDate(date) {}
    ~PharmacyOrder() {
        for (auto med : medicines) {
            delete med;
        }
    }

    int getOrderId() const { return orderId; }  // Добавленный метод

    void addMedicine(Medicine* med) {
        if (med->isExpired()) {
            cout << "Предупреждение: " << med->getName() << " с истекшим сроком годности не добавлен!" << endl;
            delete med;
            return;
        }
        medicines.push_back(med);
    }

    bool removeMedicine(const string& name) {
        MedicineNameComparator comparator(name);
        auto it = find_if(medicines.begin(), medicines.end(), comparator);

        if (it != medicines.end()) {
            delete* it;
            medicines.erase(it);
            return true;
        }
        return false;
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& med : medicines) {
            total += med->getPrice();
        }
        return total;
    }

    void printOrder() const {
        cout << "Заказ #" << orderId << " от " << orderDate.toString() << ":" << endl;
        for (const auto& med : medicines) {
            cout << "  - " << med->getInfo() << endl;
        }
        cout << "Итого: " << calculateTotal() << " руб." << endl;
    }
};

// Класс аптеки
class Pharmacy {
private:
    string name;
    string address;
    vector<PharmacyOrder*> orders;
    int nextOrderId;
public:
    Pharmacy(string n, string addr) : name(n), address(addr), nextOrderId(1) {}
    ~Pharmacy() {
        for (auto order : orders) {
            delete order;
        }
    }

    PharmacyOrder* createOrder(Date date) {
        PharmacyOrder* order = new PharmacyOrder(nextOrderId++, date);
        orders.push_back(order);
        return order;
    }

    PharmacyOrder* getOrder(int id) const {
        for (auto order : orders) {
            if (order->getOrderId() == id) {
                return order;
            }
        }
        return nullptr;
    }

    void printInfo() const {
        cout << "Аптека '" << name << "' по адресу: " << address << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Создаем аптеку
    Pharmacy pharmacy("Здоровье+", "ул. Пушкина, 15");
    pharmacy.printInfo();

    // Создаем заказ
    Date today(20, 5, 2024);
    PharmacyOrder* order = pharmacy.createOrder(today);

    // Создаем лекарства
    Medicine* aspirin = new Pill("Аспирин", 150, Date(31, 12, 2025), 20, "500 мг");
    Medicine* nurofen = new Syrup("Нурофен", 320, Date(30, 6, 2027), 150, "апельсин");
    Medicine* amoxicillin = new Pill("Амоксициллин", 450, Date(15, 3, 2024), 10, "250 мг", true);

    // Добавляем лекарства в заказ
    order->addMedicine(aspirin);
    order->addMedicine(nurofen);
    order->addMedicine(amoxicillin);

    // Выводим информацию о заказе
    cout << "\nТекущий заказ:" << endl;
    order->printOrder();

    // Удаляем лекарство из заказа
    if (order->removeMedicine("Аспирин")) {
        cout << "\nАспирин удален из заказа" << endl;
    }

    // Выводим обновленный заказ
    cout << "\nОбновленный заказ:" << endl;
    order->printOrder();

    return 0;
}