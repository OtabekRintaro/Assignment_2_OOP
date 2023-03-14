#pragma once
#include <iostream>

class Tarantula;
class Hamster;
class Cat;

class Mood
{
public:
   virtual Mood* increase() = 0;
   virtual void takeCare(Tarantula *a) = 0;
   virtual void takeCare(Hamster *a) = 0;
   virtual void takeCare(Cat *a) = 0;

   ~Mood() {};
};

class Joyful : public Mood{
public:
    Mood* increase() override;
    static Joyful* instance();
    void takeCare(Tarantula* a) override;
    void takeCare(Hamster* a) override;
    void takeCare(Cat* a) override;
    static void destroy();
protected:
   Joyful(){}
private:
   static Joyful* _instance;

};
class Usual : public Mood{
public:
    Mood* increase() override;
    static Usual* instance();
    void takeCare(Tarantula* a) override;
    void takeCare(Hamster* a) override;
    void takeCare(Cat* a) override;

    static void destroy();
protected:
   Usual(){}
private:
   static Usual* _instance;

};

class Blue : public Mood{
public:
    Mood* increase() override;
    static Blue* instance();
    void takeCare(Tarantula* a) override;
    void takeCare(Hamster* a) override;
    void takeCare(Cat* a) override;

    static void destroy();
protected:
    Blue(){}
private:
    static Blue* _instance;

};
