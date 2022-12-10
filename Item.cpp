//####################################
// Project: Aid Management System  ###
//####################################

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Utils.h"
#include "Item.h"

using namespace std;

namespace sdds
{

	bool Item::linear() const
	{
		return m_linear;
	}

	Item::Item(const Item &item)
	{
		*this = item;
	}

	Item &Item::operator=(const Item &item)
	{
		if (m_discreiption)
			delete[] m_discreiption;
		if (item.m_discreiption)
		{
			m_discreiption = new char[strlen(item.m_discreiption) + 1];
			strcpy(m_discreiption, item.m_discreiption);
		}
		m_linear = item.m_linear;
		m_price = item.m_price;
		m_qty = item.m_qty;
		m_qtyNeeded = item.m_qtyNeeded;
		m_sate = item.m_sate;
		m_sku = item.m_sku;
		return *this;
	}

	Item::~Item()
	{
		if (m_discreiption)
			delete[] m_discreiption;
		if (m_sate)
			delete m_sate;
		m_discreiption = nullptr;
		m_sate = nullptr;
	}

	int Item::readSku(std::istream &istr)
	{
		int sku;
		sku = ut.getint(40000, 99999, "SKU: ");
		m_sku = sku;
		return sku;
	}

	int Item::operator-=(int qty)
	{
		m_qty -= qty;
		return m_qty;
	}

	int Item::operator+=(int qty)
	{
		m_qty += qty;
		return m_qty;
	}

	Item::operator double() const
	{
		return m_price;
	}

	Item::operator bool() const
	{
		return m_sate && m_sku;
	}

	int Item::qtyNeeded() const
	{
		return m_qtyNeeded;
	}

	int Item::qty() const
	{
		return m_qty;
	}

	void Item::linear(bool isLinear)
	{
		m_linear = isLinear;
	}

	std::ofstream &Item::save(std::ofstream &ofstr) const
	{

		if (m_sate)
		{
			ofstr << m_sku << "\t" << m_discreiption << "\t" << m_qty << "\t" << m_qtyNeeded << "\t" << fixed << setprecision(2) << m_price;
		}

		return ofstr;
	}

	std::ifstream &Item::load(std::ifstream &ifstr)
	{
		if (m_discreiption)
		{
			delete[] m_discreiption;
			m_discreiption = nullptr;
		}

		char temp[500];
		if (ifstr)
		{
			ifstr >> m_sku;
			ifstr.ignore(10000, '\t');
			ifstr.getline(temp, 1000, '\t');
			ifstr >> m_qty;
			ifstr.ignore(10000, '\t');
			ifstr >> m_qtyNeeded;
			ifstr.ignore(10000, '\t');
			ifstr >> m_price;
			ifstr.ignore();
			if (ifstr.bad())
			{
				m_sate = "Input file stream read failed!";
			}
		}

		m_discreiption = new char[strlen(temp) + 1];
		strcpy(m_discreiption, temp);

		return ifstr;
	}

	std::ostream &Item::display(std::ostream &ostr) const
	{
		if (!m_sate)
		{
			ostr << m_sate;
		}
		else
		{
			if (m_linear)
			{
				ostr.width(5);
				ostr << m_sku << " | ";
				for (int i = 0; i < 35; i++)
				{
					if (i < int(strlen(m_discreiption)))
						ostr << m_discreiption[i];
					else
						ostr << " ";
				}
				ostr << " | ";
				ostr.setf(ios::right);
				ostr.width(4);
				ostr.fill(' ');
				ostr << m_qty << " | ";
				ostr.unsetf(ios::right);
				ostr.setf(ios::right);
				ostr.width(4);
				ostr << m_qtyNeeded << " | ";
				ostr.unsetf(ios::right);
				ostr.setf(ios::right);
				ostr.width(7);
				ostr << fixed << setprecision(2) << m_price << " |";
			}
			else
			{
				ostr << "AMA Item:" << endl;
				ostr << m_sku << ": " << m_discreiption << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr << "Unit Price: $" << double(m_price) << endl;
				ostr << "Needed Purchase Fund: $" << fixed << setprecision(2)<< m_price * double(m_qtyNeeded - m_qty) << endl;
			}
		}
		return ostr;
	}

	std::istream &Item::read(std::istream &istr)
	{
		if (m_discreiption)
		{
			delete[] m_discreiption;
			m_discreiption = nullptr;
		}
		char desc[500];
		istr.ignore(1000, '\n');
		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;
		cout << "Description: ";
		istr.getline(desc, 1000, '\n');
		m_discreiption = new char[strlen(desc) + 1];
		strcpy(m_discreiption, desc);

		m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
		m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
		m_price = ut.getdouble(0.00, 9999.00, "Unit Price: $");
		// cout << "Entered m_price" << m_price << endl;
		if (!istr)
		{
			m_sate = "Console entry failed!";
		}

		return istr;
	}

	bool Item::operator==(int sku) const
	{
		return m_sku == sku;
	}

	bool Item::operator==(const char *description) const
	{
		string str = m_discreiption;
		if (m_discreiption && description)
		{
			if (str.find(description) != std::string::npos)
			{
				return true;
			}
		}
		return false;
	}

	void Item::clear()
	{
		m_sate.clear();
	}
}