//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include "Status.h"
using namespace std;

namespace sdds
{

	const int max_year = 2030;
	class Date
	{

		sdds::Status m_st;

	private:
		int year = 0;
		int month = 0;
		int day = 0;
		bool m_formatted = true;

		bool validate();
		int uniqueDateValue() const
		{
			return (year * 372 + month * 31 + day);
		}

	public:
		Date();
		Date(int year, int month, int day);
		Date &operator=(const Date &date);
		bool operator==(Date &date) const;
		bool operator!=(Date &date) const;
		bool operator<(Date &date) const;
		bool operator>(Date &date) const;
		bool operator<=(Date &date) const;
		bool operator>=(Date &date) const;
		const Status &state() const;
		Date &formatted(bool flag);
		operator bool() const;
		ostream &write(ostream &ostr) const;
		istream &read(istream &istr);
		friend ostream &operator<<(ostream &ostr, const Date &date);
		friend istream &operator>>(istream &istr, Date &date);
	};
	ostream &operator<<(ostream &ostr, const Date &date);
	istream &operator>>(istream &istr, Date &date);
}

#endif