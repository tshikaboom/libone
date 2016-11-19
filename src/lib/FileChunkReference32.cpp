#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

using std::string;

namespace libone {

	void FileChunkReference32::parse(librevenge::RVNGInputStream *input) {
		stp = readU32(input, false);
		cb = readU32(input, false);
	}
	uint32_t FileChunkReference32::get_location() {
		return stp;
	}
	uint32_t FileChunkReference32::get_size() {
		return cb;
	}

	string FileChunkReference32::to_string() {
		std::stringstream stream;
		stream << "stp32 " << std::hex << stp << " cb32 " << cb;
		return stream.str();
	}

}
