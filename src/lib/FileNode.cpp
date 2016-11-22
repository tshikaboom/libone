#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>

#include "libone_utils.h"

#include <bitset>
using namespace std;
using std::string;

namespace libone {

	void FileNode::parse(librevenge::RVNGInputStream *input) {
		uint32_t temp;
		std::cout << "position " << std::hex << input->tell() << '\n';
		temp = readU32 (input, true);
		std::bitset<32> x(temp);
		std::cout << x << " position " << input->tell() << '\n';
		FileNodeID = (temp & IDMask) >> 22;
		std::bitset<10> y(FileNodeID);

		std::cout << "filenodeid " << y << '\n';
		Size = (temp & SizeMask) >> 9;
		std::bitset<13> z(Size);
		std::cout << "Size " << z << '\n';
		ABCD = temp & ABCDMask;

		if (get_C() == 2) {
			if ((get_A() == 1) && (get_B() == 0)) {
				FileChunkReference32 ref = FileChunkReference32();
				ref.parse(input);
				cout << "ref " << ref.to_string () << '\n';
			}
		}
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << FileNodeID << '\n';
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "ABCD " << std::hex << ABCD << '\n';
		stream << std::hex << "A " << std::hex << get_A() << '\n';
		stream << std::hex << "B " << std::hex << get_B() << '\n';
		stream << std::hex << "C "  << get_C() << '\n';
		stream << std::hex << "D "  << get_D() << '\n';
		return stream.str();
	}

	uint16_t FileNode::get_FileNodeID() {
		return FileNodeID;
	}

	uint16_t FileNode::get_Size() {
		return Size;
	}

	uint16_t FileNode::get_A() {
		return (ABCD & 0x180) >> 7;
	}

	uint16_t FileNode::get_B() {
		return (ABCD & 0x60) >> 5;
	}

	uint16_t FileNode::get_C() {
		return (ABCD & 6) >> 1;
	}

	uint16_t FileNode::get_D() {
		return (ABCD & 1);
	}
}


