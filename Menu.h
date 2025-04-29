#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20; // Maximum menu item number
    class Menu;
    class MenuItem {
	  char* m_desc{}; // Item description
	  void setEmpty();

	  // Constructors
	  MenuItem();
	  MenuItem(const char* title);
	  MenuItem(const MenuItem& mi) = delete; 

	  void operator=(const MenuItem& mi) = delete; // Delete copy operator
	  ~MenuItem(); // Destructor
	  std::ostream& display(std::ostream& os = std::cout)const;
	  operator bool() const; 
	  operator const char* () const;
	  bool isEmpty() const;
	  friend Menu; // Make "Menu" class a friend
    };

	// Menu class
    class Menu {
	  MenuItem m_title; // Title
	  MenuItem* m_items[MAX_MENU_ITEMS]{}; // Array of "MenuItem"s
	  unsigned int m_ni; // Number of Items
	  std::ostream& display(std::ostream& os = std::cout)const;
    public:
	  Menu(const char* title = ""); // Constructors
	  ~Menu(); // Destructors
	  Menu(const Menu& menu) = delete; 
	  void operator=(const Menu& menu) = delete; // Delete copy operator
	  Menu& operator<<(const char* menuitem);
	  operator bool()const;
	  unsigned int run() const;
	  operator unsigned int() const;
	  operator int() const;
	  unsigned int operator~()const;
	  const char* operator[](unsigned int index) const;
	  std::ostream& displayTitle(std::ostream& os)const;
    };
    std::ostream& operator<<(std::ostream& os, const Menu& m);
}


#endif
