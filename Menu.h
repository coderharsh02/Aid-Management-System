//####################################
// Project: Aid Management System  ###
//####################################

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds
{
	unsigned const int MAX_OPTIONS = 15;

	class Menu
	{
	public:
		unsigned int m_options = 0;
		char *m_menuList{nullptr};
		Menu();
		~Menu();
		unsigned int run() const;
	};

}
#endif // !SDDS_MENU_H
