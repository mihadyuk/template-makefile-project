/*
 * stringUtils.cpp
 *
 *  Created on: Nov 5, 2016
 *      Author: user
 */

#include "stringUtils.h"
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

using namespace std;

namespace utils {

  std::string dirname(const char *fullPath) {
    assert(fullPath);
    if (!fullPath)
      return "";
    char *_fullPath = (char *)malloc(strlen(fullPath) + 1);
    assert(_fullPath);
    if (!_fullPath)
      return "";
    strcpy(_fullPath, fullPath);
    /*
     * https://linux.die.net/man/3/dirname
     */
    char *p = ::dirname(_fullPath);
    assert(p);
    if (!p) {
      free(_fullPath);
      return "";
    }
    string retval(p);
    free(_fullPath);
    return retval;
  }

} /* namespace utils */
