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
  void run_test(const std::string &fileName, const GbcData &expectedData);
};

#endif /* GBCFILETEST_H_ */
