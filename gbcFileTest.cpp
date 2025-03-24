/*
 * gbcFileTest.cpp
 *
 *  Created on: Mar 24, 2025
 *      Author: user
 */
#include <assert.h>
#include <stdio.h>
#include "gbcFileTest.h"

GbcFileTest::GbcFileTest() {
  // TODO Auto-generated constructor stub

}

GbcFileTest::~GbcFileTest() {
  // TODO Auto-generated destructor stub
}

void GbcFileTest::run() {
  GbcData data;
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  runTestRead("/home/user/workspace/template-makefile-project/test_sec_2.bin", data);

  data = GbcData();
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  data.blob_ = std::move(std::vector<uint8_t>{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC});
  runTestRead("/home/user/workspace/template-makefile-project/test_sec_3.bin", data);

  data = GbcData();
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  data.blob_ = std::move(std::vector<uint8_t>{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC});
  data.checksum_ = 0xAA55ADDEUL;
  runTestRead("/home/user/workspace/template-makefile-project/test_sec_4.bin", data);

  data = GbcData();
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  runTestWrite("/tmp/test_sec_2_write.bin", data);

  data = GbcData();
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  data.blob_ = std::move(std::vector<uint8_t>{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC});
  runTestWrite("/tmp/test_sec_3_write.bin", data);

  data = GbcData();
  data.timestamp_ = 0x0807060504030201ULL;
  data.asciiSyms_ = std::move(std::vector<char>{(char)0xab, (char)0xcd, (char)0xef, (char)0xdd});
  data.blob_ = std::move(std::vector<uint8_t>{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC});
  data.checksum_ = 0xAA55ADDEUL;
  runTestWrite("/tmp/test_sec_4_write.bin", data);

}

void GbcFileTest::runTestRead(const std::string &fileName, const GbcData &expectedData) {
  GbcFile gbcFile;
  GbcData data;

  assert(gbcFile.isOpened() == false);
  data = gbcFile.readData();
  assert(data.timestamp_ == 0);
  assert(data.asciiSyms_.size() == 0);
  assert(data.blob_.size() == 0);
  assert(data.checksum_ == 0);

  int retval = gbcFile.open(fileName);
  printf("opening file \"%s\", retval: %d\n", fileName.c_str(), retval);
  if (retval >= 0) {
    assert(gbcFile.isOpened() == true);
    data = gbcFile.readData();
    assert(data.timestamp_ == expectedData.timestamp_);
    assert(data.asciiSyms_ == expectedData.asciiSyms_);
    assert(data.blob_ == expectedData.blob_);
    assert(data.checksum_ == expectedData.checksum_);

    gbcFile.close();
    assert(gbcFile.isOpened() == false);
    data = gbcFile.readData();
    assert(data.timestamp_ == 0);
    assert(data.asciiSyms_.size() == 0);
    assert(data.blob_.size() == 0);
    assert(data.checksum_ == 0);
  }
  else {
    assert(gbcFile.isOpened() == false);
  }
}

void GbcFileTest::runTestWrite(const std::string &fileName, const GbcData &dataToWrite) {
  GbcFile gbcFile;
  GbcData data;

  assert(gbcFile.isOpened() == false);
  data = gbcFile.readData();
  assert(data.timestamp_ == 0);
  assert(data.asciiSyms_.size() == 0);
  assert(data.blob_.size() == 0);
  assert(data.checksum_ == 0);

  int retval = gbcFile.open(fileName);
  printf("opening file \"%s\", retval: %d\n", fileName.c_str(), retval);
  if (retval >= 0) {
    assert(gbcFile.isOpened() == true);
    int retval = gbcFile.writeData(dataToWrite);
    assert(retval >= 0);

    gbcFile.close();
    assert(gbcFile.isOpened() == false);

  }
  else {
    assert(gbcFile.isOpened() == false);
  }
}

