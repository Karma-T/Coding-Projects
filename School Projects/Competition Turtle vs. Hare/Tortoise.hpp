#ifndef Tortoise_H
#define Tortoise_H
#include<vector>
//normally we do not use namespace std; in hpp file
class Tortoise {
public:
    Tortoise();
    Tortoise(int* arr, int size, int position);
    Tortoise(std::vector<int> patterns, int position);
    void move();
    int getPosition() const;
    void setPosition(int position);

private:
    std::vector<int> patterns;
    int position;
};
#endif
