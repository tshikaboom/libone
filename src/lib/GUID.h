/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libone project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBONE_GUID_H
#define INCLUDED_LIBONE_GUID_H

#include <string>
#include <cstdint>
#include <array>
#include <librevenge-stream/librevenge-stream.h>

namespace libone
{

class GUID
{
public:
  GUID();
  GUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
       const std::array<uint16_t,4> data4);
  GUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
       const uint16_t data4_1, const uint16_t data4_2,
       const uint16_t data4_3, const uint16_t data4_4);

  void parse(librevenge::RVNGInputStream *input);

  std::string to_string() const;
  void from_string(const std::string str);

  bool is_equal(const GUID other) const;


  void zero();

  friend librevenge::RVNGInputStream *operator>>(librevenge::RVNGInputStream *input, GUID &obj);

  friend bool operator==(const GUID &lhs, const GUID &rhs) noexcept;
  friend bool operator!=(const GUID &lhs, const GUID &rhs) noexcept;


  uint32_t data1() const;
  uint16_t data2() const;
  uint16_t data3() const;
  std::array<uint16_t,4> data4() const;

private:
  uint32_t Data1 = 0;
  uint16_t Data2 = 0;
  uint16_t Data3 = 0;
  std::array<uint16_t, 4> Data4 {{ 0, 0, 0, 0 }};
};

}

#endif
