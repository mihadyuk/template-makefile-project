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

}

void GbcFileTest::run_test(const std::string &fileName, const GbcData &expectedData) {
  GbcFile gbcFile;
  int retval = gbcFile.open(fileName);
  printf("opening file \"%s\", retval: %d\n", fileName.c_str(), retval);
  if (retval >= 0) {
    assert(gbcFile.isOpened() == true);
    GbcData data = gbcFile.readData();
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

