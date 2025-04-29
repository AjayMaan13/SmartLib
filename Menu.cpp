#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds {

    //////// "MenuItem" Structure Definition ////////
    // Initialises item description
    void MenuItem::setEmpty()
    {
	    m_desc = nullptr;
    }
    // Constructors
    MenuItem::MenuItem() { setEmpty(); }
    MenuItem::MenuItem(const char* title) {
      // If title is valid
      if (title) {
        // Add new title
        m_desc = new char[strlen(title) + 1];
        strcpy(m_desc, title);
      }
      else setEmpty();
    }

    // Destructor
    MenuItem::~MenuItem() {
	    delete[] m_desc;
    }

    std::ostream& MenuItem::display(std::ostream& os)const {
      // If item is not empty, display its description
      if (!isEmpty()) os << m_desc;
      return os;
    }

    bool MenuItem::isEmpty() const {
      // Check if description is Empty or Not
	    return m_desc == nullptr || m_desc[0] == '\0';
    }

    // Bool operator overload
    MenuItem::operator bool() const {
	    return !isEmpty();
    }

    // Return item description
    MenuItem::operator const char* () const {
	    return m_desc;
    }


    //////// "Menu" Structure Definition ////////
    // Display Title
    std::ostream& Menu::displayTitle(std::ostream& os)const {
      m_title.display(os);
      return os;
    }

    std::ostream& Menu::display(std::ostream& os)const {
      displayTitle(os); // Display Title
      if (m_title) os<< "\n"; 
      // Loop to list all items, if any
      for (unsigned int i = 0; i < m_ni; i++) {
          os << setfill(' ') << setw(2) << i + 1 << "- ";
          m_items[i]->display() << "\n";
      }
      os << " 0- Exit\n";
      os << "> ";
      return os;
    }

    // Constructor
    Menu::Menu(const char* title) {
      // Allocate memory for new title
	    m_title.m_desc = new char[strlen(title) + 1];
	    strcpy(m_title.m_desc, title);
	    m_ni = 0;
    }

    // Desctructor
    Menu::~Menu() {
      // Loop to deallocate memory
	    for (unsigned int i = 0; i < m_ni; i++) {
		    delete m_items[i];
	    }
    }

    // Operator Overload <<
    Menu& Menu::operator<<(const char* menuitem) {
      if (m_ni != MAX_MENU_ITEMS) {
        // Allocate memory for new MenuItem
        m_items[m_ni] = new MenuItem(menuitem);
        m_ni++;
      }
      return *this;
    }

    // Return true if Items array is not empty
    Menu::operator bool()const {
	    return m_ni > 0;
    }

    // Main logic of Menu 
    unsigned int Menu::run() const{
        display();
	    int selection = inputIntRange(0, m_ni);
	    return selection;
    }

    // Return Number of Items
    Menu::operator unsigned int() const {
	    return m_ni;
    }

    // Return Number of Items
    Menu::operator int() const {
	    return m_ni;
    }

    // Operator Overload ~
    unsigned int Menu::operator~()const {
        display();
	    int selection = inputIntRange(0, m_ni);
	    return selection;
    }

    // Operator Overload <<, display Title
    std::ostream& operator<<(std::ostream& os, const Menu& m) {
	    return m.displayTitle(os);
    }

    // Operator Overload
    const char* Menu::operator[](unsigned int index) const {
      // Returns current menu item if index is valid
	    if(index <= m_ni) return m_items[index]->m_desc;
      // Else if, index is invalid
	    return m_items[index%m_ni]->m_desc;
    }
}