#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

using std::string;

namespace libone {

	void GUID::parse(librevenge::RVNGInputStream *input) {

		  Data1 = readU32 (input, false);
		  Data2 = readU16 (input, false);
		  Data3 = readU16 (input, false);
		  for (int i=0; i<4; i++)
		    Data4[i] = readU16 (input, true);

	}

	string GUID::to_string() {
		std::stringstream stream;
		stream << "{" << std::hex << Data1 << "-" << Data2 << "-" << Data3 << "-" << Data4[0] << "-";

		for (int i=1; i<4; i++)
			stream << std::hex << Data4[i];

		stream << "}";



		return stream.str();
	}

}
