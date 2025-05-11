#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Person {
protected:
    std::string name;
    int age;
    float grade; // Average grade

public:
    Person(std::string name, int age, float grade)
        : name(name), age(age), grade(grade) {}

    virtual void display() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Average grade: " << grade << std::endl;
    }

    virtual void saveToFile(std::ofstream& file) const {
        file << "Name: " << name << ", Age: " << age << ", Average grade: " << grade << std::endl;
    }

    float getGrade() const { return grade; }
};

class SchoolStudent : public Person {
public:
    SchoolStudent(std::string name, int age, float grade)
        : Person(name, age, grade) {}

    void display() const override {
        std::cout << "[School Student] ";
        Person::display();
    }

    void saveToFile(std::ofstream& file) const override {
        file << "[School Student] ";
        Person::saveToFile(file);
    }
};

class CollegeStudent : public Person {
public:
    CollegeStudent(std::string name, int age, float grade)
        : Person(name, age, grade) {}

    void display() const override {
        std::cout << "[College Student] ";
        Person::display();
    }

    void saveToFile(std::ofstream& file) const override {
        file << "[College Student] ";
        Person::saveToFile(file);
    }
};

class UniversityStudent : public Person {
public:
    UniversityStudent(std::string name, int age, float grade)
        : Person(name, age, grade) {}

    void display() const override {
        std::cout << "[University Student] ";
        Person::display();
    }

    void saveToFile(std::ofstream& file) const override {
        file << "[University Student] ";
        Person::saveToFile(file);
    }
};

void saveBestToFile(const std::vector<Person*>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    Person* bestStudent = nullptr;
    for (const auto& student : students) {
        if (!bestStudent || student->getGrade() > bestStudent->getGrade()) {
            bestStudent = student;
        }
    }

    if (bestStudent) {
        std::cout << "Top-performing student:\n";
        bestStudent->display();
        file << "Top-performing student:\n";
        bestStudent->saveToFile(file);
    }

    file.close();
}

int main() {
    std::vector<Person*> students = {
        new SchoolStudent("Ivan", 14, 6.7),
        new CollegeStudent("Maria", 18, 6.8),
        new UniversityStudent("Andrei", 21, 7.2),
        new SchoolStudent("Oleg", 15, 5.9),
        new CollegeStudent("Elena", 19, 7.7),
        new UniversityStudent("Pavel", 22, 8.6)
    };

    std::ofstream file("students.txt");
    if (!file) {
        std::cerr << "Error opening file students.txt" << std::endl;
        return 1;
    }

    std::cout << "List of students:\n";
    for (const auto& student : students) {
        student->display();
        student->saveToFile(file);
    }

    file.close();

    saveBestToFile(students, "best_student.txt");

    for (auto& student : students) {
        delete student;
    }

    return 0;
}