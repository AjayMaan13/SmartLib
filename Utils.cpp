#include <iostream>
using namespace std;
#include "Utils.h"
namespace sdds {

    // Foolproof integer entry within limits
     int inputIntRange(int minRange, int maxRange) {
        int i;
        bool fail;
        // Loop to get input
        do {
            cin >> i;
            fail = cin.fail();
            if (fail) {
                cout << "Invalid Selection, try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (i<minRange || i>maxRange) {
                cout << "Invalid Selection, try again: ";
                cin.clear();
            }
        } while (i<minRange || i>maxRange || fail); // Check if its an valid input
        cin.clear();
        return i;
    }

    // Finds length of a number's characters
    int numLen(int n) {
        int i = 0;
        if (n > 0) {
            while (n != 0) {
                n = n / 10;
                i++;
            }
        }
        if (n < 0) i = -1;
        return i;
    }
}