/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_FILENODECHUNKREFERENCE_H
#define INCLUDED_LIBONE_FILENODECHUNKREFERENCE_H

#include <librevenge-stream/librevenge-stream.h>

namespace libone {

  enum stp_format {
		stp_uncompressed_8 = 0,
		stp_uncompressed_4 = 1,
		stp_compressed_2 = 2,
    stp_compressed_4 = 3,
		stp_invalid
	};

  enum cb_format {
    cb_uncompressed_4 = 0,
    cb_uncompressed_8 = 1,
    cb_compressed_1 = 2,
    cb_compressed_2 = 3,
    cb_invalid
  };

class FileNodeChunkReference {
  public:
    FileNodeChunkReference(enum stp_format format_stp, enum cb_format format_cb, long offset);
    bool is_fcrNil();
    bool is_fcrZero();
    uint64_t get_location();
    uint64_t get_size();
    uint32_t get_size_in_file();
    void parse(librevenge::RVNGInputStream *input);
    void set_zero();
    enum stp_format get_stp_fmt() { return m_format_stp; }
    enum cb_format get_cb_fmt() { return m_format_cb; }

  private:
    uint64_t m_offset;
    uint64_t m_stp;
    uint64_t m_cb;
    enum stp_format m_format_stp;
    enum cb_format m_format_cb;
};

}

#endif
