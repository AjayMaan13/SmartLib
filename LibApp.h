#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
#include <iostream>
#include "Book.h"
#include "PublicationSelector.h"

namespace sdds {
   class LibApp {
        bool m_changed; // A flag to keep track of changes made to the application data. 
        Menu m_mainMenu; // used as the main menu of the application
        Menu m_exitMenu; // used when exiting the program if any changes are made to the data
        Menu m_publicationMenu; //  hold the publication data file name.
        char m_fileName[256]{};
        Publication* PPA[SDDS_LIBRARY_CAPACITY]{}; // an array of Publication pointers
        int NOLP; // Number Of Loaded Publications
        int LLRN; // Last Library Reference Number

        //****// FUNCTIONS //****//
        bool confirm(const char* message);/* Instantiate a Menu in this function and 
                                             initialize it with the message argument.
                                             Then add only a "yes" as a single menu 
                                             item to the Menu.
                                          */
        void load();  // prints: "Loading Data"<NEWLINE>
        void save();  // prints: "Saving Data"<NEWLINE>
        int search(int searchType);  // prints: "Searching for publication"<NEWLINE>

        void returnPub();  /*  Calls the search() method.
                               prints "Returning publication"<NEWLINE>
                               prints "Publication returned"<NEWLINE>
                               sets m_changed to true;
                           */
        void newPublication();
        void removePublication();
        void checkOutPub();
        Publication* getPub(int libRef);/*  Create a method to return the 
                                            address of a Publication object 
                                            in the PPA that has the library 
                                            reference number matching the 
                                            "libRef" argument.
                                        */
    public:
        LibApp(const char* filename); //initialize and set the attributes and load the publication records from the database
        ~LibApp();
        void run(); // main application driver.
        void terminateMessage();
    };
}
#endif



