#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <iomanip>

// ������������ ��� ��������
enum class Platform {
    iOS,
    Android,
    WindowsMobile,
    Unknown
};

// ������������ ��� ������ ����������
enum class DevelopmentLanguage {
    Swift,
    Kotlin,
    Java,
    CSharp,
    Dart,
    JavaScript,
    Unknown
};

// ��������� ����� ��� �������� ������� ��������� (��� ���������� ����������)
template <typename T>
class ChangeHistory {
private:
    std::vector<T> history;

public:
    ChangeHistory() = default;

    void addState(const T& state) {
        history.push_back(state);
    }

    T getLastState() {
        if (history.empty()) {
            throw std::runtime_error("History is empty");
        }
        return history.back();
    }

    T rollback() {
        if (history.size() <= 1) {
            throw std::runtime_error("Nothing to rollback");
        }
        history.pop_back();
        return history.back();
    }

    void clear() {
        history.clear();
    }
};

// ����� ������������
class Developer {
private:
    std::string name;
    std::string email;
    int experienceYears;

public:
    Developer() : name(""), email(""), experienceYears(0) {}
    Developer(const std::string& name, const std::string& email, int exp)
        : name(name), email(email), experienceYears(exp) {
    }
    Developer(const Developer& other)
        : name(other.name), email(other.email), experienceYears(other.experienceYears) {
    }

    ~Developer() = default;

    // �������
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getExperienceYears() const { return experienceYears; }

    // �������
    void setName(const std::string& newName) { name = newName; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setExperienceYears(int years) { experienceYears = years; }

    void displayInfo() const {
        std::cout << "Developer: " << name << " (" << email << "), "
            << experienceYears << " years of experience\n";
    }
};

// ����� ��� ���������� � ������
class VersionInfo {
private:
    int major;
    int minor;
    int patch;

public:
    VersionInfo() : major(1), minor(0), patch(0) {}
    VersionInfo(int maj, int min, int pat) : major(maj), minor(min), patch(pat) {}
    VersionInfo(const VersionInfo& other)
        : major(other.major), minor(other.minor), patch(other.patch) {
    }

    ~VersionInfo() = default;

    // �������
    int getMajor() const { return major; }
    int getMinor() const { return minor; }
    int getPatch() const { return patch; }

    // �������
    void setMajor(int maj) { major = maj; }
    void setMinor(int min) { minor = min; }
    void setPatch(int pat) { patch = pat; }

    std::string toString() const {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
};

// ������� ����� ��� ���������� ����������
class MobileApp {
protected:
    std::string name;
    Platform platform;
    DevelopmentLanguage language;
    VersionInfo version;
    std::shared_ptr<Developer> developer;
    double price;
    ChangeHistory<std::string> nameHistory;

public:
    MobileApp() : name(""), platform(Platform::Unknown), language(DevelopmentLanguage::Unknown),
        version(), developer(nullptr), price(0.0) {
    }

    MobileApp(const std::string& name, Platform plt, DevelopmentLanguage lang,
        const VersionInfo& ver, std::shared_ptr<Developer> dev, double pr)
        : name(name), platform(plt), language(lang), version(ver), developer(dev), price(pr) {
        nameHistory.addState(name);
    }

    MobileApp(const MobileApp& other)
        : name(other.name), platform(other.platform), language(other.language),
        version(other.version), developer(other.developer), price(other.price),
        nameHistory(other.nameHistory) {
    }

    virtual ~MobileApp() = default;

    // �������
    std::string getName() const { return name; }
    Platform getPlatform() const { return platform; }
    DevelopmentLanguage getLanguage() const { return language; }
    VersionInfo getVersion() const { return version; }
    std::shared_ptr<Developer> getDeveloper() const { return developer; }
    double getPrice() const { return price; }

    // ������� � ���������� � ����������� �������
    void setName(const std::string& newName) {
        if (newName.empty()) {
            throw std::invalid_argument("App name cannot be empty");
        }
        nameHistory.addState(name);
        name = newName;
    }

    void setPlatform(Platform plt) {
        if (plt == Platform::Unknown) {
            throw std::invalid_argument("Invalid platform");
        }
        platform = plt;
    }

    void setLanguage(DevelopmentLanguage lang) {
        if (lang == DevelopmentLanguage::Unknown) {
            throw std::invalid_argument("Invalid development language");
        }
        language = lang;
    }

    void setVersion(const VersionInfo& ver) { version = ver; }
    void setDeveloper(std::shared_ptr<Developer> dev) { developer = dev; }
    void setPrice(double pr) { price = pr; }

    // ����� �����
    void rollbackName() {
        name = nameHistory.rollback();
    }

    // ����������� ����� ��� ����������� ����������
    virtual void displayInfo() const {
        std::cout << "App: " << name << "\n";
        std::cout << "Platform: " << platformToString(platform) << "\n";
        std::cout << "Language: " << languageToString(language) << "\n";
        std::cout << "Version: " << version.toString() << "\n";
        if (developer) {
            developer->displayInfo();
        }
        std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    }

    // ����������� ������ ��� �������������� enum � ������
    static std::string platformToString(Platform plt) {
        static const std::map<Platform, std::string> platformNames = {
            {Platform::iOS, "iOS"},
            {Platform::Android, "Android"},
            {Platform::WindowsMobile, "Windows Mobile"},
            {Platform::Unknown, "Unknown"}
        };
        return platformNames.at(plt);
    }

    static std::string languageToString(DevelopmentLanguage lang) {
        static const std::map<DevelopmentLanguage, std::string> languageNames = {
            {DevelopmentLanguage::Swift, "Swift"},
            {DevelopmentLanguage::Kotlin, "Kotlin"},
            {DevelopmentLanguage::Java, "Java"},
            {DevelopmentLanguage::CSharp, "C#"},
            {DevelopmentLanguage::Dart, "Dart"},
            {DevelopmentLanguage::JavaScript, "JavaScript"},
            {DevelopmentLanguage::Unknown, "Unknown"}
        };
        return languageNames.at(lang);
    }
};

// ����� ��� �������� ��������� ����������
class AppCollection {
private:
    std::vector<std::shared_ptr<MobileApp>> apps;

public:
    AppCollection() = default;
    AppCollection(const AppCollection& other) : apps(other.apps) {}
    ~AppCollection() = default;

    void addApp(std::shared_ptr<MobileApp> app) {
        apps.push_back(app);
    }

    void removeApp(const std::string& appName) {
        apps.erase(std::remove_if(apps.begin(), apps.end(),
            [&appName](const std::shared_ptr<MobileApp>& app) {
                return app->getName() == appName;
            }), apps.end());
    }

    void displayAll() const {
        std::cout << "\n=== All Mobile Applications ===\n";
        displayTableHeader();
        for (const auto& app : apps) {
            displayAppRow(app);
        }
    }

    void displayByPlatform(Platform platform) const {
        std::cout << "\n=== Applications for " << MobileApp::platformToString(platform) << " ===\n";
        displayTableHeader();
        for (const auto& app : apps) {
            if (app->getPlatform() == platform) {
                displayAppRow(app);
            }
        }
    }

private:
    void displayTableHeader() const {
        std::cout << std::left << std::setw(20) << "Name"
            << std::setw(15) << "Platform"
            << std::setw(15) << "Language"
            << std::setw(10) << "Version"
            << std::setw(10) << "Price"
            << "Developer\n";
        std::cout << std::string(80, '-') << "\n";
    }

    void displayAppRow(const std::shared_ptr<MobileApp>& app) const {
        std::cout << std::left << std::setw(20) << app->getName()
            << std::setw(15) << MobileApp::platformToString(app->getPlatform())
            << std::setw(15) << MobileApp::languageToString(app->getLanguage())
            << std::setw(10) << app->getVersion().toString()
            << "$" << std::setw(9) << std::fixed << std::setprecision(2) << app->getPrice();

        if (app->getDeveloper()) {
            std::cout << app->getDeveloper()->getName();
        }
        else {
            std::cout << "Unknown";
        }
        std::cout << "\n";
    }
};

// ������ �������������
int main() {
    try {
        // ������� �������������
        auto dev1 = std::make_shared<Developer>("John Doe", "john@example.com", 5);
        auto dev2 = std::make_shared<Developer>("Alice Smith", "alice@example.com", 3);

        // ������� ����������
        auto app1 = std::make_shared<MobileApp>(
            "Weather Forecast", Platform::iOS, DevelopmentLanguage::Swift,
            VersionInfo(1, 2, 3), dev1, 4.99);

        auto app2 = std::make_shared<MobileApp>(
            "Task Manager", Platform::Android, DevelopmentLanguage::Kotlin,
            VersionInfo(2, 0, 0), dev2, 0.0);

        auto app3 = std::make_shared<MobileApp>(
            "Fitness Tracker", Platform::Android, DevelopmentLanguage::Java,
            VersionInfo(3, 1, 5), dev1, 2.99);

        // ������� ��������� � ��������� ����������
        AppCollection collection;
        collection.addApp(app1);
        collection.addApp(app2);
        collection.addApp(app3);

        // ������� ��� ����������
        collection.displayAll();

        // ������� ���������� ��� Android
        collection.displayByPlatform(Platform::Android);

        // ������������ ������ ����������
        std::cout << "\n=== Transaction Demo ===\n";
        std::cout << "Original name: " << app1->getName() << "\n";

        app1->setName("Advanced Weather");
        std::cout << "After first change: " << app1->getName() << "\n";

        app1->setName("Weather Pro");
        std::cout << "After second change: " << app1->getName() << "\n";

        // ���������� ��������� ���������
        app1->rollbackName();
        std::cout << "After rollback: " << app1->getName() << "\n";

        // ������� ���������� ������������ ��������
        try {
            app1->setPlatform(Platform::Unknown);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        }

        try {
            app1->setLanguage(DevelopmentLanguage::Unknown);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}