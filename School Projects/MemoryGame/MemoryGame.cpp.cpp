#include "MemoryGame.hpp"
#include <iostream> //std
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

//TODO:
MemoryGame::MemoryGame() : MemoryGame(3, 8) {
}

MemoryGame::MemoryGame(int numPairs, int numSlots) {
    //validate the formal parameters
    if ( numPairs <= 0 || numSlots <= 0 || 
        2 * numPairs >  numSlots ) {
       numPairs = 3;
       numSlots = 8;
    }

    //the opposite of condition is
    //!(numPairs <= 0 || numSlots <= 0 ||
    //  2 * numPairs > numSlots)
    //is obtained by Demorgan's law
    //numPairs > 0 && numSlots > 0 && 2 * numPairs <= numSlots

    //use VALIDATED formal parameters to initialize 
    //the corresponding data members
    this->numPairs = numPairs; //this->numPairs
    //can be replace by (*this).numPairs.
    //Warning: () around (*this) cannot be omitted
    //because . operator has higher predecedence than
    //dereference * operator.
    this->numSlots = numSlots;

    //string* values = new string[numSlots]; //WRONG
    //string* values is a local variable in the 
    //current constructor,
    //the variable has nothing to do with data member values.

    values = new string[numSlots]; //CORRECT
    //data members values is declared in hpp file already,
    //do not need to redeclare it.
    //Otherwise, the data member values is not initialized at all.

//    int curr = rand() % 1000;
//    values[0] = to_string(curr); //to_string(int) converts an int to a string, for example, to_string(12) returns "12"
//    values[1] = to_string(curr);
//
//    curr = rand() % 1000;
//    values[2] = to_string(curr);
//    values[3] = to_string(curr);

      int curr;
      for (int i = 0; i < numPairs*2 ; i += 2) {
          curr = rand() % 1000;
          values[i] = to_string(curr);
          values[i+1] = to_string(curr);
      }

      //placed the integers by pairs to the first
      //[0, numPairs*2-1] slots of values,
      //for the rest of values, set them to be ""
      for (int i = numPairs * 2; i < numSlots; i++)
          values[i] = "";

      //do similar things for bShown
      bShown = new bool[numSlots];
      for (int i = 0; i < numSlots; i++)
          bShown[i] = false;
}

MemoryGame::MemoryGame(string *words, int size, int numSlots) : MemoryGame(size, numSlots) {
  if (size <= 0 || numSlots <= 0 || numSlots < 2 * size) {
    numSlots = 2 * size;
  }
  numPairs = size;
  this->numSlots = numSlots;

  values = new string[numSlots];
  bShown = new bool[numSlots];

  for (int i = 0; i < numSlots; ++i) {
    bShown[i] = false;
  }

  for (int i = 0; i < numPairs; ++i) {
    values[2 * i] = words[i];
    values[2 * i + 1] = words[i];
  }

  for (int i = 2 * numPairs; i < numSlots; ++i) {
    values[i] = "";
  }

}

MemoryGame::~MemoryGame() {
    //TODO: release dynamically allocated memory allocated to values
    delete[] values;
    //TODO: set values to be nullptr to avoid dangling pointer problem
    values = nullptr;
    //TODO: do similar things for data member bShown
    delete[] bShown;

    bShown = nullptr;
}

void MemoryGame::randomize() {
    int size = numSlots; // Initialize size to the number of elements in values

    // Continue randomizing until size is 1
    while (size > 1) {
        // Generate a random index in [0, size)
        int randomIndex = rand() % size;

        // Swap the element at randomIndex with the last element in values
        swap(values[randomIndex], values[size - 1]);

        // Reduce size by 1 so that we do not consider the already-chosen element
        size--;
    }
}

void printSeparatedLine(int size) {
cout << "+"; //the first +
//draw -----+ for (size) many times
for (int i = 0; i < size; i++) cout << "-----+";
    cout << endl;
}

void MemoryGame::display() const {
    // Print labels
cout << " ";
for (int i = 0; i < numSlots; i++)
    cout << setw(3) << i << setw(3) << " ";
cout << endl;

     // Display horizontal separator
    cout << "+";
    for (int j = 0; j < numSlots; j++) {
        cout << "-----+";
    }
    cout << endl;

    // Display the row of boxes
    cout << "|";
    for (int j = 0; j < numSlots; j++) {
        cout << setw(5) << (bShown[j] ? (values[j].empty() ? "" : values[j]) : "") << "|";
    }
    cout << endl;

    // Display horizontal separator
    cout << "+";
    for (int j = 0; j < numSlots; j++) {
        cout << "-----+";
    }
    cout << endl;
}

int MemoryGame::input() const {
    int index;
    cout << "Enter a unflipped card in [0, " << numSlots - 1 << "]: " << endl;
    cin >> index;

    while (index < 0 || index > numSlots - 1 || bShown[index]) {
        if (index < 0 || index > numSlots - 1) {
            cout << "input is not in [0, " << numSlots - 1 << "]. Re-enter: ";
            cin >> index;
            cout << endl;
        } else {
            cout << "The card is flipped already. Re-enter: ";
            cin >> index;
            cout << endl;
        }
    }
    cout << endl;
    return index;
}

void MemoryGame::play() {
    display();
    int pairsFound = 0;
    int round = 0;
    int firstIndex = -1;

    randomize();

    while (pairsFound < numPairs) {
        round++;
        cout << "Round " << setw(3) << round << ":" << endl;

        int index = input();
        bShown[index] = true;

        if (firstIndex == -1) {
            firstIndex = index;
        } else {
            if (values[firstIndex] == values[index]) {
                pairsFound++;
            } else {
                cout << "Not a match. Try again." << endl;
                bShown[firstIndex] = bShown[index] = false;
            }
            firstIndex = -1;
        }
        display();
    }
    cout << "Congratulations! Found all pairs in " << round << " rounds." << endl;
}