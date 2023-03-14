#pragma once

#include "mood.h"
#include "animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>

class Keeper{
private:
    std::vector<Mood*>moods;
    std::vector<Animal*>animals;
    void giveStat();

public:
    Keeper(std::vector<Mood*> &m, std::vector<Animal*> &a): moods(m), animals(a){}
    std::string takeCare();
    std::string testTakeCare();
    std::vector<Mood*> getMoods() {return moods;}
    std::vector<Animal*> getAnimals() {return animals;}
};
