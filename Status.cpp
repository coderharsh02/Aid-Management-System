//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#include "Status.h"
#include <iostream>
#include <cstring>
using namespace std;
namespace sdds
{

	Status::Status(const char *desc)
	{
		if (desc == nullptr)
		{
			n_code = 0;
		}
		else
		{
			cout << sizeof(desc) << endl;
			description = new char[strlen(desc) + 1];
			strcpy(description, desc);
			n_code = 0;
		}
	}

	Status::~Status()
	{
		delete[] description;
		description = nullptr;
	}

	Status &Status::operator=(const char *desc)
	{
		if (desc != NULL)
		{
			delete[] description;
			description = new char[strlen(desc) + 1];
			strcpy(description, desc);
		}
		return *this;
	}

	Status &Status::operator=(int code)
	{
		n_code = code;
		return *this;
	}

	Status::operator int() const
	{
		return n_code;
	}

	Status::operator bool() const
	{
		if (description == nullptr)
			return true;
		else
			return false;
	}

	Status::operator const char *() const
	{
		return description;
	}

	Status &Status::clear()
	{
		delete[] description;
		description = nullptr;
		n_code = 0;
		return *this;
	}

	ostream &operator<<(ostream &ostr, const Status &newstatus)
	{
		if (!bool())
		{
			if ((int)newstatus != 0)
			{
				cout << "ERR#" << (int)newstatus << ": ";
			}
			cout << (const char *)newstatus;
		}
		return ostr;
	}
}