
#include <cppunit/extensions/HelperMacros.h>

#include <cppunit/TestAssert.h>

#include <tuple>

#include "GUIDTest.h"
#include "../../lib/GUID.h"


#include <librevenge-stream/librevenge-stream.h>
#include <librevenge/librevenge.h>

CppUnit::Test *GUIDTest::suite()
{
  CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("GUIDTest");

  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID constructor", &GUIDTest::test_constructor));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID to_string", &GUIDTest::test_to_string));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID from_string", &GUIDTest::test_from_string));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID is_equal", &GUIDTest::test_is_equal));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID parse", &GUIDTest::test_parse));

  return testSuite;
}



void GUIDTest::setUp()
{
}

void GUIDTest::tearDown()
{}

void GUIDTest::test_constructor()
{
  libone::GUID guid {};

  CPPUNIT_NS::assertEquals<uint32_t>(guid.data1(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 0");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data2(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 1");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data3(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 2");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data4().at(0), 0, CPPUNIT_SOURCELINE(), "constructor 1, 3");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data4().at(1), 0, CPPUNIT_SOURCELINE(), "constructor 1, 4");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data4().at(2), 0, CPPUNIT_SOURCELINE(), "constructor 1, 5");
  CPPUNIT_NS::assertEquals<uint16_t>(guid.data4().at(3), 0, CPPUNIT_SOURCELINE(), "constructor 1, 6");


  libone::GUID guid2(1,2,3,4,5,6,7);

  CPPUNIT_NS::assertEquals<uint32_t>(guid2.data1(), 1, CPPUNIT_SOURCELINE(), "constructor 2, 0");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data2(), 2, CPPUNIT_SOURCELINE(), "constructor 2, 1");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data3(), 3, CPPUNIT_SOURCELINE(), "constructor 2, 2");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data4().at(0), 4, CPPUNIT_SOURCELINE(), "constructor 2, 3");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data4().at(1), 5, CPPUNIT_SOURCELINE(), "constructor 2, 4");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data4().at(2), 6, CPPUNIT_SOURCELINE(), "constructor 2, 5");
  CPPUNIT_NS::assertEquals<uint16_t>(guid2.data4().at(3), 7, CPPUNIT_SOURCELINE(), "constructor 2, 6");


}

void GUIDTest::test_from_string()
{
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> > cases {};

  cases.emplace_back("{00000000-0000-0000-0000-000000000000}", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("00000000-0000-0000-0000-000000000000", 0, 0, 0, 0, 0, 0,0);
  cases.emplace_back("00000000000000000000000000000000", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3}", 0X7b5c52e4, 0Xd88c, 0X4da7, 0Xaeb1, 0X5378, 0Xd029, 0X96d3);
  cases.emplace_back("FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  // failing parsing
  cases.emplace_back("FF", 0, 0, 0, 0, 0, 0, 0);




  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::GUID guid(std::get<0>(entry));

    CPPUNIT_NS::assertEquals(std::get<1>(entry), guid.data1(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data1");
    CPPUNIT_NS::assertEquals(std::get<2>(entry), guid.data2(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data2");
    CPPUNIT_NS::assertEquals(std::get<3>(entry), guid.data3(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data3");
    CPPUNIT_NS::assertEquals(std::get<4>(entry), guid.data4().at(0), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[0]");
    CPPUNIT_NS::assertEquals(std::get<5>(entry), guid.data4().at(1), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[1]");
    CPPUNIT_NS::assertEquals(std::get<6>(entry), guid.data4().at(2), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[2]");
    CPPUNIT_NS::assertEquals(std::get<7>(entry), guid.data4().at(3), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[3]");
  }
}

void GUIDTest::test_to_string()
{
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> > cases {};

  cases.emplace_back("{00000000-0000-0000-0000-000000000000}", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("{ffffffff-ffff-ffff-ffff-ffffffffffff}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}", 0x7b5c52e4, 0xd88c, 0x4da7, 0xaeb1, 0x5378, 0xd029, 0x96d3);


  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::GUID guid(
      std::get<1>(entry),
      std::get<2>(entry),
      std::get<3>(entry),
      std::get<4>(entry),
      std::get<5>(entry),
      std::get<6>(entry),
      std::get<7>(entry));

    CPPUNIT_NS::assertEquals(std::get<0>(entry), guid.to_string(), CPPUNIT_SOURCELINE(), "test case#" + std::to_string(i));
  }


}

void GUIDTest::test_is_equal()
{

  libone::GUID guid1{};

  libone::GUID guid2(0,0,0,0,0,0,0);



  CPPUNIT_NS::Asserter::failIf(guid1 != guid2, "compare zerod guids", CPPUNIT_SOURCELINE());


  libone::GUID guid3(1,2,3,4,5,6,7);
  libone::GUID guid4(1,2,3, {{4,5,6,7}});

  CPPUNIT_NS::Asserter::failIf(guid1 != guid2, "compare zerod guids 2", CPPUNIT_SOURCELINE());


}



void GUIDTest::test_parse()
{
  std::vector< std::tuple< std::string, std::array<unsigned char,16> > > cases {};




  cases.emplace_back("{00000000-0000-0000-0000-000000000000}", std::array<unsigned char, 16> {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
  cases.emplace_back("{ffffffff-ffff-ffff-ffff-ffffffffffff}", std::array<unsigned char, 16> {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF});
  cases.emplace_back("{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}", std::array<unsigned char, 16> {0xe4, 0x52, 0x5c, 0x7b, 0x8c, 0xd8, 0xa7, 0x4d, 0xae, 0xb1, 0x53, 0x78, 0xd0, 0x29, 0x96, 0xd3});


  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);

    librevenge::RVNGBinaryData bindata = librevenge::RVNGBinaryData(std::get<1>(entry).data(), std::get<1>(entry).size());
    libone::RVNGInputStreamPtr_t input(bindata.getDataStream());

    libone::GUID guid;
    input >> guid;

    CPPUNIT_NS::assertEquals(std::get<0>(entry), guid.to_string(), CPPUNIT_SOURCELINE(), "compare parsed guid #" + std::to_string(i));

  }

}
