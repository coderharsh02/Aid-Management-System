//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	bool Date::validate()
	{

		if (year < 2022 || year > max_year)
		{
			m_st = "Invalid year in date";
			m_st = 1;
			return false;
		}
		else if (month < 1 || month > 12)
		{
			m_st = "Invalid month in date";
			m_st = 2;
			return false;
		}
		else if (day < 1 || day > ut.daysOfMon(month, year))
		{
			m_st = "Invalid day in date";
			m_st = 3;
			return false;
		}
		else
		{
			m_st.clear();
		}
		return true;
	}

	Date::Date()
	{
		ut.getSystemDate(&year, &month, &day);
	}

	Date::Date(int year, int month, int day)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		validate();
	}

	Date &Date::operator=(const Date &date)
	{
		year = date.year;
		month = date.month;
		day = date.day;
		m_st = date.m_st;
		m_formatted = date.m_formatted;

		return *this;
	}

	bool Date::operator==(Date &date) const
	{
		if (uniqueDateValue() == date.uniqueDateValue())
			return true;
		return false;
	}

	bool Date::operator!=(Date &date) const
	{
		if (uniqueDateValue() != date.uniqueDateValue())
			return true;
		return false;
	}

	bool Date::operator<(Date &date) const
	{
		if (uniqueDateValue() < date.uniqueDateValue())
			return true;
		return false;
	}

	bool Date::operator>(Date &date) const
	{
		if (uniqueDateValue() > date.uniqueDateValue())
			return true;
		return false;
	}

	bool Date::operator<=(Date &date) const
	{
		if (uniqueDateValue() <= date.uniqueDateValue())
			return true;
		return false;
	}

	bool Date::operator>=(Date &date) const
	{
		if (uniqueDateValue() >= date.uniqueDateValue())
			return true;
		return false;
	}

	const Status &Date::state() const
	{
		return m_st;
	}

	Date &Date::formatted(bool flag)
	{
		m_formatted = flag;
		return *this;
	}

	Date::operator bool() const
	{
		if (this)
		{
			return m_st;
		}
		return NULL;
	}

	ostream &Date::write(ostream &ostr) const
	{

		if (m_formatted)
		{
			ostr << year << "/";
			ostr << setfill('0') << setw(2) << month << "/";
			ostr << setfill('0') << setw(2) << day;
		}
		else
		{
			ostr << year % 2000;
			ostr << setfill('0') << setw(2) << month;
			ostr << setfill('0') << setw(2) << day;
		}

		return ostr;
	}

	istream &Date::read(istream &istr)
	{
		int input;
		istr.clear();
		istr >> input;

		if (istr)
		{

			int count = 1;
			while (input != 0)
			{
				if (count == 1)
				{
					day = input % 100;
					month = 0;
					year = 0;
				}
				else if (count == 2)
				{
					month = input % 100;
					year = 0;
				}
				else if (count == 3)
				{
					year = 2000 + input % 100;
				}
				input = input / 100;
				count++;
			}
			if (year == 0)
				year = 2022;

			if (!validate())
			{
				istr.setstate(ios::badbit);
			}
		}
		else
		{
			m_st = "Invalid date value";
		}

		istr.ignore(1000, '\n');
		return istr;
	}

	ostream &operator<<(ostream &ostr, const Date &date)
	{
		return date.write(ostr);
	}

	istream &operator>>(istream &istr, Date &date)
	{
		return date.read(istr);
	}
}