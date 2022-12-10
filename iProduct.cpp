//####################################
// Project: Aid Management System  ###
//####################################

#include "iProduct.h"
namespace sdds
{
	std::ostream &operator<<(std::ostream &ostr, const iProduct &product)
	{
		product.display(ostr);
		return ostr;
	}

	std::istream &operator>>(std::istream &istr, iProduct &product)
	{
		product.read(istr);
		return istr;
	}
}
