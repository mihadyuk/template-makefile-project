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
#include <utility>
#include <mutex>
#include <list>
#include <type_traits>
#include <functional>

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

static const std::string PRODUCT_FIELD = "PRODUCT=";
static const std::string SLASH = "/";
static const std::string TTY_WORD = "tty";
static const std::string UEVENT_WORD = "/uevent";
static const std::string USB_SERIAL_DEVICES = "/sys/bus/usb-serial/devices";

static const std::string test_buffer =
        "DEVTYPE=usb_interface"
        "DRIVER=pl2303"
        "PRODUCT=067b/2303/300"
        "TYPE=0/0/0"
        "INTERFACE=255/0/0"
        "MODALIAS=usb:v067Bp2303d0300dc00dsc00dp00icFFisc00ip00in00";

bool getVidPidFromProductField(const std::string &buffer, std::pair<std::string, std::string> &result)
{
    auto product_pos = buffer.find(PRODUCT_FIELD);

    if (product_pos == std::string::npos)
    {
        printf("field PRODUCT not found");
        return false;
    }

    std::string token = buffer.substr(product_pos + PRODUCT_FIELD.size());
    while ((product_pos = token.find(SLASH)) != std::string::npos)
    {
        std::string number = token.substr(0, product_pos);
        while (number.size() < 4)
        {
            number.insert(0, "0");
        }
        if (result.first.empty())
        {
            result.first = number;
        }
        else if (result.second.empty())
        {
            result.second = number;
        }
        else
        {
            return true;
        }
        token.erase(0, product_pos + SLASH.size());
    }
    return false;
}

    template<typename F, typename... Fparams>
    class Callback {
    public:
        void add(const F callback)
        {
            std::lock_guard<std::mutex> lock(_mutex);
#if 1
            for (const F &item : _callbacks)
            {
                auto callback_ptr = callback.template target<void(*)(Fparams...)>();
                auto item_ptr     = item.template target<void(*)(Fparams...)>();
#if 1
                if (callback_ptr && item_ptr && *callback_ptr == *item_ptr)
                {
                    printf("callback %p is already added\n", *callback_ptr);
                    return;
                }
#endif

            }
#endif
            _callbacks.push_back(callback);
        }

        void call(Fparams... args)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            for (const auto & callback : _callbacks)
            {
                callback(args...);
            }
        }
    private:
        std::mutex _mutex;
        std::list<F> _callbacks;
    };



static void func(int value) {
    printf("value: %d\n", value);
}

int main(int argc, char *argv[]) {
    Callback<std::function<void(int)>, int> callbacks;
    std::function<void(int)> fn1(func);
    std::function<void(int)> fn2(std::bind(&func, std::placeholders::_1));
    auto ptr1 = fn1.target<void(*)(int)>();
    auto ptr2 = fn2.target<std::function<void(int)>>();
    callbacks.add(func);
    callbacks.add(func);
    callbacks.call(10);

#if 0
    std::pair<std::string, std::string> result;
    auto retval = getVidPidFromProductField(test_buffer, result);
    assert(retval == true);
#if 0
    auto devices = listUsbSerialDevices();

    for (const auto &dev : devices) {
        printf("dev: \"%s\"\n", dev.c_str());
    }
#endif
#endif
    return 0;
}
