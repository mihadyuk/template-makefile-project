#include <assert.h>
#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>

#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


std::vector<std::string> listDir(const std::string &dir) {
    std::vector<std::string> data;
    struct dirent *dirent;
    char buffer[4096];

    DIR *d = opendir(dir.c_str());

    if (d) {
        while ((dirent = readdir(d)) != nullptr) {
            if (dirent->d_type == DT_LNK) {
                memset(buffer, 0, sizeof(buffer));
                ssize_t lnkSize = readlink((dir + "/" + dirent->d_name).c_str(), buffer, sizeof(buffer));
                if (lnkSize > 0) {
                    //extract bus info
                    std::string lnk(buffer);
                    std::string::size_type posDev = lnk.rfind("/");
                    if (posDev != std::string::npos) {
                        std::string::size_type posDevBus = lnk.rfind("/", posDev - 1);
                        if (posDevBus != std::string::npos) {
                            data.push_back(lnk.substr(posDevBus + 1, posDev - posDevBus - 1));
                        }
                    }
                }
            }
        }
    }
    closedir(d);
    return data;
}

static void getPortInfo()
{
    // look for usb serial devices
    std::string devFolder("/sys/bus/usb-serial/devices");
    auto usbSerialDevices = listDir(devFolder);

    for (const auto &dev : usbSerialDevices) {
        printf("dev: \"%s\"\n", dev.c_str());
    }
}

int main(int argc, char *argv[]) {

  std::cout << "template makefile project \r\n";


  getPortInfo();
  return 0;
}


