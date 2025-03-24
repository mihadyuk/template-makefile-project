/*
 * gbcFileTest.h
 *
 *  Created on: Mar 24, 2025
 *      Author: user
 */

#ifndef GBCFILETEST_H_
#define GBCFILETEST_H_
#include <string>
#include "gbcFile.h"

class GbcFileTest {
public:
  GbcFileTest();
  virtual ~GbcFileTest();
  void run();
private:
  void runTestRead(const std::string &fileName, const GbcData &expectedData);
  void runTestWrite(const std::string &fileName, const GbcData &dataToWrite);
};

#endif /* GBCFILETEST_H_ */
