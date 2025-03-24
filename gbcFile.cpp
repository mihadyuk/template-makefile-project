/*
 * gbcFile.cpp
 *
 *  Created on: Mar 21, 2025
 *      Author: user
 */
#include <type_traits>
#include <filesystem>
#include "gbcFile.h"

GbcFile::GbcFile() {
  // TODO Auto-generated constructor stub

}

GbcFile::~GbcFile() {
  // TODO Auto-generated destructor stub
  close();
}

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

template<typename T, size_t chunk_size = 4>
std::vector<T> readBufTillEOF(std::fstream &fs) {
  static_assert(std::is_same<T, char>::value == true || std::is_same<T, uint8_t>::value == true);
  static_assert(chunk_size > 0);

  std::vector<T> buf_chunk(chunk_size);
  std::vector<T> buf;
  while (fs.eof() == false) {
    fs.read(reinterpret_cast<char *>(buf_chunk.data()), buf_chunk.size());
    buf_chunk.resize(fs.gcount());

    size_t last_size = buf.size();
    buf.resize(buf.size() + buf_chunk.size());
    std::copy(buf_chunk.cbegin(), buf_chunk.cend(), buf.begin() + last_size);
  }
  return buf;
}

int GbcFile::open(const std::string &fullPath) {

  if (isOpened())
    return -1;

  fs_.open(fullPath, std::ios_base::binary | std::ios_base::in | std::ios_base::app);
  if (fs_.is_open() == false) {
    return -1;
  }
  fullPath_ = fullPath;
  return 0;
}

void GbcFile::close() {
  fs_.close();
  fullPath_ = "";
}

GbcData GbcFile::readData() {

  if (isOpened() == false)
    return GbcData();

  std::array<char, GbcHeader::size()> buffer;

  fs_.clear();
  fs_.seekg(0);
  fs_.read(buffer.data(), buffer.size());
  if (fs_.gcount() != buffer.size())
    return GbcData();

  //parse given header
  std::string magic(buffer.data(), std::char_traits<char>::length(GbcHeader::magic));
  if (magic != GbcHeader::magic)
    return GbcData();

  GbcHeader header;
  std::copy(buffer.begin() + 3,
            buffer.begin() + 3 + sizeof(header.secCount_),
            reinterpret_cast<uint8_t*>(&header.secCount_));

  std::copy(buffer.begin() + 3 + sizeof(header.secCount_),
            buffer.begin() + 3 + sizeof(header.secCount_) + header.offsets_.size() * sizeof(uint32_t),
            reinterpret_cast<uint8_t *>(header.offsets_.data()));

  // parse data
  if (header.secCount_ == 0)
    return GbcData();

  GbcData data;
  fs_.read(reinterpret_cast<char *>(&data.timestamp_), sizeof(data.timestamp_));

  if (header.secCount_ > 2) {
    std::vector<char> ascii_buf(header.offsets_[2] - header.offsets_[1]);
    fs_.read(ascii_buf.data(), ascii_buf.size());
    data.asciiSyms_ = std::move(ascii_buf);

  }
  else if (header.secCount_ == 2) {
    data.asciiSyms_ = readBufTillEOF<char>(fs_);
  }


  if (header.secCount_ > 3) {
      std::vector<uint8_t> blob_buf(header.offsets_[3] - header.offsets_[2]);
      fs_.read(reinterpret_cast<char *>(blob_buf.data()), blob_buf.size());
      data.blob_ = std::move(blob_buf);
  }
  else if (header.secCount_ == 3) {
    data.blob_ = readBufTillEOF<uint8_t>(fs_);
  }

  if (header.secCount_ == 4) {
    uint32_t checksum = 0;
    fs_.read(reinterpret_cast<char *>(&checksum), sizeof(checksum));
    if (fs_.gcount() != sizeof(checksum))
      return GbcData();
    data.checksum_ = checksum;
  }

  return data;
}

int GbcFile::writeData(const GbcData &data) {
  if (isOpened() == false)
    return -1;

  // remove file content
  std::ofstream owerwrite_file(fullPath_, std::ios::out | std::ios::trunc);
  owerwrite_file.close();

  fs_.clear();
  fs_.seekg(0);
  fs_.write(GbcHeader::magic, std::char_traits<char>::length(GbcHeader::magic));

  GbcHeader header;
  if (data.timestamp_) {
    header.secCount_++;
    header.offsets_[0] = GbcHeader::size();
  }
  if (data.asciiSyms_.size()) {
    header.secCount_++;
    header.offsets_[1] = header.offsets_[0] + sizeof(data.timestamp_);
  }
  if (data.blob_.size()) {
    header.secCount_++;
    header.offsets_[2] = header.offsets_[1] + data.asciiSyms_.size();
  }
  if (data.checksum_) {
    header.secCount_++;
    header.offsets_[3] = header.offsets_[2] + data.blob_.size();
  }

  fs_.write(reinterpret_cast<const char *>(&header.secCount_), sizeof(header.secCount_));
  fs_.write(reinterpret_cast<const char *>(header.offsets_.data()), header.offsets_.size() * sizeof(uint32_t));

  if (data.timestamp_)
    fs_.write(reinterpret_cast<const char *>(&data.timestamp_), sizeof(data.timestamp_));
  else
    return 0;

  if (data.asciiSyms_.size())
    fs_.write(reinterpret_cast<const char *>(data.asciiSyms_.data()), data.asciiSyms_.size());
  else
    return 0;

  if (data.blob_.size())
    fs_.write(reinterpret_cast<const char *>(data.blob_.data()), data.blob_.size());
  else
    return 0;

  if (data.checksum_)
    fs_.write(reinterpret_cast<const char *>(&data.checksum_), sizeof(data.checksum_));

  return 0;
}


