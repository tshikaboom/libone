#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

using std::string;

namespace libone {

	void FileChunkReference64x32::parse(librevenge::RVNGInputStream *input) {
		stp = readU64(input, false);
		cb = readU32(input, false);
	}
	uint64_t FileChunkReference64x32::get_location() {
		return stp;
	}
	uint32_t FileChunkReference64x32::get_size() {
		return cb;
	}

	string FileChunkReference64x32::to_string() {
		std::stringstream stream;
		stream << "stp64 " << stp << " cb32 " << cb;
		return stream.str();
	}

}
