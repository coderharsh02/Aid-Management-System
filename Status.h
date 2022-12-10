//####################################
// Project: Aid Management System  ###
//####################################

#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
using namespace std;
namespace sdds {
	class Status {
	private:
		char* description = nullptr;
		int n_code = 0;
	public:
		Status(const char* desc = nullptr);
		~Status();
		Status& operator=(const char* desc);
		Status& operator=(int code);
		operator int() const;
		operator bool() const;
		operator const char* () const;
		Status& clear();
		
	};
	ostream& operator<<(ostream& ostr , const Status& newstatus);
}
#endif // !SDDS_STATUS_H
