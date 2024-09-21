#ifndef Hare_H
#define Hare_H
#include <vector>

class Hare {
public:
    Hare(); 
       //a typical hare that sleeps 20% of the time,
       //move 9 squares to the right 20% of the time,
       //move 12 squares to the left 10% of the time,
       //move 1 square to the right 30% of the time,
       //move 2 squares to the left 20% of the time.
    Hare(std::vector<int> patterns, int position);
    Hare(int* arr, int size, int position);
    void move();
    int getPosition() const; 
    void setPosition(int position);
//private: //for debug purpose only, when we release the class, we need to make data members private by uncomment this line.
    std::vector<int> patterns;
    int position;
};
#endif
