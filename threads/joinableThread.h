/*
 * joinableThread.h
 *
 *  Created on: Mar 26, 2025
 *      Author: user
 */

#ifndef THREADS_JOINABLETHREAD_H_
#define THREADS_JOINABLETHREAD_H_
#include <thread>

class JoinableThread {
public:
  JoinableThread();
  JoinableThread(const JoinableThread &) = delete;
  JoinableThread(JoinableThread &&) = delete;
  JoinableThread &operator=(const JoinableThread &) = delete;
  JoinableThread &operator=(JoinableThread &&) = delete;

  void start();
  void stop();
  virtual ~JoinableThread();
private:
  void worker();

  std::jthread thread_;
};

#endif /* THREADS_JOINABLETHREAD_H_ */
