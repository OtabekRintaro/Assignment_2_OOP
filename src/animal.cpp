#include "lib/animal.h"

std::ifstream &operator>>(std::ifstream &is, Animal* &a)
{
    int eL;
    std::string name;
    char kind;
    is >> kind >> name >> eL;

    switch(kind){
        case 'T': a = new Tarantula(name, eL); break;
        case 'H': a = new Hamster(name, eL); break;
        case 'C': a = new Cat(name, eL); break;
        default:
            break;
    }
    return is;
}

void Animal::increaseExhilarationLevel(int n){
    if(alive() && _exhilarationLevel + n > 70) _exhilarationLevel = 70;
    else if(alive() && _exhilarationLevel + n < 0) _exhilarationLevel = 0;
    else if(alive()) _exhilarationLevel += n;
}


