/*
 * gbcFile.cpp
 *
 *  Created on: Mar 21, 2025
 *      Author: user
 */
#include <fstream>
#include "gbcFile.h"

GbcFile::GbcFile() {
  // TODO Auto-generated constructor stub

}

GbcFile::~GbcFile() {
  // TODO Auto-generated destructor stub
}

int GbcFile::open(const std::string &fullPath) {

  if (isOpened())
    return -1;
  std::fstream fs(fullPath, std::ios_base::binary | std::ios_base::in | std::ios_base::out);
  if (fs.is_open() == false)
    return -1;

  std::array<char, GbcHeader::size()> buffer;
  fs.read(buffer.data(), buffer.size());
  if (fs.gcount() != buffer.size())
    return -1;

  //parse given header
  std::string magic(buffer.data(), std::char_traits<char>::length(GbcHeader::magic));
  if (magic != GbcHeader::magic)
    return -1;

  GbcHeader header;
  std::copy(buffer.begin() + 3,
            buffer.begin() + 3 + sizeof(header.secCount_),
            reinterpret_cast<uint8_t*>(&header.secCount_));

  std::copy(buffer.begin() + 3 + sizeof(header.secCount_),
            buffer.begin() + 3 + sizeof(header.secCount_) + header.offsets_.size() * sizeof(uint32_t),
            reinterpret_cast<uint8_t *>(header.offsets_.data()));

  // parse data
  if (header.secCount_ == 0)
    return 0;

  fs.read(reinterpret_cast<char *>(&data_.timestamp_), sizeof(data_.timestamp_));
  if (header.secCount_ <= 2)
    fs.read(reinterpret_cast<char *>(&data_.timestamp_), sizeof(data_.timestamp_));






  //header.secCount_  = buffer[4];
  //header.secCount_ |= static_cast<uint32_t>(buffer[5]) << 8;
  //header.secCount_ |= static_cast<uint32_t>(buffer[6]) << 16;
  //header.secCount_ |= static_cast<uint32_t>(buffer[7]) << 24;

  //size_t buf_index = 7;
  //for (size_t i = 0; i < header.offsets_.size(); i++) {
  //  header.offsets_[i] = buffer[buf_index++];
  // header.offsets_[i] |= static_cast<uint32_t>(buffer[buf_index++]) << 8;
  //  header.offsets_[i] |= static_cast<uint32_t>(buffer[buf_index++]) << 16;
  //  header.offsets_[i] |= static_cast<uint32_t>(buffer[buf_index++]) << 24;
  //}


  return 0;
}

void GbcFile::close() {
  isOpened_ = false;
  data_ = GbcData();
}

GbcData GbcFile::readData() {
  return data_;
}

int GbcFile::writeData(const GbcData &data) {
  return -1;
}


