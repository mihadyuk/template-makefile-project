/*
 * joinableThread.h
 *
 *  Created on: Mar 26, 2025
 *      Author: user
 */

#ifndef THREADS_JOINABLETHREAD_H_
#define THREADS_JOINABLETHREAD_H_
#include <thread>
#include <stop_token>

class JoinableThread {
public:
  JoinableThread() = default;
  JoinableThread(const JoinableThread &) = delete;
  JoinableThread(JoinableThread &&) = delete;
  JoinableThread &operator=(const JoinableThread &) = delete;
  JoinableThread &operator=(JoinableThread &&) = delete;

  void start();
  void stop();
  bool isActive() const { return thread_.joinable(); }
  virtual ~JoinableThread();
private:
  static void worker(std::stop_token stoken, JoinableThread &self);

  std::jthread thread_;
};

#endif /* THREADS_JOINABLETHREAD_H_ */
