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
//		uint16_t tmp1;
//		uint16_t tmp2;
		unsigned int temp;
		FileChunkReference32 ref;
		input->seek(0, librevenge::RVNG_SEEK_CUR);
		std::cout << "changing position to " << input->tell() << '\n';
		std::cout << "FileNode position begin " << std::hex << input->tell() << '\n';
//		input->seek(2, librevenge::RVNG_SEEK_CUR);
		temp = readU32 (input, true);
//		tmp1 = readU16(input, true);
//		tmp2 = readU16(input, true);
//		temp = tmp1 | (tmp2 << 16);
		std::bitset<32> x(temp);
		std::cout << "bitset " << x << '\n';
		std::cout << "FileNode position end " << input->tell() << '\n';
		FileNodeID = //(temp & IDMask) >> 22;
			temp >> 22;
		std::bitset<10> y(FileNodeID);

		std::cout << "filenodeid " << y << '\n';
		Size = (temp & SizeMask) >> 9;
		std::bitset<13> z(Size);
		std::cout << "Size " << z << '\n';
		ABCD = temp & ABCDMask;
		std::bitset<9> t(ABCD);
		std::cout << "ABCD " << t << '\n';
/*		switch (FileNodeID) {
			case */
		if (get_C() == 2) {
			if ((get_A() == 1) && (get_B() == 0)) {
				ref = FileChunkReference32();
				ref.parse(input);
				cout << "ref " << ref.to_string () << '\n';
				cout << "position " << input->tell() << '\n';
			}
		}
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << '\n';
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "ABCD " << std::hex << ABCD << '\n';
		stream << std::hex << "A " << std::hex << get_A() << '\n';
		stream << std::hex << "B " << std::hex << get_B() << '\n';
		stream << std::hex << "C "  << get_C() << '\n';
		stream << std::hex << "D "  << get_D() << '\n';
		return stream.str();
	}

	uint32_t FileNode::get_FileNodeID() {
		return FileNodeID;
	}

	uint32_t FileNode::get_Size() {
		return Size;
	}

	uint32_t FileNode::get_A() {
		return (ABCD & 0x180) >> 7;
	}

	uint32_t FileNode::get_B() {
		return (ABCD & 0x60) >> 5;
	}

	uint32_t FileNode::get_C() {
		return (ABCD & 6) >> 1;
	}

	uint32_t FileNode::get_D() {
		return (ABCD & 1);
	}
}


