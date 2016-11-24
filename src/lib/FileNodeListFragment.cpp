#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeListFragment.h"
#include "libone_utils.h"
using namespace std;
using std::string;

namespace libone {

	void FileNodeListFragment::parse(librevenge::RVNGInputStream *input) {
		FileNode node, node2;
		std::cout << "fragment position begin " << input->tell() << '\n';
		uintMagic = readU64 (input, false);
		FileNodeListID = readU32 (input, false);
		nFragmentSequence = readU32 (input, false);
		std::cout << "fragment position end " << input->tell() << '\n';
		node.parse(input);
		rgFileNodes.push_back(node);

//		node2.parse(input);
//		rgFileNodes.push_back(node2);
		nextFragment = 0;
		footer = 0;
	}

	string FileNodeListFragment::to_string() {
		std::stringstream stream;
		stream << std::hex << "uintMagic " << uintMagic << '\n';
		stream << std::dec << "FileNodeListID " << FileNodeListID << '\n';
		stream << "nFragmentSequence " << nFragmentSequence << '\n';
		for (FileNode i: rgFileNodes)
		stream << i.to_string() << '\n';
		return stream.str();
	}
}


