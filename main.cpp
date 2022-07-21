#include <assert.h>
#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>

#include <fstream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

static std::string getVidPid(const std::string &busInfo) {

    std::string modaliasPath = "/sys/bus/usb/devices/" + busInfo + "/modalias";

    std::ifstream modalias(modaliasPath, std::ios::in);
    std::string retval;
    modalias >> retval;
    printf("modalias: \"%s\"", retval.c_str());
    return retval;
}

static std::vector<std::string> listDir(const std::string &dir) {
    std::vector<std::string> data;
    struct dirent *dirent;
    char buffer[4096];

    DIR *d = opendir(dir.c_str());

    if (d) {
        while ((dirent = readdir(d)) != nullptr) {
            if (dirent->d_type == DT_LNK) {
                memset(buffer, 0, sizeof(buffer)); // readlink does not paste "\n", so we have to clear buffer
                ssize_t lnkSize = readlink((dir + "/" + dirent->d_name).c_str(), buffer, sizeof(buffer));
                if (lnkSize > 0) {
                    //extract bus info
                    std::string lnk(buffer);
                    std::string::size_type posDev = lnk.rfind("/");
                    if (posDev != std::string::npos) {
                        std::string::size_type posDevBus = lnk.rfind("/", posDev - 1);
                        if (posDevBus != std::string::npos) {
                            std::string busInfo(lnk.substr(posDevBus + 1, posDev - posDevBus - 1));

                            // get vid & pid using bus info
                            data.push_back(std::string(dirent->d_name) + " " + busInfo + " " + getVidPid(busInfo));
                        }
                    }
                }
            }
        }
        closedir(d);
    }

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


