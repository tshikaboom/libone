/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstring>
#include <iostream>
#include <iomanip>
#include <libone/libone.h>


#include "FileNodeListFragment.h"
#include "libone_utils.h"
using namespace std;
using std::string;

namespace libone {

	void FileNodeListFragment::parse(librevenge::RVNGInputStream *input, uint32_t ExpectedFileNodeID) {
		FileNode node;
		std::cout << "fragment position begin " << input->tell() << '\n';
		uintMagic = readU64 (input, false);
		FileNodeListID = readU32 (input, false);
		nFragmentSequence = readU32 (input, false);
		std::cout << "fragment position end " << input->tell() << '\n';
		node.parse(input);
		if (ExpectedFileNodeID && ExpectedFileNodeID != node.get_FileNodeID()) {
			cout << "Expected FileNodeID " << ExpectedFileNodeID << " got " << node.get_FileNodeID();
			return;
		}
		int i=0;
		while (!node.isEnd()) {
			rgFileNodes.push_back(node);
			i++;
			if ((i<=2) && (FileNodeListID == 0x10))
				node.try_parse_ref(input, ExpectedFileNodeID);
			node.parse(input);
		}
		if (node.get_FileNodeID() == FileNodeDescriptor::ChunkTerminatorFND) {
			FileChunkReference64x32 nextFragment_chunk;
			nextFragment_chunk.parse(input);
		}

		footer = readU64(input);
		cout << footer << "\n";
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


