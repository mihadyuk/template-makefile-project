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
#include <fstream>


struct GbcData {
  uint64_t timestamp_ = 0;
  std::vector<char> asciiSyms_;
  std::vector<uint8_t> blob_;
  uint32_t checksum_ = 0;
};

class IGbc {
public:
  virtual GbcData readData() = 0;
  virtual int writeData(const GbcData &data) = 0;
};

class GbcFile : public IGbc {
public:
  GbcFile();
  GbcFile(const GbcFile &src) = delete;
  GbcFile(GbcFile &&src) = delete;
  GbcFile &operator=(const GbcFile &src) = delete;
  GbcFile &operator=(GbcFile &&src) = delete;
  virtual ~GbcFile();

  int open(const std::string &fullPath);
  void close();
  bool isOpened() const { return fs_.is_open(); }

  GbcData readData() override;
  int writeData(const GbcData &data) override;
private:
  int openInternal(const std::string &fullPath);

  std::fstream fs_;
  std::string fullPath_;
};

#endif /* GBCFILE_H_ */
