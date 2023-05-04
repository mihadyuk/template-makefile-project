#include <assert.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>

class PPP {
public:
  void start() {
    thread_ = std::thread(&PPP::threadFunc, this);
  }

  void stop() {
    stop_ = true;
  }

private:
  std::string buildPppParams() {
      // set pppd parameters
      std::string params;

      //params += "pppd ";
      //params += " " + _path + " ";

      params += " /dev/ttyUSB0 115200 nodetach \n";

      params += "192.168.100.10:192.168.100.20 \n";

      params += "ms-dns 8.8.8.8 \n";
      params += "ms-dns 8.8.4.4 \n";

      params += "nocrtscts noauth \n";

      params += "local persist unit 3 \n";
      params += "lcp-echo-failure 3 lcp-echo-interval 20 \n";
      params += "lcp-max-configure 99999 \n";

      return params;
  }

  void threadFunc() {

    // create a pipe for stdout, stderr
    pipe(pipe_stdout_);
    pipe(pipe_stderr_);

    pid_t pid = fork();
    if (pid > 0) {
      // parent
      // process stdout, stderr from child. If child is killed, exit
      int status = 0;
      while (waitpid(pid, &status, WNOHANG) == 0) {
        // do some work while child is active
        if (WIFEXITED(status))
          break;
        if (stop_) {
          kill(pid, SIGKILL);
          stop_ = false;
        }
      }
      // exit from parent
      close(pipe_stdout_[0]);
      close(pipe_stdout_[1]);
      close(pipe_stderr_[0]);
      close(pipe_stderr_[1]);
      exit(EXIT_SUCCESS);
    }
    else if (pid == 0) {
      // child
      dup2(pipe_stdout_[1], STDOUT_FILENO);
      close(pipe_stdout_[0]);
      close(pipe_stdout_[1]);
      dup2(pipe_stderr_[1], STDERR_FILENO);
      close(pipe_stderr_[0]);
      close(pipe_stderr_[1]);
      std::string cmd("/usr/bin/pppd ");
      std::string params(buildPppParams());
      printf("executing cmd: %s, params: %s \n", cmd.c_str(), params.c_str());
      execl(cmd.c_str(), params.c_str(), nullptr);
      printf("failed to start pppd, error %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  int pipe_stdout_[2];
  int pipe_stderr_[2];
  std::thread thread_;
  std::atomic_bool stop_;
};

int main(int argc, char *argv[]) {

  PPP ppp1;
  ppp1.start();

  int inval;
  scanf("%d", &inval);

  ppp1.stop();

  std::cout << "template makefile project \r\n";
  return 0;
}


