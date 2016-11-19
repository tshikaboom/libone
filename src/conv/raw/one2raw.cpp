/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>
#include <string.h>

#include <boost/shared_ptr.hpp>

#include <librevenge/librevenge.h>
#include <librevenge-generators/librevenge-generators.h>
#include <librevenge-stream/librevenge-stream.h>

#include <libone/libone.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef VERSION
#define VERSION "UNKNOWN VERSION"
#endif

namespace
{

int printUsage()
{
  printf("Usage: one2raw [OPTION] <Document>\n");
  printf("\n");
  printf("Options:\n");
  printf("--callgraph           Display the call graph nesting level\n");
  printf("--help                Shows this help message\n");
  printf("--version             Output one2raw version \n");
  return -1;
}

int printVersion()
{
  printf("one2raw %s\n", VERSION);
  return 0;
}

} // anonymous namespace

using libone::ONEDocument;

int main(int argc, char *argv[])
{
  bool printIndentLevel = false;
  char *file = 0;
  const char *p = 0;

  if (argc < 2)
    return printUsage();

  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "--callgraph"))
      printIndentLevel = true;
    else if (!strcmp(argv[i], "--version"))
      return printVersion();
    else if (!file && strncmp(argv[i], "--", 2))
      file = argv[i];
    else
      return printUsage();
  }

  if (!file)
    return printUsage();

  std::shared_ptr<librevenge::RVNGInputStream> input(new librevenge::RVNGFileStream(file));

  ONEDocument::Type type = ONEDocument::TYPE_ONE2016;
  //ONEDocument::Confidence confidence = ONEDocument::isSupported(input.get(), &type);

  librevenge::RVNGRawDrawingGenerator documentGenerator(printIndentLevel);

  return (ONEDocument::RESULT_OK == ONEDocument::parse(input.get(), &documentGenerator, type, p)) ? 0 : 1;
}

/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
