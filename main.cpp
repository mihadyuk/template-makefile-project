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

class PPP {
public:
  void start() {
    thread_ = std::thread(&PPP::threadFunc, this);
    std::ostringstream out;
    out << std::hex << thread_.get_id() << std::endl;
    std::string out_str = out.str();
    printf("thread id: %s\n", out_str.c_str());
  }

  void stop() {
    printf("stop ppp requested\n");
    stop_ = true;
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

      params += "local persist unit 3 ";
      params += "lcp-echo-failure 3 lcp-echo-interval 20 ";
      params += "lcp-max-configure 99999 ";

      return params;
  }

  void threadFunc() {

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

    pid_t pid = fork();
    if (pid > 0) {
      // parent
      printf("fork result: 0x%.8X\n", pid);
      // process stdout, stderr from child. If child is killed, exit
      int status = 0;
      pid_t waitpid_retval = 0;
      while ((waitpid_retval = waitpid(pid, &status, WNOHANG)) == 0) {
        // do some work while child is active
        if (WIFEXITED(status)) {
          printf("child exit status: 0x%.8X\n", status);
          break;
        }
        if (stop_) {
          printf("killing 0x%.8X pid\n", pid);
          int retval = kill(pid, SIGKILL);
          printf("kill returned status: %d\n", retval);
          stop_ = false;
        }


        char buffer[128];
        // read stdout
        memset(buffer, 0, sizeof(buffer));
        ssize_t retval = read(pipe_stdout_[0], buffer, sizeof(buffer));
        if (retval > 0) {
          printf("stdout: %s\n", buffer);
        } else if (retval == 0) {
          printf("stdout: eof reached\n");
        }
        else {
          printf("stdout: error reading. retval: %ld", retval);
        }

        // read stderr
        memset(buffer, 0, sizeof(buffer));
        retval = read(pipe_stderr_[0], buffer, sizeof(buffer));
        if (retval > 0) {
          printf("stderr: %s\n", buffer);
        } else if (retval == 0) {
          printf("stderr: eof reached\n");
        }
        else {
          printf("stderr: error reading. retval: %ld", retval);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
      // exit from parent
      close(pipe_stdout_[0]);
      close(pipe_stdout_[1]);
      close(pipe_stderr_[0]);
      close(pipe_stderr_[1]);
      printf("normal exiting parent\n");
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
    else {
      printf("fork error: %d\n", pid);
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


