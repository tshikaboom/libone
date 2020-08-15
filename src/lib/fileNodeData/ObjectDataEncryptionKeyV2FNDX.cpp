#include "ObjectDataEncryptionKeyV2FNDX.h"



namespace libone
{
ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(
  StpFormat stpFormat, CbFormat cbFormat)
  : m_ref(stpFormat, cbFormat), m_EncryptionData() {}

// ObjectDataEncryptionKeyV2FNDX::ObjectDataEncryptionKeyV2FNDX(const ObjectDataEncryptionKeyV2FNDX &source)
//   : m_ref(source.m_ref),
// {
//   std::copy(source.getEncryptionData(), source.getEncryptionData() + source.getEncryptionDataLength(), m_EncryptionData);
// }

ObjectDataEncryptionKeyV2FNDX::~ObjectDataEncryptionKeyV2FNDX()
{
}

// ObjectDataEncryptionKeyV2FNDX &ObjectDataEncryptionKeyV2FNDX::operator=(const ObjectDataEncryptionKeyV2FNDX &rhs)
// {
//   if (this == &rhs)
//   {
//     return *this;
//   }
//
//   delete[] this->m_EncryptionData;
//   m_EncryptionData = new unsigned char[rhs.m_ref.cb()];
//   std::copy(rhs.m_EncryptionData, rhs.m_EncryptionData + rhs.m_ref.cb(), m_EncryptionData);
//   return *this;
// }

unsigned char *ObjectDataEncryptionKeyV2FNDX::getEncryptionData() const
{
  return m_EncryptionData.get();
}

void ObjectDataEncryptionKeyV2FNDX::setEncryptionData(const unsigned char *value, const uint64_t length)
{
  if (0 < length)
  {
    m_EncryptionData.reset(new unsigned char[length]);
    std::copy(value, value + length, m_EncryptionData.get());
  }
}

FileNodeChunkReference ObjectDataEncryptionKeyV2FNDX::getRef() const
{
  return m_ref;
}

void ObjectDataEncryptionKeyV2FNDX::setRef(
  const FileNodeChunkReference &value)
{
  m_ref = value;
}

void ObjectDataEncryptionKeyV2FNDX::parse(const libone::RVNGInputStreamPtr_t &input)
{
  input >> m_ref;

  uint64_t currentloc = input->tell();

  seek(input,m_ref.stp());
  // skip header
  skip(input,8);

  const unsigned char *const temp = readNBytes(input, m_ref.cb());
  m_EncryptionData.reset(new unsigned char[m_ref.cb()]);
  std::copy(temp, temp + m_ref.cb(), m_EncryptionData.get());
  delete temp;

  // skip footer
  skip(input,8);

  seek(input, currentloc);
}

std::string ObjectDataEncryptionKeyV2FNDX::to_string() const
{
  return "";
}

} // namespace libone
