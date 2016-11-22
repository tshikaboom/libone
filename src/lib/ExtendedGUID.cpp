#include <cstddef>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>
#include "ExtendedGUID.h"
#include "libone_utils.h"

using std::string;

namespace libone {

	void ExtendedGUID::parse(librevenge::RVNGInputStream *input) {
		guid.parse(input);

		n = readU32(input, false);
	}

	string ExtendedGUID::to_string() {
		std::stringstream stream;
		stream << guid.to_string() << "} n=" << n;



		return stream.str();
	}

}
