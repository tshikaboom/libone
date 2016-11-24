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
		FileChunkReference32 ref32;

		temp = readU32 (input, false);
		d = temp >> 31;
		c = (temp >> 27) & 0xF;
		b = (temp >> 25) & 0x3;
		a = (temp >> 23) & 0x3;
		Size = (temp >> 10) & 0x1FFF;
		FileNodeID = temp & 0x3FF;
		std::bitset<10> y(FileNodeID);

		std::cout << "filenodeid " << FileNodeID << " " << y << '\n';
		Size = (temp & SizeMask) >> 9;
		std::bitset<13> z(Size);
		std::cout << "Size " << Size << " " << z << '\n';
		std::cout << "A " << a << " B " << b << " C " << c << " D " << d << '\n';
/*		switch (FileNodeID) {
			case */
		if (get_C() == 2) {
			if ((get_A() == 1) && (get_B() == 0)) {
				ref = FileChunkReference32();
				ref.parse(input);
				cout << "ref " << ref.to_string () << '\n';
				cout << "position " << input->tell() << '\n';
			}
			if ((get_A() == 3) && (get_B() == 0)) {
				ref32 = FileChunkReference32();
				ref32.parse(input);
				cout << "ref " << ref32.to_string () << '\n';
				ref32.location8();
				cout << "ref " << ref32.to_string () << '\n';
			}
			if ((get_A() == 2) && (get_B() == 2)) {
				ref = FileChunkReference32();
				uint32_t l, s;
				l = readU16 (input, false) * 8;
				s = readU8(input, false) * 8;
				ref.set_all(l, s);
				cout << "ref " << ref.to_string() << '\n';
			}
		}
	}

	string FileNode::to_string() {
		std::stringstream stream;
		stream << "FileNodeID " << std::hex << FileNodeID << '\n';
		stream << std::hex << "Size " << Size << '\n';
		stream << std::hex << "A " << a << " B " << b << " C " << c << " D " << d << '\n';


		return stream.str();
	}

	uint32_t FileNode::get_FileNodeID() {
		return FileNodeID;
	}

	uint32_t FileNode::get_Size() {
		return Size;
	}

	uint32_t FileNode::get_A() {
		return a;
	}

	uint32_t FileNode::get_B() {
		return b;
	}

	uint32_t FileNode::get_C() {
		return c;
	}

	uint32_t FileNode::get_D() {
		return d;
	}
}


