//####################################
// Project: Aid Management System  ###
//####################################

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include <iostream>
#include "Menu.h"
#include "iProduct.h"
namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
	private:
		char *m_filename{nullptr};
		Menu m_menu;
		iProduct *iProductPtrs[sdds_max_num_items] = {nullptr};
		int iProdNum{0};
		unsigned int menu();

	public:
		AidMan();
		void run();
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void remove(int index);
		void sort();
		~AidMan();
	};
}
#endif // !SDDS_AIDMAN_H
