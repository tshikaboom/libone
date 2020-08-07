#ifndef GUIDTEST_H
#define GUIDTEST_H

#include <cppunit/TestCase.h>

class GUIDTest : public CppUnit::TestCase
{
public:
  static CppUnit::Test *suite();

  void setUp();
  void tearDown();

  void test_constructor();
  void test_to_string();
  void test_from_string();
  void test_is_equal();

  void test_parse();

};

#endif // GUIDTEST_H
