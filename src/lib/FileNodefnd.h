/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODEDESCRIPTOR_H
#define INCLUDED_LIBONE_FILENODEDESCRIPTOR_H

#include "libone_utils.h"




namespace libone {

class FileNodeDescriptor {
  public:
    virtual void parse(librevenge::RVNGInputStream *input);
    virtual string to_string();

};

class ObjectSpaceManifestRootFND : FileNodeDescriptor {
  public:
    void parse(librevenge::RVNGInputStream *input);
    string to_string();

  private:
    char gosidRoot[20];
};

class RevisionManifestListReferenceFND : FileNodeDescriptor {
  public:
    void parse(librevenge::RVNGInputStream *input);
    string to_string();

  private:



}

#endif
