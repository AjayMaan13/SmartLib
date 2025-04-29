#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Publication.h"
#include "Date.h"


using namespace std;

namespace sdds
{
    void Publication::setDefault()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
    }
    Publication::Publication()
    {
        setDefault();
    }
    Publication::Publication(const Publication &pub)
    {
        if (pub.m_title)
        {
            m_title = new char[strlen(pub.m_title) + 1];
            strcpy(m_title, pub.m_title);
            strcpy(m_shelfId, pub.m_shelfId);
            set(pub.m_membership);
            setRef(pub.m_libRef);
            m_date = pub.m_date;
        }
        else
            setDefault();
    }
    Publication &Publication::operator=(const Publication &pub)
    {
        delete[] m_title;
        m_title = nullptr;
        if (pub.m_title)
        {
            m_title = new char[strlen(pub.m_title) + 1];
            strcpy(m_title, pub.m_title);
            strcpy(m_shelfId, pub.m_shelfId);
            set(pub.m_membership);
            setRef(pub.m_libRef);
            m_date = pub.m_date;
        }
        else
            setDefault();

        return *this;
    }
    Publication::~Publication()
    {
        delete[] m_title;
    }

    //**// Methods //**//
    void Publication::set(int member_id)
    {
        m_membership = member_id;
    }
    void Publication::setRef(int value)
    {
        m_libRef = value;
    }
    void Publication::resetDate()
    {
        m_date = Date();
    }

    //**// Queries //**//
    char Publication::type() const
    {
        return 'P';
    }
    bool Publication::onLoan() const
    {
        return m_membership != 0;
    }
    Date Publication::checkoutDate() const
    {
        return m_date;
    }
    bool Publication::operator==(const char *title) const
    {
        return strstr(m_title, title) != NULL;
    }
    Publication::operator const char *() const
    {
        return m_title;
    }
    int Publication::getRef() const
    {
        return m_libRef;
    }

    bool Publication::conIO(std::ios &io) const
    {
        return &io == &std::cin || &io == &std::cout;
    }
    std::ostream &Publication::write(std::ostream &os) const
    {
        char oldFill = os.fill();
        // Check if console output object is IO
        if (conIO(os))
        {
            // Output Settings
            os.setf(ios::left);
            os.fill('.');

            os << "| ";

            // Change width
            os.width(SDDS_SHELF_ID_LEN);
            os << m_shelfId;

            os << " | ";

            // Check width length
            if (strlen(m_title) > SDDS_TITLE_WIDTH) {
                os << string(m_title, m_title + SDDS_TITLE_WIDTH);
            }
            else {
                os.width(SDDS_TITLE_WIDTH);
                os << m_title;
            }
            os << " | ";

            // Output membership
            if (m_membership != 0)
                os << m_membership;
            else
                os << " N/A ";

            os << " | ";

            if (!m_date.errCode())
                os << m_date;
            else
                os << " N/A ";

            os << " |";

            // Fill output is empty
            os.fill(oldFill);
            os.unsetf(ios::left);

            return os;
        }
        else
        {
            os << type() << "\t";
            os << m_libRef;
            os << "\t";
            os << m_shelfId;
            os << "\t";
            os << m_title;
            os << "\t";
            os << m_membership;
            os << "\t";
            os << m_date;

            return os;
        }
    }
    std::istream &Publication::read(std::istream &istr)
    {
        char *title = new char[256];
        char shelfID[SDDS_SHELF_ID_LEN + 2] = {'\0'};
        int membership = 0, libRef = -1;
        Date date;
        setDefault();
        if (conIO(istr))
        {
            cout << "Shelf No: ";
            istr >> shelfID;
            
            if (strlen(shelfID) != SDDS_SHELF_ID_LEN)
                istr.setstate(ios::failbit);
            else
                istr.ignore(1000, '\n');
            cout << "Title: ";
            istr.getline(title, 256, '\n');
            cout << "Date: ";
            istr >> date;
        }
        else
        {
            istr >> libRef;
            istr.ignore();
            istr.get(shelfID, SDDS_SHELF_ID_LEN + 2, '\t');
            istr.ignore();
            istr.get(title, 256, '\t');
            istr.ignore();
            istr >> membership;
            istr.ignore();
            istr >> date;
        }
        if (!date)
            istr.setstate(ios::failbit);
        if (istr)
        {
            delete[] m_title;
            m_title = nullptr;
            if (title)
            {
                m_title = new char[strlen(title) + 1];
                strcpy(m_title, title);
                strcpy(m_shelfId, shelfID);
                m_membership = membership;
                m_date = date;
                m_libRef = libRef;
            }
        }
        delete[] title;
        return istr;
    }
    Publication::operator bool() const
    {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

}
