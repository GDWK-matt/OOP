#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Базовый класс для платформы
class Platform {
protected:
    string name;
    string version;

public:
    Platform() : name("Unknown"), version("1.0") {}
    Platform(const string& n, const string& v) : name(n), version(v) {}
    Platform(const Platform& other) : name(other.name), version(other.version) {}
    virtual ~Platform() {}

    string getName() const { return name; }
    string getVersion() const { return version; }
    void setName(const string& n) { name = n; }
    void setVersion(const string& v) { version = v; }

    virtual void displayInfo() const {
        cout << "Platform: " << name << " (v" << version << ")";
    }
};

// Шаблонный класс для рейтинга приложения
template <typename T>
class AppRating {
private:
    T rating;
    int reviewsCount;

public:
    AppRating() : rating(0), reviewsCount(0) {}
    AppRating(T r, int c) : rating(r), reviewsCount(c) {}
    AppRating(const AppRating& other) : rating(other.rating), reviewsCount(other.reviewsCount) {}

    T getRating() const { return rating; }
    int getReviewsCount() const { return reviewsCount; }
    void setRating(T r) { rating = r; }
    void setReviewsCount(int c) { reviewsCount = c; }

    void displayInfo() const {
        cout << "Rating: " << rating << "/5 (" << reviewsCount << " reviews)";
    }
};

// Класс разработчика
class Developer {
private:
    string name;
    string country;
    int foundedYear;

public:
    Developer() : name("Unknown"), country("Unknown"), foundedYear(0) {}
    Developer(const string& n, const string& c, int y) : name(n), country(c), foundedYear(y) {}
    Developer(const Developer& other) : name(other.name), country(other.country), foundedYear(other.foundedYear) {}
    ~Developer() {}

    string getName() const { return name; }
    string getCountry() const { return country; }
    int getFoundedYear() const { return foundedYear; }
    void setName(const string& n) { name = n; }
    void setCountry(const string& c) { country = c; }
    void setFoundedYear(int y) { foundedYear = y; }

    void displayInfo() const {
        cout << "Developer: " << name << " (" << country << ", founded " << foundedYear << ")";
    }
};

// Базовый класс мобильного приложения
class MobileAppBase {
protected:
    string name;
    Platform platform;
    Developer developer;
    double price;

public:
    MobileAppBase() : name("Unknown"), price(0.0) {}
    MobileAppBase(const string& n, const Platform& p, const Developer& d, double pr)
        : name(n), platform(p), developer(d), price(pr) {}
    virtual ~MobileAppBase() {}

    virtual void displayInfo() const = 0;
    virtual void saveToFile(ofstream& file) const = 0;

    string getName() const { return name; }
    Platform getPlatform() const { return platform; }
    Developer getDeveloper() const { return developer; }
    double getPrice() const { return price; }

    void setName(const string& n) { name = n; }
    void setPlatform(const Platform& p) { platform = p; }
    void setDeveloper(const Developer& d) { developer = d; }
    void setPrice(double p) { price = p; }
};

// Класс мобильного приложения с double рейтингом
class MobileApp : public MobileAppBase {
protected:
    AppRating<double> rating;

public:
    MobileApp() : MobileAppBase() {}
    MobileApp(const string& n, const Platform& p, const Developer& d, double pr, const AppRating<double>& r)
        : MobileAppBase(n, p, d, pr), rating(r) {}

    AppRating<double> getRating() const { return rating; }
    void setRating(const AppRating<double>& r) { rating = r; }

    void displayInfo() const override {
        cout << "App: " << name << endl;
        cout << "  "; platform.displayInfo(); cout << endl;
        cout << "  "; developer.displayInfo(); cout << endl;
        cout << "  Price: $" << fixed << setprecision(2) << price << endl;
        cout << "  "; rating.displayInfo(); cout << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "App: " << name << "\n";
        file << "  Platform: " << platform.getName() << " (v" << platform.getVersion() << ")\n";
        file << "  Developer: " << developer.getName() << " (" << developer.getCountry() << ", founded "
            << developer.getFoundedYear() << ")\n";
        file << "  Price: $" << fixed << setprecision(2) << price << "\n";
        file << "  Rating: " << rating.getRating() << "/5 (" << rating.getReviewsCount() << " reviews)\n";
    }
};

// Класс игры с int рейтингом
class GameApp : public MobileAppBase {
private:
    AppRating<int> rating;
    string genre;
    bool isMultiplayer;

public:
    GameApp() : MobileAppBase(), genre("Unknown"), isMultiplayer(false) {}
    GameApp(const string& n, const Platform& p, const Developer& d, double pr,
        const AppRating<int>& r, const string& g, bool mp)
        : MobileAppBase(n, p, d, pr), rating(r), genre(g), isMultiplayer(mp) {}

    AppRating<int> getRating() const { return rating; }
    string getGenre() const { return genre; }
    bool getIsMultiplayer() const { return isMultiplayer; }

    void setRating(const AppRating<int>& r) { rating = r; }
    void setGenre(const string& g) { genre = g; }
    void setIsMultiplayer(bool mp) { isMultiplayer = mp; }

    void displayInfo() const override {
        cout << "Game: " << name << endl;
        cout << "  "; platform.displayInfo(); cout << endl;
        cout << "  "; developer.displayInfo(); cout << endl;
        cout << "  Price: $" << fixed << setprecision(2) << price << endl;
        cout << "  "; rating.displayInfo(); cout << endl;
        cout << "  Genre: " << genre << endl;
        cout << "  Multiplayer: " << (isMultiplayer ? "Yes" : "No") << endl;
    }

    void saveToFile(ofstream& file) const override {
        file << "Game: " << name << "\n";
        file << "  Platform: " << platform.getName() << " (v" << platform.getVersion() << ")\n";
        file << "  Developer: " << developer.getName() << " (" << developer.getCountry() << ", founded "
            << developer.getFoundedYear() << ")\n";
        file << "  Price: $" << fixed << setprecision(2) << price << "\n";
        file << "  Rating: " << rating.getRating() << "/5 (" << rating.getReviewsCount() << " reviews)\n";
        file << "  Genre: " << genre << "\n";
        file << "  Multiplayer: " << (isMultiplayer ? "Yes" : "No") << "\n";
    }
};

// Класс для управления приложениями
class AppManager {
private:
    vector<MobileAppBase*> apps;

public:
    AppManager() {}
    ~AppManager() {
        for (auto app : apps) {
            delete app;
        }
    }

    void addApp(MobileAppBase* app) {
        apps.push_back(app);
    }

    void displayAllApps() const {
        cout << "\n=== ALL APPLICATIONS ===\n";
        for (const auto& app : apps) {
            app->displayInfo();
            cout << "----------------------\n";
        }
    }

    void displayAppsByPlatform(const string& platformName) const {
        cout << "\n=== APPLICATIONS FOR " << platformName << " ===\n";
        for (const auto& app : apps) {
            if (app->getPlatform().getName() == platformName) {
                app->displayInfo();
                cout << "----------------------\n";
            }
        }
    }

    void saveAllAppsToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << "=== ALL APPLICATIONS ===\n\n";
            for (const auto& app : apps) {
                app->saveToFile(file);
                file << "----------------------\n";
            }
            file.close();
            cout << "Data saved to " << filename << endl;
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }

    void saveAppsByPlatformToFile(const string& filename, const string& platformName) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << "=== APPLICATIONS FOR " << platformName << " ===\n\n";
            for (const auto& app : apps) {
                if (app->getPlatform().getName() == platformName) {
                    app->saveToFile(file);
                    file << "----------------------\n";
                }
            }
            file.close();
            cout << "Data saved to " << filename << endl;
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }
};

int main() {
    // Создаем платформы
    Platform android("Android", "12.0");
    Platform ios("iOS", "15.4");

    // Создаем разработчиков
    Developer google("Google LLC", "USA", 1998);
    Developer apple("Apple Inc.", "USA", 1976);
    Developer epic("Epic Games", "USA", 1991);
    Developer kitchen("Game Kitchen", "Spain", 2011);

    // Создаем рейтинги
    AppRating<double> chromeRating(4.5, 5000000);  // double для приложений
    AppRating<double> safariRating(4.7, 3000000);
    AppRating<int> fortniteRating(4.2, 10000000);    // int для игр
    AppRating<int> blasphemousRating(4.6, 50000000);

    // Создаем менеджер приложений
    AppManager manager;

    // Добавляем приложения
    manager.addApp(new MobileApp("Google Chrome", android, google, 0.0, chromeRating));
    manager.addApp(new MobileApp("Safari", ios, apple, 2.0, safariRating));
    manager.addApp(new GameApp("Fortnite", android, epic, 9.9, fortniteRating, "Battle Royale", true));
    manager.addApp(new GameApp("Fortnite", ios, epic, 8.9, fortniteRating, "Battle Royale", true));
    manager.addApp(new GameApp("Blasphemous", android, kitchen, 10, blasphemousRating, "Metroidvania", false));

    // Выводим информацию
    manager.displayAllApps();
    manager.displayAppsByPlatform("Android");

    // Сохраняем в файлы
    manager.saveAllAppsToFile("all_apps.txt");
    manager.saveAppsByPlatformToFile("android_apps.txt", "Android");

    return 0;
}