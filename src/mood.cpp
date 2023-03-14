#include "lib/mood.h"
#include "lib/animal.h"


Joyful* Joyful::_instance = nullptr;
Usual* Usual::_instance = nullptr;
Blue* Blue::_instance = nullptr;


Joyful* Joyful::instance() 
{
 if(_instance == nullptr){
        _instance = new Joyful();
    }
    return _instance;
}


void Joyful::destroy()
{
    if(_instance != nullptr){
        delete _instance;
    }
    _instance = nullptr;
}

void Joyful::takeCare(Tarantula* a)
{
     a->increaseExhilarationLevel(1);
}
void Joyful::takeCare(Hamster* a)
{
     a->increaseExhilarationLevel(2);
}
void Joyful::takeCare(Cat* a)
{
     a->increaseExhilarationLevel(3);
}

Mood* Joyful::increase(){
  return Joyful::instance();
 }

Usual* Usual::instance() 
{
 if(_instance == nullptr){
        _instance = new Usual();
    }
    return _instance;
}
void Usual::takeCare(Tarantula* a)
{
     a->increaseExhilarationLevel(-2);
}
void Usual::takeCare(Hamster* a)
{
     a->increaseExhilarationLevel(-3);
}
void Usual::takeCare(Cat* a)
{
     a->increaseExhilarationLevel(3);
}
 
 Mood* Usual::increase(){
  return Joyful::instance();
 }


void Usual::destroy()
{
    if(_instance != nullptr){
        delete _instance;
    }
    _instance = nullptr;
}

Blue* Blue::instance() 
{
 if(_instance == nullptr){
        _instance = new Blue();
    }
    return _instance;
}


void Blue::destroy()
{
    if(_instance != nullptr){
        delete _instance;
    }
    _instance = nullptr;
}
Mood* Blue::increase(){
  return Usual::instance();
 }

void Blue::takeCare(Tarantula* a)
{
     a->increaseExhilarationLevel(-3);
}
void Blue::takeCare(Hamster* a)
{
     a->increaseExhilarationLevel(-5);
}
void Blue::takeCare(Cat* a)
{
     a->increaseExhilarationLevel(-7);
}