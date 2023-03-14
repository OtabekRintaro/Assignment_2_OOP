#include "lib/keeper.h"
#include <string>

std::string toUpper(std::string text);
void sentenceDeath(Animal* a);
std::string getAnimal(int eL, std::vector<Animal*> as);
int getMax(std::vector<Animal*> as);

std::string Keeper::testTakeCare()
{
    std::string listhighest = "";
    bool l = false;
    for(int j = 0; j<moods.size(); j++)
    {
        listhighest += std::to_string(j+1);
        listhighest += " ";
        if(l && animals.size() != 0){
            moods[j] = moods[j]->increase();
        }
        l = true;
        for(int i = 0; i<animals.size(); ++i){
            if(animals[i]->alive())
            {
                animals[i]->takeCare(moods[j]);
                l = l && animals[i]->getExhilarationLevel() >= 5;
            }
            else{
                animals.erase(animals.begin() + i);
                i--;
            }
        }
        listhighest += getAnimal(getMax(animals),animals);
        listhighest += "\n";
    }
    return listhighest;
}

std::string Keeper::takeCare()
{
    srand(time(NULL));
    int daycount = 0;
    std::string listhighest = "";
    bool l = false;
    std::cout << "Current status of Animals" << std::endl << "-------" << std::endl;
    giveStat();
    std::cout << "----------------------------------------------------------------------" << std::endl << std::endl;
    for(Mood* m: moods)
    {
        daycount++;
        listhighest += std::to_string(daycount);
        listhighest += " ";
        if(l){
            m = m->increase();
        }
        l = true;
        for(int i = 0; i < animals.size(); ++i){
            if(animals[i]->alive())
            {
                animals[i]->takeCare(m);
                l = l && animals[i]->getExhilarationLevel() >= 5;
            }
            else{
                sentenceDeath(animals[i]);
                animals.erase(animals.begin() + i);
                i--;
            }
        }
        listhighest += getAnimal(getMax(animals),animals);
        listhighest += "\n";
        std::cout << daycount << " - Day" << std::endl ;
        std::cout << "---" << std::endl;
        giveStat();
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "Highest Exhilaration Level: " << getMax(animals) << " Animals: " << getAnimal(getMax(animals),animals) << std::endl << std::endl << std::endl;
    }
    return listhighest;
}

void Keeper::giveStat()
{
    for(Animal* a : animals)
        std::cout << "Name: " << a->getName() << " Exhilaration Level: " << a->getExhilarationLevel() << std::endl;
}

void sentenceDeath(Animal* a){
    int t = rand() % 4 + 1;
    switch(t){
    case 1:
        std::cout << "*************************************************************************" << std::endl;
        std::cout << "Today, one of the lovely pets went somewhere, sadly, it never came back. Goodbye, " << a->getName() << "." << std::endl;
        std::cout << "*************************************************************************" << std::endl; break;
    case 2:
        std::cout << "*************************************************************************" << std::endl;
        std::cout << a->getName() << " could not bear it anymore. We found him hanging from the door handle today. RIP, " << a->getName() << "." << std::endl;
        std::cout << "*************************************************************************" << std::endl; break;
    case 3:
        std::cout << "*************************************************************************" << std::endl;
        std::cout << "Hello, " << a->getName() << "! " << a->getName() << "? NOOOOOOOO, " << toUpper(a->getName()) << "!!!!!!!" << std::endl;
        std::cout << "*************************************************************************" << std::endl; break;
    case 4:
        std::cout << "*************************************************************************" << std::endl;
        std::cout << "What a lovely day, I guess it's time to check on our pets! Oh. OH! OH NO, " << toUpper(a->getName()) << "!" << std::endl;
        std::cout << "*************************************************************************" << std::endl; break;
    default:
        break;
    }
}

std::string toUpper(std::string text){
    std::string temp = text;
    for(int i = 0; i < text.length(); i++) temp[i] = toupper(text[i]);
    return temp;
}

std::string getAnimal(int eL, std::vector<Animal*> as){
    std::string ret = "";
    for(Animal* m: as) {
        if(m->getExhilarationLevel() == eL){
            ret += m->getName();
            ret += " ";
        }
    }
    return ret;
}
int getMax(std::vector<Animal*> as)
{
    int max = 0;
    for(Animal* a: as)
        if(max < a->getExhilarationLevel()) max = a->getExhilarationLevel();
    return max;
}
