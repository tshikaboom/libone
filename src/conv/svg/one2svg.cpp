/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include <librevenge/librevenge.h>
#include <librevenge-generators/librevenge-generators.h>
#include <librevenge-stream/librevenge-stream.h>

#include <libone/libone.h>

namespace
{

int printUsage()
{
	printf("Usage: one2svg [OPTION] <Document>\n");
	printf("\n");
	printf("Options:\n");
	printf("--help                Shows this help message\n");
	return -1;
}

} // anonymous namespace

using libone::ONEDocument;

int main(int argc, char *argv[])
{
	if (argc < 2)
		return printUsage();

	char *file = 0;

	for (int i = 1; i < argc; i++)
	{
		if (!file && strncmp(argv[i], "--", 2))
			file = argv[i];
		else
			return printUsage();
	}

	if (!file)
		return printUsage();

	librevenge::RVNGFileStream input(file);

	if (!ONEDocument::isSupported(&input))
	{
		std::cerr << "ERROR: Unsupported file format (unsupported version) or file is encrypted!" << std::endl;
		return 1;
	}

	librevenge::RVNGStringVector vec;
	librevenge::RVNGSVGDrawingGenerator generator(vec, "");
	bool result = ONEDocument::parse(&input, &generator);
	if (!result || vec.empty() || vec[0].empty())
	{
		std::cerr << "ERROR: SVG Generation failed!" << std::endl;
		return 1;
	}

#if 1
	std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
	std::cout << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"";
	std::cout << " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
#endif
	std::cout << vec[0].cstr() << std::endl;
	return 0;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
