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


static std::string getModalias(const std::string &busInfo) {

    std::string modaliasPath = "/sys/bus/usb/devices/" + busInfo + "/modalias";

    std::ifstream modalias(modaliasPath, std::ios::in);
    std::string retval;
    modalias >> retval;
    //printf("modalias: \"%s\"", retval.c_str());
    return retval;
}

static std::vector<std::string> listUsbSerialDevices() {
    std::vector<std::string> retval;
    struct dirent *dirent;
    char buffer[4096];

    std::string dir("/sys/bus/usb-serial/devices");
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

                            // format string as "<device name> <bus info> <modalias>"
                            retval.push_back(std::string(dirent->d_name) + " " + busInfo + " " + getModalias(busInfo));
                        }
                    }
                }
            }
        }
        closedir(d);
    }

    return retval;
}

int main(int argc, char *argv[]) {

    auto devices = listUsbSerialDevices();

    for (const auto &dev : devices) {
        printf("dev: \"%s\"\n", dev.c_str());
    }
    return 0;
}
