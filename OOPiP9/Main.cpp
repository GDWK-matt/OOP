#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <windows.h>
using namespace std;

// ����� ��� ������ � �����
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

// ������� ����� ��� ��������
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
        return name + " (����: " + to_string(price) + " ���., ����� ��: " + expirationDate.toString() + ")";
    }

    int getPrice() const { return price; }
    string getName() const { return name; }
    bool needsPrescription() const { return prescriptionRequired; }
};

// ����� ��� ��������
class Pill : public Medicine {
private:
    int quantity;
    string dosage;
public:
    Pill(string n, int p, Date exp, int q, string d, bool pr = false)
        : Medicine(n, p, exp, pr), quantity(q), dosage(d) {
    }

    string getInfo() const override {
        return "�������� " + Medicine::getInfo() +
            ", ����������: " + to_string(quantity) + " ��., ���������: " + dosage;
    }
};

// ����� ��� �������
class Syrup : public Medicine {
private:
    double volume; // � ��
    string flavor;
public:
    Syrup(string n, int p, Date exp, double v, string f, bool pr = false)
        : Medicine(n, p, exp, pr), volume(v), flavor(f) {
    }

    string getInfo() const override {
        return "����� " + Medicine::getInfo() +
            ", �����: " + to_string(volume) + " ��, ����: " + flavor;
    }
};

// ������� ��� ��������� �������� �� �����
class MedicineNameComparator {
private:
    string nameToFind;
public:
    MedicineNameComparator(const string& name) : nameToFind(name) {}

    bool operator()(Medicine* med) const {
        return med->getName() == nameToFind;
    }
};

// ����� ������
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

    int getOrderId() const { return orderId; }  // ����������� �����

    void addMedicine(Medicine* med) {
        if (med->isExpired()) {
            cout << "��������������: " << med->getName() << " � �������� ������ �������� �� ��������!" << endl;
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
        cout << "����� #" << orderId << " �� " << orderDate.toString() << ":" << endl;
        for (const auto& med : medicines) {
            cout << "  - " << med->getInfo() << endl;
        }
        cout << "�����: " << calculateTotal() << " ���." << endl;
    }
};

// ����� ������
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
        cout << "������ '" << name << "' �� ������: " << address << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // ������� ������
    Pharmacy pharmacy("��������+", "��. �������, 15");
    pharmacy.printInfo();

    // ������� �����
    Date today(20, 5, 2024);
    PharmacyOrder* order = pharmacy.createOrder(today);

    // ������� ���������
    Medicine* aspirin = new Pill("�������", 150, Date(31, 12, 2025), 20, "500 ��");
    Medicine* nurofen = new Syrup("�������", 320, Date(30, 6, 2027), 150, "��������");
    Medicine* amoxicillin = new Pill("������������", 450, Date(15, 3, 2024), 10, "250 ��", true);

    // ��������� ��������� � �����
    order->addMedicine(aspirin);
    order->addMedicine(nurofen);
    order->addMedicine(amoxicillin);

    // ������� ���������� � ������
    cout << "\n������� �����:" << endl;
    order->printOrder();

    // ������� ��������� �� ������
    if (order->removeMedicine("�������")) {
        cout << "\n������� ������ �� ������" << endl;
    }

    // ������� ����������� �����
    cout << "\n����������� �����:" << endl;
    order->printOrder();

    return 0;
}