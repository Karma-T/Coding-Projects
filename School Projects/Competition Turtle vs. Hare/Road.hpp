#ifndef Road_H
#define Road_H
#include <vector>
class Road {
public:
    Road();
    Road(int length); 
    void mark(int index, char ch);
    void display() const;
    int length() const;
//private:
    std::vector<char> blocks;
};
#endif
