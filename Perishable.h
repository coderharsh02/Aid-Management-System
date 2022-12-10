//####################################
// Project: Aid Management System  ###
//####################################

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include <iostream>
#include "Date.h"
#include "Item.h"
namespace sdds {
	class Perishable : public Item{
	private:
		char* instructions = nullptr;
	protected:
		Date m_expDate;
	public:
		Perishable() = default;
		Perishable(const Perishable& perishable);
		Perishable& operator=(const Perishable & perishable);
		~Perishable();
		const Date& expiry() const;
		virtual int readSku(std::istream & istr);
		virtual std::ofstream& save(std::ofstream & ofstr)const;
		virtual std::ifstream& load(std::ifstream & ifstr);
		virtual std::ostream& display(std::ostream & ostr)const;
		virtual std::istream& read(std::istream & istr);

	
	};
}
#endif // !SDDS_PERISHABLE_H