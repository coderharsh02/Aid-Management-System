//####################################
// Project: Aid Management System  ###
//####################################

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"
using namespace std;

namespace sdds {
	class Item : public iProduct {
	private:
		double m_price = 0.0;
		char* m_discreiption = nullptr;
		bool m_linear = false;
		int m_qty = 0;
		int m_qtyNeeded = 0;
	protected:
		int m_sku = 0;
		Status m_sate;
		bool linear() const;
	public:
		Item() = default;
		Item(const Item& item);
		Item& operator=( const Item& item);
		virtual ~Item();
		// main data entry
		int readSku(std::istream& istr);
		virtual int operator-=(int qty);
		// to increase the quantity on hand
		virtual int operator+=(int qty);
		// returns the price of the produce
		virtual operator double()const;
		// returns if the iProduct is in a good state
		virtual operator bool()const;
		// returns the number of products needed
		virtual int qtyNeeded()const;
		// retuns the quantity on hand
		virtual int qty()const;
		// determines if the iProduct is displayed in a linear format or 
		// descriptive format
		void linear(bool isLinear);
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		// loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr);
		// displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const;
		// reads the iProduct from the console
		virtual std::istream& read(std::istream& istr);
		// return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const;
		// rtrns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const;

		void clear();

	};
	
}

#endif