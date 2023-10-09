/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa5
*/
// Shuffle.cpp
#include"List.h"

using namespace std;

// Shuffle function
void shuffle(List& D) {
    // Creates new list R
    List R;

    // Calculates midpoint to determine where exactly to split List D
    int midPoint = D.length() / 2;
    D.moveBack();

    // Inserts the last half of elements into List R
    // Equally splits initial contents of List D into 2 separate lists
    while(D.position() > midPoint) {
        R.insertAfter(D.back());
        D.eraseBefore();
    }        

    D.moveFront();

    // Prepares to merge the elements by inserting each element of R at each
    // cursor position of D.
    while(R.position() != R.length()) {
        // Allows elements of Lists D and R to merge
        D.insertBefore(R.peekNext());
  
        if(D.position() != D.length()) {
            D.moveNext(); 
        } else { break; } 

        R.moveNext();
    }
}

int main(int argc, char *argv[]) {
    // Throws an error if there is anything but 1 additional argument
    if(argc != 2) {
        cout << "Invalid number of arguments" << endl;
        exit(EXIT_FAILURE);
    } 

    // Set the size to equal the inputted value
    int size = atoi(argv[1]);

    cout << "deck size\tshuffle count" << endl;
    cout << "------------------------------" << endl;

    // Perform shuffles for list sizes ranging from 1 to the inputted size
    for(int i = 1; i <= size; i++) {
        List D;

        // Inserts elements 0 to i - 1 in numeric order
        for(int j = 0; j < i; j++) {
            D.insertBefore(j);
        }

        // Creates a copy of the created list to help check when it returns to 
        // its original state
        // Calls shuffle on List D
        List I = D;
        shuffle(D);
        int shuffleCount = 1;

        // While List D != original List I, shuffle will keep being called
        // The number of shuffles made is tracked with shuffleCount
        while(!(D == I)) {
            shuffle(D);
            shuffleCount++;
        }

        // Prints the number of shuffles to return to original state for each i
        // 1 <= i <= size
        cout << " " << i << "\t\t " << shuffleCount << endl;
    }
}
