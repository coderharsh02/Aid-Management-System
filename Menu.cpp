//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "Utils.h"
#include "Menu.h"
using namespace std;
namespace sdds
{

	Menu::Menu()
	{

		if (m_options > MAX_OPTIONS || m_menuList == nullptr)
		{
			m_options = 0;
			m_menuList = nullptr;
		}
	}

	Menu::~Menu()
	{
		delete[] m_menuList;
	}

	unsigned int Menu::run() const
	{
		int option;
		cout << m_menuList << "0- Exit" << endl;
		option = ut.getint(0, m_options, "> ");
		return option;
	}
}