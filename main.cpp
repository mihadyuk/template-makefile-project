#include <assert.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>
#include <chrono>
#include <sstream>
#include <sys/ioctl.h>

class PPP {
public:
  void start() {
    stop_ = false;

    // create a pipe for stdout, stderr
    int retval = pipe(pipe_stdout_);
    if (retval < 0) {
      printf("unable to create stdout pipe, error: %d\n", retval);
      return;
    }
    retval = pipe(pipe_stderr_);
    if (retval < 0) {
      printf("unable to create stderr pipe, error: %d\n", retval);
      close(pipe_stdout_[0]);
      close(pipe_stdout_[1]);
      return;
    }

    pid_ = fork();
    printf("fork result: 0x%.8X\n", pid_);
    if (pid_ > 0) {
      // parent
      int status = 0;
      for (int i = 0; i < 10; i++) {
        pid_t waitpid_retval = waitpid(pid_, &status, WNOHANG);
        printf("waitpid_retval: 0x%.8X, child exit status: 0x%.8X\n", waitpid_retval, status);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }

      // create a thread for processing stdout, stderr
      thread_ = std::thread(&PPP::threadFunc, this);
      std::ostringstream out;
      out << std::hex << thread_.get_id() << std::endl;
      std::string out_str = out.str();
      printf("thread id: %s\n", out_str.c_str());
      return;
    }
    else if (pid_ == 0) {
      // child
      dup2(pipe_stdout_[1], STDOUT_FILENO);
      close(pipe_stdout_[0]);
      close(pipe_stdout_[1]);
      dup2(pipe_stderr_[1], STDERR_FILENO);
      close(pipe_stderr_[0]);
      close(pipe_stderr_[1]);
      //std::string cmd("/usr/bin/pppd");
      //std::string params(buildPppParams());
      //printf("executing cmd: %s, params: %s \n", cmd.c_str(), params.c_str());
      //execl(cmd.c_str(), params.c_str(), nullptr);
#if 1
      execl("/usr/bin/pppd", "pppd", "/dev/ttyUSB0", "115200", "nodetach", "192.168.100.10:192.168.100.20", "nocrtscts", "noauth",
            "local", "persist", "unit", "3", "lcp-echo-failure", "3", "lcp-echo-interval", "20",
            "lcp-max-configure","9999", nullptr);
#endif
      printf("failed to start pppd, error %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  void stop() {
    pid_t pid = getpid();
    printf("pid: 0x%.4X\n", pid);
    if (pid == pid_) {
      printf("stop() is called from child. exiting");
      return;
    }
    printf("stop ppp requested\n");
    stop_ = true;
    thread_.join();
    printf("stopped ppp\n");

    printf("killing 0x%.8X pid\n", pid_);
    int retval = kill(pid_, SIGKILL);
    printf("kill returned status: %d\n", retval);
    int status = 0;
    pid_t waitpid_retval = waitpid(pid_, &status, 0);
    printf("waitpid_retval: 0x%.8X, status: 0x%.8X\n", waitpid_retval, status);

    close(pipe_stdout_[0]);
    close(pipe_stdout_[1]);
    close(pipe_stderr_[0]);
    close(pipe_stderr_[1]);
  }

private:
  std::string buildPppParams() {
      // set pppd parameters
      std::string params;

      //params += "pppd ";
      //params += " " + _path + " ";

      params += " /dev/ttyUSB0 115200 nodetach ";

      params += "192.168.100.10:192.168.100.20 ";

      params += "ms-dns 8.8.8.8 ";
      params += "ms-dns 8.8.4.4 ";

      params += "nocrtscts noauth ";
      //params += "nocrtscts ";

      params += "local persist unit 3 ";
      params += "lcp-echo-failure 3 lcp-echo-interval 20 ";
      params += "lcp-max-configure 99999 ";

      return params;
  }

  void threadFunc() {
    char buffer[128];

    while (stop_ == false) {
      // read stdout
      int bytesAvailable = 0;
      if (ioctl(pipe_stdout_[0], FIONREAD, &bytesAvailable) == 0) {
        if (bytesAvailable > 0) {
          memset(buffer, 0, sizeof(buffer));
          ssize_t retval = read(pipe_stdout_[0], buffer, bytesAvailable);
          if (retval > 0) {
            printf("stdout: %s\n", buffer);
          } else if (retval == 0) {
            printf("stdout: eof reached\n");
          }
          else {
            printf("stdout: error reading. retval: %ld", retval);
          }
        }
      }
      else {
        printf("ioctl failed\n");
      }

      // read stderr
      bytesAvailable = 0;
      if (ioctl(pipe_stderr_[0], FIONREAD, &bytesAvailable) == 0) {
        if (bytesAvailable > 0) {
          memset(buffer, 0, sizeof(buffer));
          ssize_t retval = read(pipe_stderr_[0], buffer, bytesAvailable);
          if (retval > 0) {
            printf("stderr: %s\n", buffer);
          } else if (retval == 0) {
            printf("stderr: eof reached\n");
          }
          else {
            printf("stderr: error reading. retval: %ld\n", retval);
          }
        }
      }
      else {
        printf("ioctl failed\n");
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    printf("exiting thread\n");
  }

  int pipe_stdout_[2];
  int pipe_stderr_[2];
  std::thread thread_;
  std::atomic_bool stop_;
  pid_t pid_ = -1;
};

int main(int argc, char *argv[]) {
#if 0
  execl("/usr/bin/pppd", "/dev/ttyUSB0", "115200", "nodetach", "192.168.100.10:192.168.100.20", "nocrtscts", "noauth",
              "local", "persist", "unit", "3", "lcp-echo-failure", "3", "lcp-echo-interval", "20",
              "lcp-max-configure","9999", nullptr);

  return 0;
#endif
  PPP ppp1;
  ppp1.start();

  int inval;
  scanf("%d", &inval);
  //std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  ppp1.stop();

  std::cout << "template makefile project \r\n";
  return 0;
}


