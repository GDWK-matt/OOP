#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class Ciferblat {
private:
    std::string material;
    std::string tip;

public:
    Ciferblat() : material("Neizvestno"), tip("Analogovyy") {}
    Ciferblat(std::string m, std::string t) : material(m), tip(t) {}

    void vivesti() const {
        std::cout << "Material ciferblata: " << material << ", Tip: " << tip << std::endl;
    }
};

class IstochnikEnergii {
private:
    std::string tip;
    int vremyaRaboty; // Vremya raboty v chasah

public:
    IstochnikEnergii() : tip("Mehanicheskiy"), vremyaRaboty(0) {}
    IstochnikEnergii(std::string t, int life) : tip(t), vremyaRaboty(life) {}

    void vivesti() const {
        std::cout << "Istochnik energii: " << tip << ", Vremya raboty: " << vremyaRaboty << " chasov" << std::endl;
    }
};

class Chasy {
protected:
    std::string marka;
    double cena;
    Ciferblat ciferblat;
    IstochnikEnergii istochnik;

public:
    
    Chasy() : marka("Neizvestno"), cena(0) {}
    Chasy(std::string m, double c, Ciferblat cif, IstochnikEnergii ist) : marka(m), cena(c), ciferblat(cif), istochnik(ist) {}

    virtual void vivesti() const {
        std::cout << "Marka: " << marka << ", Cena: " << cena << " rubley" << std::endl;
        ciferblat.vivesti();
        istochnik.vivesti();
    }

    double poluchitCenu() const { return cena; }
    std::string poluchitMarku() const { return marka; }
};

class MehanicheskieChasy : public Chasy {
public:
    MehanicheskieChasy(std::string m, double c, Ciferblat cif, IstochnikEnergii ist) : Chasy(m, c, cif, ist) {}

    void vivesti() const override {
        std::cout << "[Mehanicheskie chasy] ";
        Chasy::vivesti();
    }
};

class ElektronnyeChasy : public Chasy {
public:
    ElektronnyeChasy(std::string m, double c, Ciferblat cif, IstochnikEnergii ist) : Chasy(m, c, cif, ist) {}

    void vivesti() const override {
        std::cout << "[Elektronnye chasy] ";
        Chasy::vivesti();
    }
};

void zapisVFail(const std::vector<Chasy*>& chasy, const std::string& fail) {
    std::ofstream f(fail);
    if (!f) {
        std::cerr << "Oshibka pri otkrytii faila " << fail << std::endl;
        return;
    }

    for (const auto& ch : chasy) {
        f << "Marka: " << ch->poluchitMarku() << ", Cena: " << ch->poluchitCenu() << " rubley\n";
    }
    f.close();
}

void vivestiSamyeDorogieChasy(const std::vector<Chasy*>& chasy) {
    std::vector<Chasy*> sortirovannyeChasy = chasy;
    std::sort(sortirovannyeChasy.begin(), sortirovannyeChasy.end(), [](Chasy* a, Chasy* b) {
        return a->poluchitCenu() > b->poluchitCenu();
        });

    std::cout << "\nSamye dorogie 10 chasov:\n";
    for (size_t i = 0; i < std::min<size_t>(10, sortirovannyeChasy.size()); ++i) {
        sortirovannyeChasy[i]->vivesti();
    }
}

void pokazatMenu(std::vector<Chasy*>& chasy) {
    int vibor;
    do {
        std::cout << "\nSistema ucheta chasov\n";
        std::cout << "1. Vivesti vse chasy\n";
        std::cout << "2. Zapisat dannye v fail\n";
        std::cout << "3. Vivesti samye dorogie 10 chasov\n";
        std::cout << "4. Vyhod\n";
        std::cout << "Vvedite variant: ";
        std::cin >> vibor;

        switch (vibor) {
        case 1:
            for (const auto& ch : chasy) {
                ch->vivesti();
                std::cout << ("======================================================\n");
            }
            break;
        case 2:
            zapisVFail(chasy, "chasy_dannye.txt");
            break;
        case 3:
            vivestiSamyeDorogieChasy(chasy);
            break;
        case 4:
            std::cout << "Vyhod...\n";
            break;
        default:
            std::cout << "Nepravilnyy variant. Poprobuyte eshche raz.\n";
            break;
        }
    } while (vibor != 4);
}

int main() {
    std::vector<Chasy*> chasy = {
        new MehanicheskieChasy("Rolex", 1000000, Ciferblat("Zoloto", "Analogovyy"), IstochnikEnergii("Mehanicheskiy", 0)),
        new ElektronnyeChasy("Apple Watch", 50000, Ciferblat("Steklo", "Cifrovoy"), IstochnikEnergii("Batareya", 48)),
        new MehanicheskieChasy("Omega", 800000, Ciferblat("Stal", "Analogovyy"), IstochnikEnergii("Mehanicheskiy", 0)),
        new ElektronnyeChasy("Casio", 10000, Ciferblat("Plastik", "Cifrovoy"), IstochnikEnergii("Batareya", 36))
    };

    pokazatMenu(chasy);

    for (auto& ch : chasy) {
        delete ch;
    }
    chasy.clear();

    return 0;
}
