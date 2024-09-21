#ifndef _MEMORY_GAME
#define _MEMORY_GAME
#include <string>
using namespace std;
class MemoryGame {
public: //public method member, any class can use these methods
    MemoryGame();
       //default constructor, with 3 pairs of random integers in range [0, 999] 
       //placed in 8 blocks (two blocks are empty).
    MemoryGame(int numPairs, int numSlots);
       //Place numPairs pairs of random integers in range [0, 999] in numSlots space, need numPairs > 0, numSlots > 0, and numSlots >= 2 * numPairs
    MemoryGame(string *words, int size, int numSlots);
       //instead of randomly generated integers,
       //use words as data
    ~MemoryGame();
    void play();
    void display() const;
         //display array values, if bShown[i] is true,
         //then values[i] is displayed, where i is the index.
    void randomize();
        //randomize the layout of elements in values.
    int input() const;
        //input an int that is a valid index and 
        //the corresponding element of values is not shown yet.
        //That is, the input i is in [0, numSlots) and
        //bShown[i] is false. 
private: //private data members, private means that
         //only methods in this class, not other class,
         //can access or modify these data members.
    int numPairs; //numPairs of identical twin items
    int numSlots;
        //size of array value, besides identical twins,
        //may contain empty string to
        //make the problem more challenging
    string *values;
        //a string to represent the layout of data,
        //mixed with possible empty strings.
        //Use array to access each element in const time.
    bool *bShown;
        //an array of boolean to indicate which element of
        //array values is shown or not.
        //If bShown[i] is true, then values[i] is shown,
        //otherwise values[i] is not shown,
        //where 0 <= i and i < numSlots.
};
#endif 
