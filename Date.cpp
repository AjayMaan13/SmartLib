#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Lib.h"
#include "Date.h"
using namespace std;

namespace sdds
{

   // Some variables to be used
   bool sdds_test = false;
   int sdds_year = 2023;
   int sdds_mon = 12;
   int sdds_day = 25;

   // Validate date
   bool Date::validate()
   {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR + 1)
      {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12)
      {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays())
      {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays() const
   {
      int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
   int Date::systemYear() const
   {
      int theYear = sdds_year;
      if (!sdds_test)
      {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         theYear = lt.tm_year + 1900;
      }
      return theYear;
   }
   void Date::setToToday()
   {
      if (sdds_test)
      {
         m_day = sdds_day;
         m_mon = sdds_mon;
         m_year = sdds_year;
      }
      else
      {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         m_day = lt.tm_mday;
         m_mon = lt.tm_mon + 1;
         m_year = lt.tm_year + 1900;
      }
      errCode(NO_ERROR);
   }

   // Days since 0001/01/01
   int Date::daysSince0001_1_1() const
   {

      int ty = m_year;
      int tm = m_mon;
      if (tm < 3)
      {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }

   // Constructor
   Date::Date() : m_CUR_YEAR(systemYear())
   {
      setToToday();
   }

   // Constructor
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear())
   {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }

   // Status of the date
   const char *Date::dateStatus() const
   {
      return DATE_ERROR[errCode()];
   }

   // Current Year
   int Date::currentYear() const
   {
      return m_CUR_YEAR;
   }

   // error code changed
   void Date::errCode(int readErrorCode)
   {
      m_ErrorCode = readErrorCode;
   }

   // error code return
   int Date::errCode() const
   {
      return m_ErrorCode;
   }

   // Check if its bad right now
   bool Date::bad() const
   {
      return m_ErrorCode != 0;
   }
   std::istream &Date::read(std::istream &is)
   {
      errCode(NO_ERROR);
      int year, month, day;
      char slash;
      is >> year >> slash >> month >> slash >> day;
      if (is.fail())
      {
         errCode(CIN_FAILED);
         is.clear();
      }
      else
      { 
         *this = Date(year, month, day);
      }
      return is; 
   }

   std::ostream &Date::write(std::ostream &os) const
   {
      if (bad())
      {
         os << dateStatus();
      }
      else
      {
         char oldFill = os.fill();
         os << m_year << "/";


         // display month
         os.setf(ios::right);
         os.width(2);
         os.fill('0');
         os << m_mon << "/";


         // display day
         os.setf(ios::right);
         os.width(2);
         os.fill('0');
         os << m_day;


         os.fill(oldFill);
         os.unsetf(ios::right);
      }
      return os;
   }


   //**// Operators //**//
   bool Date::operator==(const Date &other) const {
      return this->daysSince0001_1_1() == other.daysSince0001_1_1();
   }

   bool Date::operator!=(const Date &other) const {
      return this->daysSince0001_1_1() != other.daysSince0001_1_1();
   }

   bool Date::operator>=(const Date &other) const {
      return this->daysSince0001_1_1() >= other.daysSince0001_1_1();
   }

   bool Date::operator<=(const Date &other) const {
      return this->daysSince0001_1_1() <= other.daysSince0001_1_1();
   }

   bool Date::operator<(const Date &other) const {
      return this->daysSince0001_1_1() < other.daysSince0001_1_1();
   }

   bool Date::operator>(const Date &other) const {
      return this->daysSince0001_1_1() > other.daysSince0001_1_1();
   }
   int Date::operator-(const Date& other) const {
        return this->daysSince0001_1_1() - other.daysSince0001_1_1();
    }

   // bool type conversion operator
   Date::operator bool() const
   {
      if (!bad())
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   ostream &operator<<(ostream &os, const Date &RO) {
      return RO.write(os);
   }

   istream &operator>>(istream &is, Date &RO) {
      return RO.read(is);
   }

}

