/*
 * utils.h
 *
 *  Created on: May 18, 2023
 *      Author: user
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <optional>
#include <utility>
#include <unistd.h>

#include "timeElapsed.h"

enum class WaitpidResult {
  Error = -1,
  NormalExit = 0,
  KilledBySignal = 1,
  Timeout = 2
};

/**
 * WaitpidResult, status
 * */
using WaitProcessCompletionResult = std::pair<WaitpidResult, std::optional<int>>;

WaitProcessCompletionResult waitProcessCompletion(pid_t pid, uint32_t timeoutMs);

#endif /* UTILS_H_ */
