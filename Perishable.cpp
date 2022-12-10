//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <string.h>
#include <fstream>
#include "Item.h"
#include "Perishable.h"
#include "iProduct.h"
#include "Utils.h"
#include "Date.h"

using namespace std;

namespace sdds
{
	Perishable::Perishable(const Perishable &permishable)
	{
		if (permishable)
		{
			Item::operator=(permishable);
			delete[] instructions;
			instructions = new char[strlen(permishable.instructions) + 1];
			strcpy(instructions, permishable.instructions);
			m_expDate = permishable.m_expDate;
		}
	}
	Perishable &Perishable::operator=(const Perishable &permishable)
	{
		if (this != &permishable)
		{
			// (Item&)*this = permishable;
			Item::operator=(permishable);
			delete[] instructions;
			instructions = new char[strlen(permishable.instructions) + 1];
			strcpy(instructions, permishable.instructions);
			m_expDate = permishable.m_expDate;
		}
		return *this;
	}
	Perishable::~Perishable()
	{
		delete[] instructions;
		instructions = nullptr;
	}
	const Date &Perishable::expiry() const
	{
		return m_expDate;
	}

	int Perishable::readSku(istream &istr)
	{
		m_sku = ut.getint(10000, 39999, "SKU: ");
		return m_sku;
	}
	ofstream &Perishable::save(ofstream &ofstr) const
	{
		if (m_sate)
		{
			Item::save(ofstr);
			ofstr << "\t";
			if (instructions && strlen(instructions) > 0)
			{
				ofstr << instructions;
			}
			ofstr << "\t";
			Date date = m_expDate;
			date.formatted(false);
			date.write(ofstr);
		}
		return ofstr;
	}

	ifstream &Perishable::load(ifstream &ifstr)
	{
		Item::load(ifstr);
		char m_ins[900];
		ifstr.getline(m_ins, 1000, '\t');
		m_expDate.read(ifstr);
		delete[] instructions;
		instructions = new char[strlen(m_ins) + 1];
		strcpy(instructions, m_ins);
		if (ifstr.bad())
		{
			m_sate = "Input file stream read (perishable) failed!";
		}
		return ifstr;
	}
	ostream &Perishable::display(ostream &ostr) const
	{
		if (ostr.bad())
		{
			ostr << m_sate;
		}
		else
		{
			if (operator bool())
			{
				if (linear())
				{
					Item::display(ostr);
					if (instructions != nullptr && instructions[0] != '\0')
					{
						ostr << "*";
					}
					else
					{
						ostr << " ";
					}
					m_expDate.write(ostr);
				}
				else
				{
					ostr << "Perishable ";
					Item::display(ostr);
					ostr << "Expiry date: " << m_expDate << endl;
					if (instructions != nullptr && instructions[0] != '\0')
					{
						ostr << "Handling Instructions: " << instructions << endl;
					}
				}
			}
		}
		return ostr;
	}
	istream &Perishable::read(istream &istr)
	{
		Item::read(istr);

		delete[] instructions;
		instructions = nullptr;
		char enterInstr[900];
		cout << "Expiry date (YYMMDD): ";
		istr >> m_expDate;
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n')
		{
			istr.getline(enterInstr, 900, '\n');
			instructions = new char[strlen(enterInstr) + 1];
			strcpy(instructions, enterInstr);
		}
		else
		{
			istr.clear();
		}
		if (istr.fail())
		{
			m_sate = "Perishable console date entry failed!";
		}
		return istr;
	}
}