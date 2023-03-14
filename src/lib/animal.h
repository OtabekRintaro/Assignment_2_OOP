#pragma once
#include <iostream>
#include "mood.h"
#include <fstream>

class Animal{
protected:
    std::string _name;
    int _exhilarationLevel;
    Animal(std::string n, int eL) : _name(n), _exhilarationLevel(eL){}


public:

    int getExhilarationLevel() const {return _exhilarationLevel;}
    std::string getName() const { return _name;}
    bool alive() const {return _exhilarationLevel > 0;}
    void increaseExhilarationLevel(int n);

    virtual void takeCare(Mood* &m) = 0;
    virtual ~Animal(){}

    friend std::ifstream &operator>>(std::ifstream &is, Animal* &a);
};

class Tarantula: public Animal{
public:
    Tarantula(std::string n, int eL) : Animal(n,eL) {}
    void takeCare(Mood* &m) override { m->takeCare(this);}

};

class Hamster: public Animal{
public:
    Hamster(std::string n, int eL) : Animal(n,eL) {}
    void takeCare(Mood* &m) override { m->takeCare(this);}

};

class Cat: public Animal{
public:
    Cat(std::string n, int eL) : Animal(n,eL) {}
    void takeCare(Mood* &m) override { m->takeCare(this);}

};
