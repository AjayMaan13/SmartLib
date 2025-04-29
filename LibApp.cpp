#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"
#include "Utils.h"
using namespace std;

namespace sdds
{

    // Constructors with updated members
    LibApp::LibApp(const char *filename)
        : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), // Base constructors
          m_publicationMenu("Choose the type of publication:")
    {
        m_changed = false;
        strncpy(m_fileName, filename, 256); // copy filename
        NOLP = 0;
        LLRN = 0;

        // Output options from mainMenu
        m_mainMenu << "Add New Publication" << "Remove Publication"
                   << "Checkout publication from library" << "Return publication to library";

        // Output options from exitMenu
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationMenu << "Book" << "Publication";
        load(); // Run load function
    }

    // Destructor
    LibApp::~LibApp()
    {
        // Delete all PPA members
        for (int i = 0; i < NOLP; i++)
        {
            delete PPA[i];
        }
    }

    // Confirm action 
    bool LibApp::confirm(const char *message)
    {
        Menu menu(message);
        menu << "Yes";
        int selection = menu.run();

        // Check if the output is yes/1
        return selection == 1;
    }

    // New load function
    void LibApp::load()
    {
        // Print data
        cout << "Loading Data\n";

        // New file
        ifstream infile(m_fileName);
        char type{};
        int i;
        
        // Loop to load data from file
        for (i = 0; infile; i++)
        {
            infile >> type;
            infile.ignore();
            if (infile)
            {
                if (type == 'P')
                    PPA[i] = new Publication;
                else if (type == 'B')
                    PPA[i] = new Book;
                if (PPA[i])
                {
                    infile >> *PPA[i];
                    NOLP++;
                    LLRN = PPA[i]->getRef();
                }
            }
        }
    }

    // New Save function
    void LibApp::save()
    {
        cout << "Saving Data\n";
        ofstream ofs(m_fileName);

        // Saves the loaded data
        for (int i = 0; i < NOLP; i++)
        {
            if (PPA[i]->getRef() != 0) // Condition
                ofs << *PPA[i] << endl;
        }
    }

    // New search function
    // searchType: 1 = Search all | 2 = Search on loan | 3 = Search available publications
    int LibApp::search(int searchType)
    {
        // Let the user choose
        PublicationSelector ps("Select one of the following found matches:", 15);
        int s, i, resultReturned{};
        char *title = new char[256];
        bool matchFound = false;

        // Match the searchType
        if (searchType == 1)
        {
            s = m_publicationMenu.run(); // run function

            // Switch to check multiple cases
            switch (s)
            {
            case 0:
                cout << "Aborted!\n"; // Out of program
            case 1:
                cin.ignore();

                cout << "Publication Title: ";

                cin.getline(title, 256);

                // Loop to see titles
                for (i = 0; i < NOLP; i++)
                {
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() != 'P')
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }

                // See if match is found
                if (matchFound)
                {
                    ps.sort();
                    resultReturned = ps.run();
                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else // No match found
                    cout << "No matches found!\n";
                break;
            case 2:
                // Second case
                cin.ignore();
                cout << "Publication Title: ";
                cin.getline(title, 256);
                for (i = 0; i < NOLP; i++)
                {
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() == 'P')
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }
                // See if match is found
                if (matchFound)
                {
                    ps.sort();
                    resultReturned = ps.run();
                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else
                    cout << "No matches found!\n";
                break;
            }
        }
        else if (searchType == 2) // If searchType if 2
        {
            // call run() function
            s = m_publicationMenu.run();

            // Switch case for s
            switch (s)
            {
            case 0:
                cout << "Aborted!\n"; // out of program
            case 1: // first case
                cin.ignore();
                cout << "Publication Title: ";
                cin.getline(title, 256);

                // Loop data
                for (i = 0; i < NOLP; i++) {
                    // See if conditions matches
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() != 'P' && PPA[i]->onLoan())
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }

                // Check if match is found
                if (matchFound)
                {
                    ps.sort();

                    resultReturned = ps.run();

                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else // No match is found
                    cout << "No matches found!\n";
                break;
            case 2:
                cin.ignore(); // call ignore function

                // Get publication title
                cout << "Publication Title: ";
                cin.getline(title, 256);

                //Loop to change output
                for (i = 0; i < NOLP; i++)
                {
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() == 'P' && PPA[i]->onLoan())
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }

                // See if match is found
                if (matchFound) {
                    ps.sort();
                    resultReturned = ps.run();
                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else
                    cout << "No matches found!\n";
                break;
            }
        }
        else if (searchType == 3) // See if seachType is entered 3
        {
            // call run function
            s = m_publicationMenu.run();
            switch (s)
            {
            case 0:
                cout << "Aborted!\n"; // case abborted
            case 1:
                cin.ignore();

                // Get publication title
                cout << "Publication Title: ";
                cin.getline(title, 256);

                // Loop to enter data
                for (i = 0; i < NOLP; i++)
                {
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() != 'P' && !PPA[i]->onLoan())
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }
                if (matchFound) // Check if match is found
                {
                    ps.sort();
                    resultReturned = ps.run();
                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else
                    cout << "No matches found!\n";
                break;
            case 2:
                // Case 2
                cin.ignore();

                // Get input
                cout << "Publication Title: ";
                cin.getline(title, 256); // Input

                // Loop
                for (i = 0; i < NOLP; i++)  {
                    if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() == 'P' && !PPA[i]->onLoan())
                    {
                        matchFound = true;
                        ps << *PPA[i];
                    }
                }
                if (matchFound) // Match found
                {
                    ps.sort();
                    resultReturned = ps.run();
                    if (resultReturned == 0)
                        cout << "Aborted!\n";
                }
                else
                    cout << "No matches found!\n";
                break;
            }
        }

        // Delete title and return result
        delete[] title;
        return resultReturned;
    }

    // getPub function to get certain publication
    Publication *LibApp::getPub(int libRef)
    {
        // Loop to find publication
        for (int i = 0; i < NOLP; i++)
        {
            // See if the match is found
            if (PPA[i]->getRef() == libRef)
                return PPA[i];
        }
        return nullptr;
    }

    // Return the publication
    void LibApp::returnPub()
    {
        // Variable Initialisation
        int index = -1;
        int daysOnLoan, daysLate;
        double penalty;
        Date d;

        // output text
        cout << "Return publication to the library\n";

        // search by reference of 2
        int searchReturnVal = search(2); // search function returns 0 by default

        // Check conditions
        if (searchReturnVal > 0) { 
            // Loop to getRef and change index of which pub to return
            for (int i = 0; i < NOLP; i++) {
                if (PPA[i]->getRef() == searchReturnVal)
                    index = i;
            }
            if (index > -1)
            {
                cout << *PPA[index] << endl;

                // Confirm to return publication
                if (confirm("Return Publication?"))
                {
                    daysOnLoan = d - PPA[index]->checkoutDate();
                    if (daysOnLoan > SDDS_MAX_LOAN_DAYS)
                    {
                        // Update variables and return data
                        daysLate = daysOnLoan - SDDS_MAX_LOAN_DAYS;
                        penalty = .50 * daysLate;
                        cout << "Please pay $";
                        cout << fixed << setprecision(2) << penalty;
                        cout.unsetf(ios::fixed);
                        cout << " penalty for being " << daysLate << " days late!\n";
                    }
                    PPA[index]->set(0);
                    m_changed = true;
                    cout << "Publication returned\n";
                }
            }
        }
    }

    // Create new Publication
    void LibApp::newPublication()
    {
        // Initiate variables
        int s;
        Publication *pub = nullptr;

        // Check if library is full
        if (NOLP == SDDS_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!\n";
            return;
        }
        else
        {
            // Output text
            cout << "Adding new publication to the library\n";
            s = m_publicationMenu.run(); // call run function

            // See the cases of the run function return
            switch (s)
            {
            case 0:
                cout << "Aborted!\n"; // out of program
                break;
            case 1: // Create new book
                // Initiate a book
                pub = new Book;

                // Read input
                pub->read(cin);
                if (cin.fail())
                    cin.ignore(1000, '\n');
                else
                {
                    // Confirm to add the book
                    if (confirm("Add this publication to the library?"))
                    {
                        // Check condition
                        if (pub)
                        {
                            LLRN++;
                            pub->setRef(LLRN);
                            PPA[NOLP] = pub;
                            NOLP++;
                            m_changed = true;
                            cout << "Publication added\n";
                        }
                        else // an error occured
                        {
                            cout << "Failed to add publication!\n";
                            delete pub;
                        }
                    }
                    else
                        cout << "Aborted!\n"; // Out of action
                }
                break;
            case 2: // Add new publicatoin

                // Initiate publication
                pub = new Publication;

                // read input
                pub->read(cin);

                // if any errors occur
                if (cin.fail())
                    cin.ignore(1000, '\n');
                else
                {
                    // Confirm to add publication
                    if (confirm("Add this publication to the library?"))
                    {
                        if (pub) // check if it exists
                        {
                            LLRN++;
                            pub->setRef(LLRN);
                            PPA[NOLP] = pub;
                            NOLP++;
                            m_changed = true;
                            cout << "Publication added\n";
                        }
                        else // No action
                        {
                            cout << "Failed to add publication!\n";
                            delete pub;
                        }
                    }
                    else
                        cout << "Aborted!\n"; // Out of action
                }
                break;
            }
        }
    }

    // Remove a publication
    void LibApp::removePublication()
    {
        // Initiate variables
        int searchReturnVal;
        int index = -1;

        // Output texts
        cout << "Removing publication from the library\n";
        searchReturnVal = search(1); // call search
        // search function returns 0 by default

        // Check cases and conditions
        if (searchReturnVal > 0)
        { 
            // change value
            for (int i = 0; i < NOLP; i++)
            {
                if (PPA[i]->getRef() == searchReturnVal)
                    index = i;
            }
            if (index > -1) // check condition
            {
                cout << *PPA[index] << endl;

                // confirm to remove
                if (confirm("Remove this publication from the library?"))
                {
                    PPA[index]->setRef(0);
                    m_changed = true;
                    cout << "Publication removed\n";
                }
            }
        }
    }

    // Check out a certain publication
    void LibApp::checkOutPub()
    {
        // Initiate variables
        int searchReturnVal, num, len, index = -1;
        cout << "Checkout publication from the library\n"; // Output texts
        searchReturnVal = search(3); // call Search 
        // search returns 0 by default

        // Check conditions
        if (searchReturnVal > 0)
        { 
            // Loop to change data
            for (int i = 0; i < NOLP; i++)
            {
                if (PPA[i]->getRef() == searchReturnVal)
                    index = i;
            }
            // Check condition
            if (index > -1)
            {
                cout << *PPA[index] << endl;

                // Confirm to check out publication
                if (confirm("Check out publication?"))
                {
                    // Add info
                    cout << "Enter Membership number: ";

                    // Loop to check if input is valid or not
                    do
                    {
                        cin >> num;
                        len = numLen(num); // find length of number
                        if (len != 5) // ERROR!
                            cout << "Invalid membership number, try again: ";
                    } while (len != 5);

                    // Change value
                    PPA[index]->set(num);
                    m_changed = true;
                    cout << "Publication checked out\n";
                }
            }
        }
    }

    // Ending text output
    void LibApp::terminateMessage()
    {
        cout << "\n-------------------------------------------\n";
        cout << "Thanks for using Seneca Library Application" << endl;
    }

    // Run the main program logic
    void LibApp::run()
    {
        // Initiate variables
        int s, ss;

        // Loop the main logic
        do
        {
            s = m_mainMenu.run(); // call run method

            // Use switch to run multiple cases
            switch (s)
            {
            case 1: // Add publication
                newPublication();
                cout << "\n";
                break;
            case 2: // Remove publication
                removePublication();
                cout << "\n";
                break;
            case 3: // Check out a publication
                checkOutPub();
                cout << "\n";
                break;
            case 4: // Return a publication
                returnPub();
                cout << "\n";
                break;
            case 0: // Exit the program
                if (!m_changed) // See if anything is changed
                    s = -1;
                else
                {
                    // Run the exit menu run() method
                    ss = m_exitMenu.run();

                    // Switch to check cases
                    switch (ss)
                    {
                    case 1: // Save data
                        save();
                        s = -1;
                        break;
                    case 2: // Don't save
                        cout << "\n";
                        break;
                    case 0: // Discard all changes
                        if (confirm("This will discard all the changes are you sure?"))
                            s = -1;
                        else
                            cout << "\n";
                        break;
                    }
                }
            }
        } while (s != -1);
        // Loop ends
        
        terminateMessage(); // Ending of code
    }

}
