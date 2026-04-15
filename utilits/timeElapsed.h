/*
 * timeElapsed.h
 *
 *  Created on: Jun 8, 2015
 *      Author: user
 */

#ifndef TIMEELAPSED_H_
#define TIMEELAPSED_H_
#include <chrono>
//#include <type_traits>

template <typename ClockSource>
class TimeElapsedBase {
#if 0
    static_assert(std::is_same_v<ClockSource, std::chrono::steady_clock> ||
                  std::is_same_v<ClockSource, std::chrono::high_resolution_clock>);
    static_assert(ClockSource::is_steady);
#endif
    ClockSource::time_point timeStamp_;
public:
    TimeElapsedBase() {
        start();
    }
    virtual ~TimeElapsedBase() = default;

    void start() {
        timeStamp_ = ClockSource::now();
    }

    std::chrono::milliseconds elapsedMs() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(ClockSource::now() - timeStamp_);
    }
};

using TimeElapsed = TimeElapsedBase<std::chrono::steady_clock>;


#endif //TIMEELAPSED_H_
