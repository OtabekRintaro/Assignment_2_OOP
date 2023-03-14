#include <iostream>
#include <fstream>
#include "lib/keeper.h"
#include "lib/mood.h"
#include "lib/animal.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

enum ERROR{FILEERROR, EMPTYFILE};

void read(vector<Mood*> &moods, vector<Animal*> &animal,const string &fileName);

int main()
{
    vector<Mood*> moods;
    vector<Animal*> animals;
    try{
        read(moods,animals,"inputs/input.txt");
        Keeper* Steve = new Keeper(moods, animals);
        string highestlist = Steve->takeCare();
        cout << highestlist;
    }
    catch(ERROR e){
        if(e == FILEERROR)  cout << "File opening was unsuccessful!" << endl;
        if(e == EMPTYFILE)  cout << "File is empty!" << endl;
    }
    return 0;
}

void read(vector<Mood*> &moods, vector<Animal*> &animals, const string &fileName){
    int n = 0;
    Animal* a;
    std::string moodline;
    ifstream f;
    f.open(fileName);
    if(f.fail())
    {
        throw FILEERROR;
    }
    f >> n;
    if(n == 0) throw EMPTYFILE;
    for(int i = 0; i < n; i++) {
        f >> a;
        animals.push_back(a);
    }
    f >> moodline;
    moods.resize(moodline.length());
    for(int i = 0; i < moodline.length(); i++){
        switch(moodline[i]){
            case 'j': moods[i] = Joyful::instance(); break;
            case 'u': moods[i] = Usual::instance(); break;
            case 'b': moods[i] = Blue::instance(); break;
            default:    break;
        }
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"

TEST_CASE("Inner loop")
{
    vector<Animal*> animals;
    vector<Mood*> moods;
    SECTION("Length based")
    {
        moods.push_back(Joyful::instance());
        Keeper* Steve = new Keeper(moods, animals);
        string highestlist = Steve->testTakeCare();
        CHECK(highestlist == "1 \n");

        animals.push_back(new Tarantula("Chopper",10));
        Steve = new Keeper(moods, animals);
        highestlist = Steve->testTakeCare();
        CHECK(highestlist == "1 Chopper \n");

        animals.push_back(new Hamster("Eldiyar",10));
        animals.push_back(new Cat("Chipin", 10));
        Steve = new Keeper(moods, animals);
        highestlist = Steve->testTakeCare();
        CHECK(highestlist == "1 Chipin \n");
    }
    SECTION("First and last")
    {
        moods.push_back(Blue::instance());
        moods.push_back(Joyful::instance());
        moods.push_back(Usual::instance());
        animals.push_back(new Hamster("Eldiyar",10));
        animals.push_back(new Cat("Chipin", 10));
        animals.push_back(new Cat("Zhusup",10));
        Keeper* Steve = new Keeper(moods, animals);
        Steve->testTakeCare();
        vector<Animal*> temp = Steve->getAnimals();
        CHECK(temp[0]->getName() == "Eldiyar");

        animals.clear();
        temp.clear();
        animals.push_back(new Hamster("Eldiyar",3));
        animals.push_back(new Cat("Chipin", 10));
        animals.push_back(new Cat("Zhusup",10));
        Steve = new Keeper(moods, animals);
        Steve->testTakeCare();
        temp = Steve->getAnimals();
        CHECK_FALSE(temp[0]->getName() == "Eldiyar");

        animals.clear();
        temp.clear();
        animals.push_back(new Hamster("Eldiyar",3));
        animals.push_back(new Cat("Chipin", 10));
        animals.push_back(new Cat("Zhusup",10));
        Steve = new Keeper(moods, animals);
        Steve->testTakeCare();
        temp = Steve->getAnimals();
        CHECK(temp[temp.size()-1]->getName() == "Zhusup");

        animals.clear();
        temp.clear();
        animals.push_back(new Hamster("Eldiyar",3));
        animals.push_back(new Cat("Chipin", 10));
        animals.push_back(new Cat("Zhusup", 3));
        Steve = new Keeper(moods, animals);
        Steve->testTakeCare();
        temp = Steve->getAnimals();
        CHECK_FALSE(temp[temp.size()-1]->getName() == "Zhusup");
    }
}

TEST_CASE("Outer loop")
{
    vector<Animal*> animals;
    vector<Mood*> moods;
    SECTION("Length based")
    {
        animals.push_back(new Tarantula("Spido", 10));
        Keeper* Steve = new Keeper(moods, animals);
        CHECK(Steve->testTakeCare() == "");

        moods.push_back(Joyful::instance());
        Steve = new Keeper(moods, animals);
        CHECK(Steve->testTakeCare() == "1 Spido \n");

        moods.push_back(Joyful::instance());
        moods.push_back(Usual::instance());
        Steve = new Keeper(moods, animals);
        CHECK(Steve->testTakeCare() == "1 Spido \n2 Spido \n3 Spido \n");
    }
    SECTION("First and last")
    {
        animals.push_back(new Tarantula("Mano", 10));
        moods.push_back(Usual::instance());
        moods.push_back(Usual::instance());
        moods.push_back(Blue::instance());
        Keeper * Steve = new Keeper(moods, animals);
        Steve->testTakeCare();
        vector<Mood*> m = Steve->getMoods();
        CHECK(m[0] == Usual::instance());
        CHECK(m[1] == Joyful::instance());
        CHECK(m[2] == Usual::instance());

        moods.clear();
        moods.push_back(Usual::instance());
        moods.push_back(Usual::instance());
        moods.push_back(Blue::instance());
        animals.push_back(new Tarantula("Spido mano", 3));
        animals.push_back(new Hamster("Hamsto", 7));
        Steve = new Keeper(moods,animals);
        Steve->testTakeCare();
        m = Steve->getMoods();
        CHECK(m[0] == Usual::instance());
        CHECK(m[1] == Usual::instance());
        CHECK(m[2] == Blue::instance());
    }
}

TEST_CASE("takeCare")
{
    SECTION("exhiliration level == 0")
    {
        Animal* spido = new Tarantula("spido", 0);
        Animal* hamsto = new Hamster("hamsto", 0);
        Animal* cato = new Cat("cato", 0);

        Mood* goodmoodo = Joyful::instance();
        Mood* moodo = Usual::instance();
        Mood* badmoodo = Blue::instance();
        spido->takeCare(goodmoodo);
        hamsto->takeCare(goodmoodo);
        cato->takeCare(goodmoodo);
        CHECK(spido->getExhilarationLevel() == 0);
        CHECK(hamsto->getExhilarationLevel() == 0);
        CHECK(cato->getExhilarationLevel() == 0);
        spido->takeCare(moodo);
        hamsto->takeCare(moodo);
        cato->takeCare(moodo);
        CHECK(spido->getExhilarationLevel() == 0);
        CHECK(hamsto->getExhilarationLevel() == 0);
        CHECK(cato->getExhilarationLevel() == 0);
        spido->takeCare(badmoodo);
        hamsto->takeCare(badmoodo);
        cato->takeCare(badmoodo);
        CHECK(spido->getExhilarationLevel() == 0);
        CHECK(hamsto->getExhilarationLevel() == 0);
        CHECK(cato->getExhilarationLevel() == 0);
    }
    SECTION("exhilliration level == 1")
    {
        Animal* spido = new Tarantula("spido", 1);
        Animal* hamsto = new Hamster("hamsto", 1);
        Animal* cato = new Cat("cato", 1);

        Mood* goodmoodo = Joyful::instance();
        Mood* moodo = Usual::instance();
        Mood* badmoodo = Blue::instance();
        spido->takeCare(goodmoodo);
        hamsto->takeCare(goodmoodo);
        cato->takeCare(goodmoodo);
        CHECK(spido->getExhilarationLevel() == 2);
        CHECK(hamsto->getExhilarationLevel() == 3);
        CHECK(cato->getExhilarationLevel() == 4);
        spido->takeCare(moodo);
        hamsto->takeCare(moodo);
        cato->takeCare(moodo);
        CHECK(spido->getExhilarationLevel() == 0);
        CHECK(hamsto->getExhilarationLevel() == 0);
        CHECK(cato->getExhilarationLevel() == 7);
        spido->takeCare(badmoodo);
        hamsto->takeCare(badmoodo);
        cato->takeCare(badmoodo);
        CHECK(spido->getExhilarationLevel() == 0);
        CHECK(hamsto->getExhilarationLevel() == 0);
        CHECK(cato->getExhilarationLevel() == 0);
    }
    SECTION("exhiliration level == 70")
    {
        Animal* spido = new Tarantula("spido", 70);
        Animal* hamsto = new Hamster("hamsto", 70);
        Animal* cato = new Cat("cato", 70);

        Mood* goodmoodo = Joyful::instance();
        Mood* moodo = Usual::instance();
        Mood* badmoodo = Blue::instance();
        spido->takeCare(goodmoodo);
        hamsto->takeCare(goodmoodo);
        cato->takeCare(goodmoodo);
        CHECK(spido->getExhilarationLevel() == 70);
        CHECK(hamsto->getExhilarationLevel() == 70);
        CHECK(cato->getExhilarationLevel() == 70);
        spido->takeCare(moodo);
        hamsto->takeCare(moodo);
        cato->takeCare(moodo);
        CHECK(spido->getExhilarationLevel() == 68);
        CHECK(hamsto->getExhilarationLevel() == 67);
        CHECK(cato->getExhilarationLevel() == 70);
        spido->takeCare(badmoodo);
        hamsto->takeCare(badmoodo);
        cato->takeCare(badmoodo);
        CHECK(spido->getExhilarationLevel() == 65);
        CHECK(hamsto->getExhilarationLevel() == 62);
        CHECK(cato->getExhilarationLevel() == 63);
    }
}

#endif
