#ifndef Competition_H
#define Competition_H
#include "Hare.hpp"
#include "Tortoise.hpp"
#include "Road.hpp"

class Competition {
public:
    Competition();
    Competition(Hare coney, Tortoise cooter, int length);
    void play();

private:
    Hare rabbit;
    Tortoise tor;
    Road lane;
};
#endif
