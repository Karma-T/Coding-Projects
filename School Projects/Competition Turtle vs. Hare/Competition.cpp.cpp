#include <iostream>
#include "Competition.hpp"

using namespace std;

Competition::Competition() {
    rabbit = Hare();
    tor = Tortoise();
    lane = Road();    
}

Competition::Competition(Hare coney, Tortoise cooter, int length) {
    rabbit = coney;
    tor = cooter;
    lane = Road(length);
}

void Competition::play() {
    int lastPos = lane.length() - 1;
    int round = 1;

    while (rabbit.getPosition() < lastPos && tor.getPosition() < lastPos) {
        rabbit.move();
        rabbit.setPosition(max(rabbit.getPosition(), 0));
        rabbit.setPosition(min(rabbit.getPosition(), lastPos));
        lane.mark(rabbit.getPosition(), 'H');

        tor.move();
        tor.setPosition(max(tor.getPosition(), 0));
        tor.setPosition(min(tor.getPosition(), lastPos));
        lane.mark(tor.getPosition(), 'T');

        cout << "Round " << round << ": ";
        lane.display();

        if (rabbit.getPosition() == tor.getPosition()) {
            cout << "Ouch! Tortoise bites hare." << endl;
        }

        lane.mark(rabbit.getPosition(), ' ');
        lane.mark(tor.getPosition(), ' ');

        round++;
    }

    if (rabbit.getPosition() == lastPos) {
        cout << "Yuck, hare wins." << endl;
    } else if (tor.getPosition() == lastPos) {
        cout << "Tortoise wins!" << endl;
    } else {
        cout << "It is a tie." << endl;
    }
}