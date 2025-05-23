#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
#include "Lib.h"

namespace sdds {
    class Book:public Publication {
	    char* m_name{};

    public:
        Book();

        // Rule of Three
        Book(const Book& book);
        Book& operator=(const Book& book);
        ~Book();

        // Methods
        char type()const;
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& istr);
        void set(int member_id);
        operator bool() const;
    };
}
#endif