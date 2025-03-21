/*
 * gbcFile.h
 *
 *  Created on: Mar 21, 2025
 *      Author: user
 */

#ifndef GBCFILE_H_
#define GBCFILE_H_
#include <stdint.h>
#include <stddef.h>
#include <array>
#include <string>
#include <vector>

struct GbcHeader {
  static constexpr const char *magic = "gbc";
  size_t secCount_    = 0;
  std::array<uint32_t, 4> offsets_;
};

struct GbcData {
  uint64_t timestamp_ = 0;
  std::string asciiSyms_;
  std::vector<uint8_t> blob_;
  uint32_t crcChecksum_ = 0;
};

class IGbc {
public:
  virtual GbcData readData() = 0;
  virtual int writeData(const GbcData &data) = 0;
};

class GbcFile : public IGbc {
public:
  GbcFile();
  virtual ~GbcFile();

  int open(const std::string &fullPath);
  void close();
  bool isOpened() const { return isOpened_; }

  GbcData readData() override;
  int writeData(const GbcData &data) override;
private:
  bool isOpened_ = false;
  GbcHeader header_;
  GbcData data_;
};

#endif /* GBCFILE_H_ */
