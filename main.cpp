#include <assert.h>
#include <iostream>
#include <string>
#include <unistd.h>


class PPP {
public:
  void start() {

    std::string cmd("/usr/bin/pppd " + buildPppParams());

    //std::cout.rdbuf(prev_cout_buf);
    //std::cerr.rdbuf(prev_cerr_buf);

    pid_t pid = fork();
    if (pid == 0)
    {
        printf("executing cmd %s\n", cmd.c_str());
        int retval = std::system(cmd.c_str());
        if (retval < 0)
        {
            printf("failed to start pppd, error %d\n", retval);
            return;
        }
        printf("ppp started. retval: %d\n", retval);
        return;
    }
    return;
  }

  void stop() {
    std::string cmd("killall -SIGTERM pppd");

    printf("executing cmd %s\n", cmd.c_str());
    int retval = std::system(cmd.c_str());
    if (retval < 0)
    {
        printf("failed to stop pppd, error %d\n", retval);
        return;
    }
    printf("killed pppd. retval: %d\n", retval);
  }

private:
  std::string buildPppParams() {
      // set pppd parameters
      std::string params;

      //params += "pppd ";
      //params += " " + _path + " ";

      params += " /dev/ttyUSB0 115200 ";

      params += "192.168.100.10:192.168.100.20 ";

      params += "ms-dns 8.8.8.8 ";
      params += "ms-dns 8.8.4.4 ";

      params += "nocrtscts noauth ";

      params += "local persist unit 3 ";
      params += "lcp-echo-failure 3 lcp-echo-interval 20 ";
      params += "lcp-max-configure 99999 ";

      return params;
  }


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


