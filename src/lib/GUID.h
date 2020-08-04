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

/** @brief globally unique identifier class specified by [RFC4122] or [C706] */
class GUID
{
public:
  /** Default construtor. Initializes to {00000000-0000-0000-0000-000000000000}. */
  GUID();

  /** Constructor to initialize specific GUID */
  GUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
       const std::array<uint16_t,4> data4);

  /** Constructor to initialize specific GUID */
  GUID(const uint32_t data1, const uint16_t data2, const uint16_t data3,
       const uint16_t data4_1, const uint16_t data4_2,
       const uint16_t data4_3, const uint16_t data4_4);

  /** Parse GUID's content from RVNGInputStream byte stream. */
  void parse(librevenge::RVNGInputStream *input);

  /** Converts GUID object to a string in this format: "{00000000-0000-0000-0000-000000000000}" */
  std::string to_string() const;

  /** Parse GUID object from string.
   * @param str - should have the format "{00000000-0000-0000-0000-000000000000}" */
  void from_string(const std::string str);

  /** Checks if GUIDs are identical */
  bool is_equal(const GUID other) const;


  /** resets GUID to {00000000-0000-0000-0000-000000000000} */
  void zero();

  friend librevenge::RVNGInputStream *operator>>(librevenge::RVNGInputStream *input, GUID &obj);

  friend bool operator==(const GUID &lhs, const GUID &rhs) noexcept;
  friend bool operator!=(const GUID &lhs, const GUID &rhs) noexcept;


  /** Getter.
   * @return first data sequence GUID */
  uint32_t data1() const;
  /** Getter.
   * @return second data sequence of GUID */
  uint16_t data2() const;
  /** Getter.
   * @return third data sequence of GUID */
  uint16_t data3() const;
  /** Getter.
   * @return forth data sequence of GUID */
  std::array<uint16_t,4> data4() const;

private:
  uint32_t Data1 = 0;
  uint16_t Data2 = 0;
  uint16_t Data3 = 0;
  std::array<uint16_t, 4> Data4 {{ 0, 0, 0, 0 }};
};

}

#endif
