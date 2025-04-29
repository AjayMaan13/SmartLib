#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Book.h"

using namespace std;

namespace sdds {
    // Initial Constructor
    Book::Book(): Publication() {
        m_name = nullptr;
    }

    //**// The Rule of Three //**//
    Book::Book(const Book& book): Publication(book) {
        // Check if name is non-empty
        if (book.m_name) {
            // Assign new name
            m_name = new char[strlen(book.m_name) + 1];
            strcpy(m_name, book.m_name);
        } else {
            m_name = nullptr;
        }
    }

    // Operator overload
    Book& Book::operator=(const Book& book) {
        // Change address
        if (this != &book) {
            Publication::operator=(book);
            delete[] m_name;
            m_name = nullptr;

            // Check if name is non-empty
            if (book.m_name) {
                m_name = new char[strlen(book.m_name) + 1];
                strcpy(m_name, book.m_name);
            }
        }
        return *this;
    }

    // Destructor
    Book::~Book() {
        delete[] m_name;
    }

    //**// Methods //**// 
    // Return type of Book
    char Book::type() const {
        return 'B';
    }

    // Write function
    std::ostream& Book::write(std::ostream& os) const {
        // Invoke write of Base Class
        Publication::write(os);

        // Check if incoming argument is a console IO object
        if (Publication::conIO(os)) {
            os << " ";

            // Check if length of name is more than MACRO
            if (strlen(m_name) > SDDS_AUTHOR_WIDTH) {
                for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
                    os << m_name[i];
                }
            } else {
                os.setf(ios::left);
                os.width(SDDS_AUTHOR_WIDTH);
                os.fill(' ');
                os << m_name;
                os.unsetf(ios::left);
            }
            os << " |";
        } else {
            os << '\t';
            os << m_name;
        }
        return os;
    }

    // Read Function
    std::istream& Book::read(std::istream& istr) {
        char author[256 + 1]{};
        Publication::read(istr); // Invoke base class
        delete[] m_name;
        m_name = nullptr;

        // Check if incoming argument is a console IO object
        if (Publication::conIO(istr)) {
            istr.ignore(3000, '\n');
            cout << "Author: ";
            istr.getline(author, 256 + 1, '\n');
        } else {
            istr.ignore();
            istr.get(author, 256 + 1, '\n');
        }

        // If incoming istream object is not in a fail state
        if (istr) {
            m_name = new char[strlen(author) + 1];
            strcpy(m_name, author);
        }
        return istr;
    }

    // Sets name and date of the Book
    void Book::set(int member_id) {
        Publication::set(member_id);
        Publication::resetDate();
    }

    // Return true if book is non-empty
    Book::operator bool() const {
        return m_name != nullptr && Publication::operator bool();
    }
}
