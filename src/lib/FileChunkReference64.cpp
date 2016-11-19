#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

using std::string;

namespace libone {

	void FileChunkReference64::parse(librevenge::RVNGInputStream *input) {
		stp = readU64(input, false);
		cb = readU64(input, false);
	}
	uint64_t FileChunkReference64::get_location() {
		return stp;
	}
	uint64_t FileChunkReference64::get_size() {
		return cb;
	}

	string FileChunkReference64::to_string() {
		std::stringstream stream;
		stream << "stp64 " << std::hex << stp << " cb64 " << cb;
		return stream.str();
	}

}
